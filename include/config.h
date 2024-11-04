#ifndef CHESSBOT_CONFIG_H
#define CHESSBOT_CONFIG_H

namespace ChessBot
{
    constexpr static gpio_num_t MOTOR_A_PIN1;
    constexpr static gpio_num_t MOTOR_A_PIN2;
    constexpr static gpio_num_t MOTOR_B_PIN1;
    constexpr static gpio_num_t MOTOR_B_PIN2;

    constexpr static gpio_num_t ENCODER_A_PIN1;
    constexpr static gpio_num_t ENCODER_A_PIN2;
    constexpr static gpio_num_t ENCODER_B_PIN1;
    constexpr static gpio_num_t ENCODER_B_PIN2;

    constexpr static gpio_num_t RELAY_IR_LED_PIN;
    constexpr static gpio_num_t PHOTODIODE_A_PIN;
    constexpr static gpio_num_t PHOTODIODE_B_PIN;
    constexpr static gpio_num_t PHOTODIODE_C_PIN;
    constexpr static gpio_num_t PHOTODIODE_D_PIN;

    static float_t MOTOR_A_DRIVE_MULTIPLIER;
    static float_t MOTOR_B_DRIVE_MULTIPLIER;

    static float_t ENCODER_MULTIPLIER;
};

#endif