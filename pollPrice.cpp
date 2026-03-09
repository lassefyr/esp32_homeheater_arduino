#include <Arduino.h>
#include <HTTPClient.h>
#include <WiFiClientSecure.h>
#include <ArduinoJson.h>
#include <vector>
#include <algorithm>
#include <time.h>
#include "pollPrice.h"
#include "jsondata.h"

#define USE_TEST_DATA false 
/*
WiFi: Ensure WiFi is connected before calling checkIfUpd or forceUpd.
Time: The ESP32 getLocalTime depends on NTP. In your main setup, ensure you call:

configTime(0, 0, "pool.ntp.org"); 
setenv("TZ", "EET-2EEST,M3.5.0/3,M10.5.0/4", 1); // Example for Finland
tzset();
*/

    ReadPrice::ReadPrice() {
        // Initialize array with default safe values
        for (int i = 0; i < 96; i++) curPr[i] = 0.2;
    }
    
    
    // Helper to calculate array index from Hour and Minute
    int ReadPrice::getQIndex(int hours, int mins) {
        if (hours >= 0 && hours <= 23) {
            return (hours * 4) + (mins / 15);
        } else {
            return -1;
        }
    }

    // Logic to calculate the dynamic price limit
    // Takes the 25th lowest price (approx index 24) and adds margin
    void ReadPrice::calcLimitFromPrices() {
        std::vector<float> tlist;
        for (int i = 0; i < 96; i++) {
            tlist.push_back(curPr[i]);
        }
        
        // Sort ascending
        std::sort(tlist.begin(), tlist.end());

        if (tlist.size() >= 25) {
            // Logic from python: tlist[24] + 0.005
            limP = tlist[24] + 0.005;
        }
    }

    void ReadPrice::setLim(float value) {
        limP = value;
        Serial.print("setlimit to ");
        Serial.println(value);
    }

    float ReadPrice::getLim() {
        return limP;
    }

    // Returns average price for a specific hour (averages 4 quarters)
    float ReadPrice::getCurrPrice(int myH) {
        if (myH > 23) myH = myH - 24; // Fixed logic: python had -23 which implies index 24 becomes 1. -24 makes it 0.

        float tprice = 0.0;
        int myIndex = myH * 4;

        for (int i = 0; i < 4; i++) {
            if (myIndex < 96) {
                tprice += curPr[myIndex];
            }
            myIndex++;
        }
        tprice /= 4.0;
        return tprice;
    }

    // Get current index (0-95) based on current time
    int ReadPrice::getInd() {
        struct tm timeinfo;
        if (!getLocalTime(&timeinfo)) return 0;
        
        // Python logic adjusted hour by clkDev, but getLocalTime handles timezone 
        // if configTime is set correctly. Assuming we stick to Python logic:
        int myH = timeinfo.tm_hour; 
        // Note: In Python you added clkDev manually. In ESP32, usually configTime handles TZ.
        // If you want manual shift: myH += clkDev;

        if (myH >= 24) myH = myH - 24;

        return (myH * 4) + (timeinfo.tm_min / 15);
    }

    int ReadPrice::getCH() {
        struct tm timeinfo;
        if (!getLocalTime(&timeinfo)) return 0;
        return timeinfo.tm_hour; // Returns 0-23
    }

    float ReadPrice::getPriceNow() {
        int idx = getInd();
        if (idx >= 0 && idx < 96) {
            return curPr[idx];
        }
        return 0.99; // Error safe high price
    }

    void ReadPrice::forceUpd() {
        needRd = true;
        checkIfUpd(0);
    }
    
/**
 * @brief Checks if it is time to update electricity prices and performs the fetch.
 * 
 * This function connects to the spot-hinta.fi API to retrieve today's prices.
 * It handles WiFi connection, JSON deserialization, and updates the global
 * price array 'curPr'.
 * 
 * @note This function allocates a large JSON document on the Heap and may 
 *       cause heap fragmentation if called frequently. It is designed to run
 *       once per day between 00:00 and 01:00.
 * 
 * @param hour The specific hour to check against (0-23). 
 *             Pass -1 to automatically retrieve the current system hour.
 * @return void
 */
 void ReadPrice::checkIfUpd(int hour)
{
    if (hour == -1) hour = getCH();
    
    // Reset the flag at 11 PM
    if (hour == 23) needRd = true;

    if (needRd && (hour == 0 || hour == 1))
    {
        Serial.println("Starting Price Update Sequence...");

        const int maxRetries = 3;
        int attempt = 0;
        bool success = false;

        // ALLOCATE MEMORY ONCE (ON HEAP)
        // 20KB buffer. Using pointer prevents stack overflow.
        DynamicJsonDocument* doc = new DynamicJsonDocument(16384); 
        
        if (!doc) {
            Serial.println("CRITICAL: Heap allocation failed! Rebooting...");
            delay(1000);
            ESP.restart(); // If we can't allocate RAM, we must reboot.
            return;
        }

        // RETRY LOOP
        while (attempt < maxRetries && !success)
        {
            attempt++;
            Serial.printf("Attempt %d of %d...\n", attempt, maxRetries);

            #if USE_TEST_DATA
                // Test Data Logic (Same as before)
                DeserializationError error = deserializeJson(*doc, TEST_JSON_DATA);
                if (!error) success = true;
            #else
                // Web Logic
                WiFiClientSecure client;
                client.setInsecure(); // Or use setCACert if you have the cert
                HTTPClient http;
                http.setTimeout(10000); // 10 second timeout

                if (http.begin(client, url))
                {
                    int httpCode = http.GET();
                    if (httpCode == HTTP_CODE_OK)
                    {
                        // FIX: Download payload to a String first
                        // This handles Chunked Transfer Encoding safely
                        String payload = http.getString();
                        
                        // Optional debug: check if payload looks empty
                        if (payload.length() == 0) {
                            Serial.println("Error: Empty payload received");
                        } else {
                            DeserializationError error = deserializeJson(*doc, payload);
                            if (!error) {
                                success = true;
                            } else {
                                Serial.printf("JSON Error: %s\n", error.c_str());
                                // Debug: Print first 50 chars to see what we actually got
                                Serial.println("Start of payload: " + payload.substring(0, 50));
                            }
                        }
                    }
                    else {
                        Serial.printf("HTTP Error: %s\n", http.errorToString(httpCode).c_str());
                    }
                    http.end(); // Close connection
                }
                else {
                    Serial.println("Connection failed to start.");
                }
            #endif

            if (!success) {
                Serial.println("Retrying in 3 seconds...");
                doc->clear(); // Clear the JSON document before reuse
                delay(3000);  // Wait before hammering the server again
            }
        }

        // PROCESS DATA IF SUCCESSFUL
        if (success)
        {
            // Reset old prices
            for (int i = 0; i < 96; i++) curPr[i] = 0.2;
            
            // Extract data using (*doc)
            for (JsonObject item : (*doc).as<JsonArray>())
            {
                const char* dt = item["DateTime"];
                float price = item["PriceWithTax"];
                
                // Safety check on string length
                if (dt && strlen(dt) >= 16) {
                    char hBuf[3] = {dt[11], dt[12], '\0'};
                    char mBuf[3] = {dt[14], dt[15], '\0'};
                    int myHour = atoi(hBuf);
                    int myMin = atoi(mBuf);
                    int idx = getQIndex(myHour, myMin);
                    if (idx >= 0 && idx < 96) curPr[idx] = price;
                }
            }
            calcLimitFromPrices();
            needRd = false; // Mark as done
            Serial.println("Prices Updated Successfully!");
        }
        else
        {
            Serial.println("FAILED all attempts.");
            // Apply fallback prices
            if(needRd) {
                 for (int i = 0; i < 96; i++) {
                    curPr[i] = 0.12;
                    if(i<24) curPr[i] = 0.06;
                 }                     
                 limP = 0.1;
                 
                 // CRITICAL DECISION HERE:
                 // If we failed 3 times, do we want to try again in the next loop?
                 // If yes, keep needRd = true.
                 // If no (accept defeat for today), set needRd = false.
                 
                 needRd = false; // Set to false so we don't hammer the API all night
            }
        }

        // FREE MEMORY
        delete doc; 
    }
}