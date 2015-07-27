#include "SDL2/SDL.h"
#include "SDL2/SDL_ttf.h"
#include "application.h"
#include <cstdlib>
#include <ctime>
#include <cstdio>
#include "random.h"

#include "packedfile.h"
#include "clua.h"
#include "lua.hpp"
#include "LuaBridge/LuaBridge.h"
#include "baseobject.h"

#undef main
int main(int argc, char* argv[])
{
    srand(time(NULL));
    if (SDL_Init(SDL_INIT_EVERYTHING)==-1)
    {
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error", "SDL_Init failed.", NULL);
        exit(-1);
    }
    if (TTF_Init()==-1)
    {
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error", "TTF_Init failed.", NULL);
        exit(-2);
    }
    
    Application app;

    /*
    CLua* l=new CLua();

    lua_State* L = l->getState();

    luabridge::push (L, &app);
    lua_setglobal (L, "app");

    l->doFile("lua/test.lua");
    if (l->getError())
        puts(l->getError());

    delete l;
    */
    app.start();
    TTF_Quit();
    SDL_Quit();
    return 0;
}
