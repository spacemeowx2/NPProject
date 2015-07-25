#ifndef FONT_H
#define FONT_H
#include <string>
#include "SDL_ttf.h"
using namespace std;

class Font
{
    public:
        Font(const char fileName[], int ptSize);
        Font(int ptSize);
        SDL_Surface* Render_Blended(string& text, SDL_Color fg);
        SDL_Surface* Render_Blended(string& text, Uint8 r, Uint8 g, Uint8 b, Uint8 a=255)
            {SDL_Color c={r,g,b,a};return Render_Blended(text, c);}
        SDL_Surface* Render_Blended(const char text[], SDL_Color fg);
        SDL_Surface* Render_Blended(const char text[], Uint8 r, Uint8 g, Uint8 b, Uint8 a=255)
            {SDL_Color c={r,g,b,a};return Render_Blended(text, c);}
        virtual ~Font();
    protected:
    private:
        TTF_Font *font;
};

#endif // FONT_H
