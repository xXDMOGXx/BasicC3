#ifndef CHESSBOT_CONNECTION_H
#define CHESSBOT_CONNECTION_H

#include "Arduino.h"

namespace ChessBot
{
    void connect();
    void disconnect();
    void connectionTest();

    void acceptData();
    void decodeMessage(std::array<byte, 32> message, std::array<int, 32>& buffer, int len);
    void handleMessage(std::array<int, 32>& message);

    void sendMessage(int message);

    void handshake();
    void checkHandshake();

    void pingServer();
    void onPingFail();
};

#endif