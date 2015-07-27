#ifndef BASEOBJECT_H
#define BASEOBJECT_H

class BaseObject;
#include "game.h"
#include "render.h"
#include <cstdint>

class BaseObject
{
    public:
        BaseObject(Game*);
        virtual ~BaseObject();
        virtual void onUpdate(){}
        virtual void onDraw(){}
        Game& getGame() { return *mGame; }
        Render& getRender() { return *mRen; }
        bool shouldUpdate;
        bool shouldDraw;
        int64_t posX, posY; //The center point of object
    protected:
    private:
        Render* mRen;
        Game* mGame;
};

#endif // BASEOBJECT_H
