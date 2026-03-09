#include <Arduino.h>
#include <WiFi.h> // Use <ESP8266WiFi.h> if using ESP8266
#include <ESPAsyncWebServer.h>
#include <time.h>
#include <Ticker.h>
#include <esp_task_wdt.h>
#include "secrets.h"
#include "pollPrice.h"
#include "getHtml.h"

#define WDT_TIMEOUT 50  // seconds

// --- Configuration ---
const char* ssid = YOUR_SSID;         // secrets.SSID
const char* password = YOUR_PASSWORD; // secrets.PASSWORD
const char* hostname = "My-ESP32-Heater"; 

const int ledPin = 2;
const char* TZ_INFO = "EET-2EEST,M3.5.0/3,M10.5.0/4"; 

// --- Global Objects ---
AsyncWebServer server(80);
Ticker ledTicker;
Ticker backgroundTaskTicker;
Ticker wdtTicker;

// --- HState Class (Hardware Control) ---
class HState {
public:
    const int pin15kW = 12;
    const int pin9kW = 14;
    const int pinIn = 27;
    int tim15kW = 0;

    HState() {
        pinMode(pin15kW, OUTPUT);
        pinMode(pin9kW, OUTPUT);
        pinMode(pinIn, INPUT_PULLUP);
        digitalWrite(pin15kW, LOW);
        digitalWrite(pin9kW, LOW);
    }

    void en_15kW() { digitalWrite(pin15kW, HIGH); }
    void dis_15kW() { digitalWrite(pin15kW, LOW); }
    void en_9kW() { digitalWrite(pin9kW, HIGH); }
    void dis_9kW() { digitalWrite(pin9kW, LOW); }

    void chk15kW() {
        if (digitalRead(pinIn) == HIGH) { // Note: Python .value() is typically HIGH/True
            tim15kW++;
            if (tim15kW > 10) {
                tim15kW = 10;
                en_9kW();
            }
        } else {
            dis_9kW();
            tim15kW = 0;
        }
    }
};

HState relMod;
ReadPrice myP;
volatile bool backgroundLogicAlive = false;
GetHTML myGet(&myP);

// --- Helper Functions ---
void toggleLed() {
    digitalWrite(ledPin, !digitalRead(ledPin));
}

// Equivalent to NTP setup
void setupNTP() {
    configTzTime(TZ_INFO, 0, "pool.ntp.org", "time.nist.gov");
    struct tm timeinfo;
    int retry = 0;
    while(!getLocalTime(&timeinfo) && retry < 5){
        Serial.println("Failed to obtain time");
        delay(500);
        retry++;
    }
    if (retry == 5) ESP.restart();
    Serial.println("Time synchronized");
}

// Equivalent to myBG() logic
// In Arduino, we don't usually sleep() inside a function for 20s blocking other code.
// Instead, we use a timer to fire this function periodically.
void runBackgroundLogic() {
    static bool isInitialized = false;

    // First run initialization (force update)
    if (!isInitialized) {
        myP.forceUpd();
        isInitialized = true;
    }

    // Main logic
    myP.checkIfUpd();
    
    Serial.printf("Free Heap: %d\n", ESP.getFreeHeap());

    float priceNow = myP.getPriceNow();
    float lim      = myP.getLim();

    Serial.printf("priceNow = %.6f, lim = %.6f\n", priceNow, lim);

    if (priceNow > lim) {
        Serial.println("drives OFF");
        relMod.dis_15kW();
    } else {
        Serial.println("Halpaa -- ON ");
        relMod.en_15kW();
    }
    /*
    if (myP.getPriceNow() > myP.getLim()) {
        Serial.println("drives OFF");
        relMod.dis_15kW();
    } else {
        Serial.println("Halpaa -- ON ");
        relMod.en_15kW();
    }*/

    relMod.chk15kW();

    backgroundLogicAlive = true;
}
void logHeap(const char* tag) 
{
    Serial.printf("[%s] Free heap: %u\n", tag, ESP.getFreeHeap());
}

void setup() {
    Serial.begin(115200);

    esp_task_wdt_config_t wdt_config = {
        .timeout_ms = WDT_TIMEOUT * 1000, // Convert seconds to milliseconds
        .idle_core_mask = (1 << 0) | (1 << 1), // Watch both cores (0 and 1)
        .trigger_panic = true             // Trigger panic (restart) on timeout
    };

    // 2. IMPORTANT: Try to reconfigure first. 
    // If it fails (because it wasn't initialized yet), then initialize it.
    if (esp_task_wdt_reconfigure(&wdt_config) != ESP_OK) {
        esp_task_wdt_init(&wdt_config);
    }

    // 3. Add the current task (loopTask) to the TWDT
    esp_err_t err = esp_task_wdt_add(NULL);
    if (err != ESP_OK) {
        Serial.printf("Failed to add task to WDT: %s\n", esp_err_to_name(err));
    } else {
        Serial.println("Task added to WDT successfully");
    }

    // Hardware Setup
    pinMode(ledPin, OUTPUT);
    
    // Connect WiFi
    WiFi.mode(WIFI_STA);
    WiFi.setHostname(hostname); 

    WiFi.begin(ssid, password);
    Serial.print("Connecting to network...");
    
    int wifi_retry = 0;
    while (WiFi.status() != WL_CONNECTED) {
        delay(1000);
        Serial.print(".");
        wifi_retry++;
        if (wifi_retry > 20) ESP.restart(); // Software reset if connection fails long
    }
    Serial.println("\nConnected! IP: " + WiFi.localIP().toString());

    // Setup Time (NTP)
    setupNTP();

    // Start LED Blink Timer (every 500ms)
    ledTicker.attach_ms(500, toggleLed);

    // Setup Web Server Routes
    server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
        // This tells the server: 
        // 1. Send status 200
        // 2. Content type text/html
        // 3. Use the 'index_html' stored in PROGMEM (Flash)
        // 4. Use the processor lambda function to replace %VAR%
        
        request->send_P(200, "text/html", index_html, [](const String& var){
            // Call the method inside your GetHTML instance
            return myGet.processor(var); 
        });
    });    

/*
    server.on("/toggle", HTTP_GET, [](AsyncWebServerRequest *request){
        Serial.println("Receive Toggle Request!");
        // led_module.toggle(); // Implement logic
        request->send(200, "text/plain", "OK");
    });
*/
    server.on("/pup", HTTP_GET, [](AsyncWebServerRequest *request)
    {
        //logHeap("before limUp");
        myGet.limUp();
        //logHeap("after limUp");        
        request->send(200, "text/plain", "OK");
        //logHeap("after send");
    });

    server.on("/pdown", HTTP_GET, [](AsyncWebServerRequest *request){
        myGet.limDown();
        //Serial.println("PriceDown!");
        request->send(200, "text/plain", "OK");
    });

    server.on("/shutdown", HTTP_GET, [](AsyncWebServerRequest *request){
        request->send(200, "text/plain", "Shutting down (restarting)...");
        delay(1000);
        ESP.restart();
    });

    server.begin();

    // Init Logic immediately
    runBackgroundLogic();
    
    // Schedule background logic to run every 20 seconds (replacing uasyncio.sleep(20))
    backgroundTaskTicker.attach(20, runBackgroundLogic);
}

void loop() {
    // Empty Loop
    // Unlike MicroPython with uasyncio, the AsyncWebServer handles requests 
    // in the background, and Tickers handle the periodic tasks.
    
    // Note: If you have logic that MUST run in the main thread (not interrupt context),
    // you should check flags here instead of doing heavy work in Ticker callbacks.
    
    // WDT feeding is handled automatically by loop() in Arduino ESP32 usually,
    // but explicit feeding can be done here:
    if(backgroundLogicAlive)
    {
        esp_task_wdt_reset(); 
        backgroundLogicAlive = false;
    }

    delay(1000);

}



