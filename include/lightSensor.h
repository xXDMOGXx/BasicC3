#ifndef CHESSBOT_LIGHT_SENSOR_H
#define CHESSBOT_LIGHT_SENSOR_H

namespace ChessBot
{
    void setupIR();
    void activateIR();
    void deactivateIR();
    std::array<int, 4> readLightLevels();
};

#endif