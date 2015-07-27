#include "font.h"
#include "SDL2/SDL_ttf.h"

Font::Font(const char fileName[], int ptSize)
{
    font = TTF_OpenFont(fileName, ptSize);
}

Font::Font(int ptSize)
{
    font = TTF_OpenFont("res/FZYTK.TTF", ptSize);
}

Font::~Font()
{
    TTF_CloseFont(font);
}

SDL_Surface* Font::Render_Blended(string& text, SDL_Color fg)
{
    return TTF_RenderUTF8_Blended(font, text.c_str(), fg);
}

SDL_Surface* Font::Render_Blended(const char text[], SDL_Color fg)
{
    return TTF_RenderUTF8_Blended(font, text, fg);
}
