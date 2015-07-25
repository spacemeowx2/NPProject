#ifndef WORLDSCENE_H
#define WORLDSCENE_H

#include "scene.h"

class WorldScene:
    public Scene,
    virtual public EventReceiver
{
    public:
        WorldScene();
        virtual ~WorldScene();
        void onLoadRes(Game*);
        bool onUpdate();
        void onDraw(Render&);
        void onDestroyRes(Game*);
        void onMouseUp(int x, int y, int button);
        void onKeyUp(SDL_Keycode);
        void onPlayerDie();
    protected:
    private:
        bool quit;
};

#endif // WORLDSCENE_H