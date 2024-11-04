#ifndef CHESSBOT_STATUS_H
#define CHESSBOT_STATUS_H

namespace ChessBot
{
    bool getConnectionStatus();
    void setConnectionStatus(bool value);

    bool getLoggingStatus();
    void setLoggingStatus(bool value);
};

#endif