#include <Arduino.h>
#include <time.h> // For struct tm
#include "getHtml.h"
#include "pollPrice.h"

// Forward declaration of the ReadPrice class so GetHTML knows it exists
// (Assuming ReadPrice is defined in your main file or a separate header)
//class ReadPrice; 



// --- The GetHTML Class ---

    GetHTML::GetHTML(ReadPrice* priceObject) {
        myP = priceObject;
    }

    void GetHTML::limUp() {
        // Assuming ReadPrice has getLim() and setLim(float)
        // I cast to ReadPrice pointers methods. 
        // Note: You need to implement these in your ReadPrice class
        float myF = myP->getLim();
        myF += 0.005;
        if (myF > 0.17) {
            myF = 0.17;
        }
        myP->setLim(myF);
    }

    void GetHTML::limDown() {
        float myF = myP->getLim();
        myF -= 0.005;
        if (myF < 0.005) {
            myF = 0.0;
        }
        myP->setLim(myF);
    }

    String GetHTML::getTimeString() {
        // Standard C++ approach to time formatting
        struct tm timeinfo;
        if(!getLocalTime(&timeinfo)){
            return "Time Error";
        }
        
        // Format: DD/MM/YYYY HH:MM
        char buffer[30];
        // Note: The Python code added `myP.getCH()` (Current Hour) into the string separately.
        // Here we just use the real time.
        // If getCH() is different from real hour (e.g. simulation), use myP->getCH()
        snprintf(buffer, 30, "%02d/%02d/%04d %02d:%02d", 
            timeinfo.tm_mday, 
            timeinfo.tm_mon + 1, 
            timeinfo.tm_year + 1900, 
            myP->getCH(), // Using the logic from python code
            timeinfo.tm_min
        );
        return String(buffer);
    }

    String GetHTML::getPrices() {
        String myprices = "";
        for (int i = 0; i < 24; i++) {
            // Using String(val, 4) to keep 4 decimal places precision
            myprices += String(myP->getCurrPrice(i), 4);
            if (i < 23) {
                myprices += ",";
            }
        }
        return myprices;
    }

    String GetHTML::getBkCol() {
        String mycolor = "";
        float limit = myP->getLim();
        int currentHour = myP->getCH();

        for (int i = 0; i < 24; i++) {
            float price = myP->getCurrPrice(i);
            
            if (limit > price) {
                // Price is cheap (Green)
                if (i == currentHour) {
                    mycolor += "\"#20a020\""; // Darker Green for current
                } else {
                    mycolor += "\"#00f000\""; // Bright Green
                }
            } else {
                // Price is expensive (Red)
                if (i == currentHour) {
                    mycolor += "\"#a02020\""; // Darker Red for current
                } else {
                    mycolor += "\"#f00000\""; // Bright Red
                }
            }

            if (i < 23) {
                mycolor += ",";
            }
        }
        return mycolor;
    }

    String GetHTML::getLimit() {
        String limitval = "";
        float lim = myP->getLim();
        for (int i = 0; i < 24; i++) {
            limitval += String(lim, 4);
            if (i < 23) {
                limitval += ",";
            }
        }
        return limitval;
    }

    
    String GetHTML::processor(const String& var) {
        if(var == "TIME") {
            return getTimeString();
        }
        else if(var == "PRICES") {
            return getPrices();
        }
        else if(var == "COLORS") {
            return getBkCol();
        }
        else if(var == "LIMITS") {
            return getLimit();
        }
        return String(); // Return empty if unknown
    }

    // Returns the complete HTML page as one large String
    // (ESP32 has enough RAM for this ~4KB string)
/*
    String GetHTML::getPage() {
        String page;
        // Reserve memory to prevent fragmentation (approx size)
        page.reserve(4500); 

        page += FPSTR(htdata_1);     // Head
        page += getTimeString();     // Dynamic Time
        page += FPSTR(htdata_2);     // Buttons & Script Start
        page += getPrices();         // Data Array 1
        page += FPSTR(htdata_3);     // JS glue
        page += getBkCol();          // Colors Array
        page += FPSTR(htdata_4);     // JS glue
        page += getLimit();          // Data Array 2
        page += FPSTR(htdata_5);     // Footer

        return page;
    }
*/
/*
// ... existing includes and ReadPrice class ...

// 1. Create your price object
ReadPrice myP; 

// 2. Include the code provided above (or paste it here)

// 3. Create the HTML generator, passing the address of myP
GetHTML myGet(&myP);

void setup() {
    // ... setup wifi ...
    
    server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
        // Generate the page and send it
        request->send(200, "text/html", myGet.getPage());
    });
    
    // ... rest of setup ...
}
*/



