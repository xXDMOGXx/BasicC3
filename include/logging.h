#ifndef CHESSBOT_LOGGING_H
#define CHESSBOT_LOGGING_H

namespace ChessBot
{
    void log(char message[]);
    void log(int value);

    void logln(char message[]);
    void logln(int value);

    void logError(char message[], int error);
};

#endif