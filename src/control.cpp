#ifndef BOT_CONTROL_CPP
#define BOT_CONTROL_CPP

#include "control.h"

#include "Arduino.h"
#include "logging.h"
#include "motor.h"
#include "status.h"

namespace Bot
{
    void enableWeapon() {
        setWeaponStatus(true);
        setWeaponPower(-100);
        logln((char*)"Weapon Enabled!");
    }

    void disableWeapon() {
        setWeaponPower(-100);
        setWeaponStatus(false);
        logln((char*)"Weapon Disabled!");
    }

    void enableDrive() {
        setDriveStatus(true);
        setLeftPower(0);
        setRightPower(0);
        logln((char*)"Drive Enabled!");
    }

    void disableDrive() {
        setLeftPower(0);
        setRightPower(0);
        setDriveStatus(false);
        logln((char*)"Drive Disabled!");
    }

    void enableAuto() {
        enableWeapon();
        enableDrive();
        setAutoStatus(true);
        logln((char*)"Autonomous Enabled!");
    }

    void disableAuto() {
        disableWeapon();
        disableDrive();
        setAutoStatus(false);
        logln((char*)"Autonomous Disabled!");
    }
};

#endif