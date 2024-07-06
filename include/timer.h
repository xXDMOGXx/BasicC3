#ifndef BOT_TIMER_H
#define BOT_TIMER_H

#include <vector>

namespace Bot
{
    using TimerCallback = void (*)();
    struct Timer {
        bool oneOff;
        int delay;
        unsigned long lastMillis;
        TimerCallback func;
    };

    Timer timerDelay(int delay, TimerCallback func);
    Timer timerInterval(int interval, TimerCallback func);

    void timerCancel(size_t index);
    void timerCancelAll();

    void timerStep();
};

#endif