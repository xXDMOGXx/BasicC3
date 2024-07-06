#ifndef BOT_STATUS_CPP
#define BOT_STATUS_CPP

#include "status.h"

namespace Bot
{
    bool autoEnabled = true;
    bool driveEnabled = true;
    bool weaponEnabled = true;
    bool connected = false;
    bool doLogging = true;

    bool getAutoStatus() {
        return autoEnabled;
    }
    void setAutoStatus(bool value) {
        autoEnabled = value;
    }

    bool getDriveStatus() {
        return driveEnabled;
    }
    void setDriveStatus(bool value) {
        driveEnabled = value;
    }

    bool getWeaponStatus() {
        return weaponEnabled;
    }
    void setWeaponStatus(bool value) {
        weaponEnabled = value;
    }

    bool getConnectionStatus() {
        return connected;
    }
    void setConnectionStatus(bool value) {
        connected = value;
    }

    bool getLoggingStatus() {
        return doLogging;
    }
    void setLoggingStatus(bool value) {
        doLogging = value;
    }
};

#endif