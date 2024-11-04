#ifndef CHESSBOT_CONTROL_CPP
#define CHESSBOT_CONTROL_CPP

#include "control.h"

#include "Arduino.h"
#include "motor.h"
#include "lightSensor.h"

namespace ChessBot
{
    void setupBot() {
        setupMotors();
        setupIR();
        activateIR();
    }

    void drive(float tiles) {

    }

    void drive(float leftPower, float rightPower) {
        setLeftPower(leftPower);
        setRightPower(rightPower);
    }

    void stop() {
        setLeftPower(0);
        setRightPower(0);
    }

    std::array<int, 4> returnLightLevels() {
        return readLightLevels();
    }
};

#endif