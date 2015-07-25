#include "baseobject.h"
#include "game.h"
#include "render.h"

BaseObject::BaseObject(Game* game)
{
    mGame = game;
    mRen = &game->getRender();
    shouldUpdate = shouldDraw = true;
//    debugInfo=0;
}

BaseObject::~BaseObject()
{
    //dtor
}
