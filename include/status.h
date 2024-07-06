#ifndef BOT_STATUS_H
#define BOT_STATUS_H

namespace Bot
{
    bool getAutoStatus();
    void setAutoStatus(bool value);

    bool getDriveStatus();
    void setDriveStatus(bool value);

    bool getWeaponStatus();
    void setWeaponStatus(bool value);

    bool getConnectionStatus();
    void setConnectionStatus(bool value);

    bool getLoggingStatus();
    void setLoggingStatus(bool value);
};

#endif