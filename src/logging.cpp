#ifndef CHESSBOT_LOGGING_CPP
#define CHESSBOT_LOGGING_CPP

#include "logging.h"

#include "Arduino.h"
#include "status.h"

namespace ChessBot
{
    void log(char message[]) {
        if (getLoggingStatus()) {
            Serial.print(message);
        }
    }

    void log(int value) {
        if (getLoggingStatus()) {
            Serial.print(value);
        }
    }

    void logln(char message[]) {
        if (getLoggingStatus()) {
            Serial.println(message);
        }
    }

    void logln(int value) {
        if (getLoggingStatus()) {
            Serial.println(value);
        }
    }

    void logError(char message[], int error) {
        if (getLoggingStatus()) {
            Serial.printf(message, error);
        }
    }
};

#endif