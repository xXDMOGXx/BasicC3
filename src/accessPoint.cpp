#ifndef BOT_ACCESS_POINT_CPP
#define BOT_ACCESS_POINT_CPP

#include "accessPoint.h"

#include "Arduino.h"
#include "logging.h"
#include "connection.h"
#include "timer.h"

#include "WiFi.h"

namespace Bot
{
    constexpr static char SSID[] = "Bot Wifi Network";
    constexpr static char PASS[] = "password";
    
    void connectAccessPoint() {
        logln((char*)"Connecting to WiFi Network...");
        WiFi.mode(WIFI_STA);
        WiFi.begin(SSID, PASS);
        if (WiFi.status() == WL_CONNECTED) {
            logln((char*)"Connected to WiFi Network!");
            // Connect to the PC websocket server
            connect();
        } else {
            logln((char*)"Connection Failed! Retrying...");
            timerDelay(5000, &connectAccessPoint);
        }
    }

    void createAccessPoint() {
        logln((char*)"Creating Access Point");
        WiFi.softAP(SSID, PASS);
        logln((char*)"Access Point Created");
        connect();
    }
};

#endif