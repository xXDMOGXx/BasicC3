#ifndef CHESSBOT_WIRELESS_CPP
#define CHESSBOT_WIRELESS_CPP

#include "wireless.h"

#include "Arduino.h"
#include "logging.h"
#include "connection.h"
#include "timer.h"
#include "../env.h"

#include "WiFi.h" // Built in library

namespace ChessBot
{
    void connectWiFi() {
        logln((char*)"Connecting to WiFi Network...");
        WiFi.mode(WIFI_STA);
        WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
        if (WiFi.status() == WL_CONNECTED) {
            logln((char*)"Connected to WiFi Network!");
            // Connect to the PC server
            connect();
        } else {
            logln((char*)"Connection Failed! Retrying...");
            timerDelay(5000, &connectWiFI);
        }
    }

    void createWiFi() {
        logln((char*)"Creating Access Point");
        WiFi.softAP(WIFI_SSID, WIFI_PASSWORD);
        logln((char*)"Access Point Created");
        connect();
    }
};

#endif