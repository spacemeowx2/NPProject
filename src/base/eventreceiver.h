#ifndef EVENTRECEIVER_H
#define EVENTRECEIVER_H

#include "SDL2/SDL.h"

class EventReceiver
{
    public:
        virtual bool onKeyDown(SDL_Keycode){ return false; };
        virtual bool onKeyUp(SDL_Keycode){ return false; };
        virtual bool onMouseMove(int x, int y){ return false; };
        virtual bool onMouseDown(int x, int y, int button){ return false; };
        virtual bool onMouseUp(int x, int y, int button){ return false; };
    protected:
    private:
};

#endif // EVENTRECEIVER_H
