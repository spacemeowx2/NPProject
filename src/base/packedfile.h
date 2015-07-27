#ifndef PACKETFILE_H
#define PACKETFILE_H
#include "SDL2/SDL.h"
#include <string>

SDL_RWops* pfOpenSDL_RWops(const char* fn);
std::string pfGetString(const char* fn);


#endif // PACKETFILE_H