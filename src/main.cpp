#include "SDL.h"
#include "SDL_ttf.h"
#include "application.h"
#include <cstdlib>
#include <ctime>
#include <cstdio>
#include "random.h"

#include "lua.hpp"

#undef main
int main(int argc, char* argv[])
{
    lua_State* L;
    L = luaL_newstate();
    luaL_openlibs(L);
    luaL_dofile(L, "test.lua");
    lua_close(L);
    return 0;

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
    app.start();
    TTF_Quit();
    SDL_Quit();
    return 0;
}
