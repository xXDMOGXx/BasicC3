#ifndef CHESSBOT_CONTROL_H
#define CHESSBOT_CONTROL_H

namespace ChessBot
{
    void setupBot();
    void drive(float tiles);
    void drive(float leftPower, float rightPower);
    void stop();
    std::array<int, 4> returnLightLevels();
};

#endif