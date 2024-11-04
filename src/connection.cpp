#ifndef CHESSBOT_CONNECTION_CPP
#define CHESSBOT_CONNECTION_CPP

#include "connection.h"

#include "Arduino.h"
#include "logging.h"
#include "timer.h"
#include "control.h"
#include "status.h"
#include "../env.h"

#include "WiFi.h"

namespace ChessBot
{
    // These are the various different supported message types that can be sent over TCP
    enum MESSAGE_TYPE {
        HANDSHAKE_REQUEST,
        HANDSHAKE_RESPONSE,
        PING_REQUEST,
        PING_RESPONSE,
        QUERY_VAR,
        QUERY_RESPONSE,
        SET_VAR,
        TURN_BY_ANGLE,
        DRIVE_TILES,
        ACTION_SUCCESS,
        ACTION_FAIL,
        DRIVE_TANK,
        ESTOP,
    };

    WiFiClient client;
    bool pinging = false;
    bool pingFailed = false;
    
    void connect() {
        setConnectionStatus(false);
        logln((char*)"Connecting to Server...");
        if (!client.connect(SERVER_IP, SERVER_PORT)) {
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
            case HANDSHAKE_RESPONSE:
                if (!getConnectionStatus()) {
                    // Server accepted the handshake
                    setConnectionStatus(true);
                    logln((char*)"Accepted!");
                    pingServer();
                }
                break;
            case PING_RESPONSE:
                pinging = false;
                if (pingFailed) {
                    logln((char*)"Pinging Restored!");
                    pingFailed = false;
                }
                break;
            case DRIVE_TANK:
                drive(message[1], message[2]);
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