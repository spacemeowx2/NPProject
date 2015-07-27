#include "clua.h"

#include "lua.hpp"
#include "LuaBridge/LuaBridge.h"


#include "baseobject.h"
#include "application.h"
#include "game.h"

using namespace luabridge;

void CLua::declareClass2Lua()
{
    luabridge::getGlobalNamespace(L)
        .beginClass<Application> ("Application")
        	.addConstructor <void (*) (void)> ()
            .addFunction("start", &Application::start)
        .endClass ()
        .beginClass<Game> ("Game")
        	.addConstructor <void (*) (int, int)> ()
        	.addFunction("run", &Game::run)
        .endClass ()
        .beginClass<BaseObject> ("BaseObject")
        	.addConstructor <void (*) (Game*)> ()
        	.addFunction("onUpdate", &BaseObject::onUpdate)
        	.addFunction("onDraw", &BaseObject::onDraw)
        	.addFunction("getGame", &BaseObject::getGame)
        	.addFunction("getRender", &BaseObject::getRender)
        	.addData("shouldUpdate", &BaseObject::shouldUpdate)
        	.addData("shouldDraw", &BaseObject::shouldDraw)
        .endClass ()
    ;

}