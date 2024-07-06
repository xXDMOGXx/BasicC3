#ifndef BOT_MOTOR_H
#define BOT_MOTOR_H

namespace Bot
{
    void setupMotors();
    void setLeftPower(int power);
    void setRightPower(int power);
    void setWeaponPower(int power);
};

#endif