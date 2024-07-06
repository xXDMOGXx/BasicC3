#ifndef BOT_MOTOR_CPP
#define BOT_MOTOR_CPP

#include "motor.h"

#include "Arduino.h"
#include "status.h"

namespace Bot
{
    void setupMotors() {
        // Any setup needed to get motors working
    }

    void setLeftPower(int power) {
        if (getDriveStatus()) {
            // Code needed to turn left motor
        }
    }

    void setRightPower(int power) {
        if (getDriveStatus()) {
            // Code needed to turn right motor
        }
    }

    void setWeaponPower(int power) {
        if (getWeaponStatus()) {
            // Code needed to turn weapon motor
        }
    }
};

#endif