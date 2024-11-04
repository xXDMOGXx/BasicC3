#ifndef CHESSBOT_LIGHT_SENSOR_CPP
#define CHESSBOT_LIGHT_SENSOR_CPP

#include "lightSensor.h"

#include "Arduino.h"
#include "config.h"

namespace ChessBot
{
    void setupIR() {
        pinMode(RELAY_IR_LED_PIN, OUTPUT);
    }

    void activateIR() {
        digitalWrite(RELAY_IR_LED_PIN, HIGH);
    }

    void deactivateIR() {
        digitalWrite(RELAY_IR_LED_PIN, LOW);
    }

    std::array<int, 4> readLightLevels() {
        return { analogRead(PHOTODIODE_A_PIN), analogRead(PHOTODIODE_B_PIN), analogRead(PHOTODIODE_C_PIN), analogRead(PHOTODIODE_D_PIN)} ;
    }
};

#endif