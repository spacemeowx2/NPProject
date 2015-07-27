#ifndef GAME_H
#define GAME_H

class Game;
#include "render.h"
#include "scene.h"
#include "eventreceiver.h"
#include <vector>
const int SWITCH_RANDOM=-1;
const int SWITCH_FADE=0;
const int SWITCH_POP=1;
const int SWITCH_PUSH=2;
const int SWITCH_COUNT=3;

using std::vector;

class Game
{
    public:
        Game(int, int);
        ~Game();
        void run(Scene*);
        void addEventReceiver(EventReceiver*);
        void removeEventReceiver(EventReceiver*);
        void switchScene(Scene*, Scene*,int method=SWITCH_RANDOM);
        Render* getRender() { return mRen; }
    protected:
    private:
        Render* mRen;
        vector<EventReceiver*> mEventReceivers;
        int mouseX, mouseY;
};

#endif // GAME_H
