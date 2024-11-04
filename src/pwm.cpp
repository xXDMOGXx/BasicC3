#ifndef CHESSBOT_PWM_CPP
#define CHESSBOT_PWM_CPP

#include "pwm.h"

#include "Arduino.h"
#include "driver/ledc.h"
#include "config.h"

namespace ChessBot
{
    constexpr static uint8_t LEDC_DUTY_RES = 14;
    static uint16_t LEDC_DUTY_STEPS = pow(2, LEDC_DUTY_RES);
    constexpr static int16_t LEDC_FREQUENCY = 5000;

    void setupPWM(int pin, int channel) {
        ledcSetup(channel, LEDC_FREQUENCY, LEDC_DUTY_RES);
        ledcAttachPin(pin, channel);
    }

    void writePWM(int channel, int dutyCycle) {
        ledcWrite(channel, dutyCycle);
    }

    // Value between [0, 1]
    int mapPowerToDuty(float power) {
        return map(power, 0, 1, 0, LEDC_DUTY_STEPS);
    }
};

#endif