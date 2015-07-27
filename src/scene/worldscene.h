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
        bool onMouseUp(int x, int y, int button);
        bool onKeyUp(SDL_Keycode);
    protected:
    private:
        bool quit;
};

#endif // WORLDSCENE_H