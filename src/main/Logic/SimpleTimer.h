#ifndef TIMER_H
#define TIMER_H

#include <chrono>
#include "../dispatcher/Dispatcher.h"
#include "../Imports.h"

class SimpleTimer
{
    private:
        std::chrono::high_resolution_clock::time_point start_time;
        std::chrono::duration<double> paused_duration;
        bool is_paused;
        std::thread* stopStartHandler;
        Dispatcher *disp;
        void stopStartThread();
    public:
        SimpleTimer(Dispatcher *disp);
        void startTimer();
        void stopTimer();
        void resumeTimer();
        void resetTimer();
        double getTime();
};

#endif
