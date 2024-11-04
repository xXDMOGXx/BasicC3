#ifndef CHESSBOT_STATUS_CPP
#define CHESSBOT_STATUS_CPP

#include "status.h"

namespace ChessBot
{
    bool connected = false;
    bool doLogging = true;

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