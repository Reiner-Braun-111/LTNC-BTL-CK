#ifndef _TIME
#define _TIME

#include <SDL2/SDL.h>
#include <string>
#include <sstream>

using namespace std;

class Timer {
    private:
        Uint32 tick_start;
        Uint32 tick_pause;
        bool isStarted;
        bool isPaused;
    public:
        Timer();
        void start();
        void stop();
        void pause();
        void unpause();
        Uint32 getTicks();
        int getState();
        bool countDown(int amount);
        string getClockCount();
};

#endif
