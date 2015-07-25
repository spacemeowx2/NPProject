#ifndef EVENTRECEIVER_H
#define EVENTRECEIVER_H

#include "SDL.h"

class EventReceiver
{
    public:
        virtual void onKeyDown(SDL_Keycode){};
        virtual void onKeyUp(SDL_Keycode){};
        virtual void onMouseMove(int x, int y){};
        virtual void onMouseDown(int x, int y, int button){};
        virtual void onMouseUp(int x, int y, int button){};
    protected:
    private:
};

#endif // EVENTRECEIVER_H
