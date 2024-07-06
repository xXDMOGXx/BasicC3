#ifndef BOT_LOGGING_H
#define BOT_LOGGING_H

namespace Bot
{
    void log(char message[]);
    void log(int value);

    void logln(char message[]);
    void logln(int value);

    void logError(char message[], int error);
};

#endif