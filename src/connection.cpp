#ifndef BOT_CONNECTION_CPP
#define BOT_CONNECTION_CPP

#include "connection.h"

#include "Arduino.h"
#include "logging.h"
#include "timer.h"
#include "control.h"
#include "motor.h"
#include "status.h"

#include "WiFi.h"

namespace Bot
{
    enum MESSAGE_TYPE {
        HANDSHAKE_REQUEST,
        HANDSHAKE_ACCEPTED,
        PING_REQUEST,
        PING_RESPONDED,
        DISABLE_WEAPON,
        ENABLE_WEAPON,
        DISABLE_DRIVE,
        ENABLE_DRIVE,
        SEND_LEFT,
        SEND_RIGHT,
        SEND_WEAPON,
        ENABLE_AUTO,
        DISABLE_AUTO
    };

    constexpr static char IP[] = "192.168.4.2";
    constexpr static int PORT = 61134;
    constexpr static bool DO_HANDSHAKE = true;
    constexpr static int HANDSHAKE_INTERVAL = 3000;
    constexpr static bool DO_PINGING = true;
    constexpr static int PING_INTERVAL = 1000;

    WiFiClient client;
    bool pinging = false;
    bool pingFailed = false;
    
    void connect() {
        setConnectionStatus(false);
        logln((char*)"Connecting to Server...");
        if (!client.connect(IP, PORT)) {
            logln((char*)"Connection Failed! Retrying...");
            timerDelay(5000, &connect);
        } else {
            logln((char*)"Connected to Server!");
            if (DO_HANDSHAKE) {
                handshake();
            } else {
                setConnectionStatus(true);
            }
        }
    }

    void disconnect() {
        setConnectionStatus(false);
        client.stop();
    }

    void connectionTest() {
        if (!client.connected()) {
            logln((char*)"Disconnected! Reconnecting...");
            connect();
        }
    }

    void acceptData() {
        if (client.available()) {
            std::array<byte, 32> message;
            int len = 0;
            while (client.available() || message[len-1] != ';') {
                message[len] = client.read();
                len += 1;
            }
            std::array<int, 32> buffer;
            decodeMessage(message, buffer, len);
            handleMessage(buffer);
        }
    }

    void decodeMessage(std::array<byte, 32> message, std::array<int, 32>& buffer, int len) {
        for(int i = 0; i < len; i++) {
            if ((char)message[i] == ';') { break; }
            buffer[i] = (int)message[i];
        }
    }

    void handleMessage(std::array<int, 32>& message) {
        switch (message[0]) {
            case HANDSHAKE_ACCEPTED:
                if (!getConnectionStatus()) {
                    // Server accepted the handshake
                    setConnectionStatus(true);
                    logln((char*)"Accepted!");
                    setDriveStatus(true);
                    setWeaponStatus(true);
                    pingServer();
                }
                break;
            case PING_RESPONDED:
                pinging = false;
                if (pingFailed) {
                    logln((char*)"Pinging Restored!");
                    pingFailed = false;
                }
                break;
            case DISABLE_WEAPON:
                disableWeapon();
                break;
            case ENABLE_WEAPON:
                enableWeapon();
                break;
            case DISABLE_DRIVE:
                disableDrive();
                break;
            case ENABLE_DRIVE:
                enableDrive();
                break;
            case SEND_LEFT:
                setLeftPower(message[1]);
                break;
            case SEND_RIGHT:
                setRightPower(message[1]);
                break;
            case SEND_WEAPON:
                setWeaponPower(message[1]);
                break;
            case ENABLE_AUTO:
                enableAuto();
                break;
            case DISABLE_AUTO:
                disableAuto();
                break;
        }
    }

    void sendMessage(int message) {
        client.write(message);
        client.write(';');
    }

    // Send a handshake to the server. Block until accepted
    void handshake() {
        if (!getConnectionStatus()) {
            if (!client.connected()) {
                logln((char*)"Lost Connection. Reconnecting...");
                connect();
            } else {
                logln((char*)"Sending Handshake...");
                sendMessage(HANDSHAKE_REQUEST);
                timerDelay(1000, [](){
                    acceptData();
                    timerDelay(HANDSHAKE_INTERVAL, &checkHandshake);
                });
            }
        }
    }

    void checkHandshake() {
        if (!getConnectionStatus()) {
            handshake();
        }
    }

    void pingServer() {
        if (getConnectionStatus()) {
            if (pinging) {
                onPingFail();
            } else {
                //flashLED(1, 50);
                sendMessage(PING_REQUEST);
                pinging = true;
            }
            timerDelay(PING_INTERVAL, &pingServer);
        }
    }

    void onPingFail() {
        pinging = false;
        if (pingFailed) {
            pingFailed = false;
            if (client.connected()) {
                logln((char*)"Server Unresponsive!");
                setConnectionStatus(false);
                handshake();
            } else {
                logln((char*)"Lost Connection!");
                connect();
            }
        } else {
            pingFailed = true;
            logln((char*)"Pinging Failed! Retrying...");
        }
    }
};

#endif