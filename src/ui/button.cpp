#include "button.h"
#include "baseobject.h"
#include "eventreceiver.h"
#include "game.h"
#include "render.h"
#include "font.h"
#include <iostream>
using namespace std;

Button::Button(Game* game, int ix, int iy, int iw, int ih):
    BaseObject(game), x(ix), y(iy), w(iw), h(ih)
{
    textTexture = NULL;
    textW = textH = 0;
    isMouseIn=false;
    isButtonDown=false;
    getGame().addEventReceiver(this);

    font = new Font(20);
}

Button::~Button()
{
    delete font;
    getGame().removeEventReceiver(this);
}

bool Button::inRect(int mx, int my)
{
    if ((mx>=x) && (mx<=x+w))
    {
        if ((my>=y) && (my<=y+h))
        {
            return true;
        }
    }
    return false;
}

bool Button::onMouseDown(int mx, int my, int button)
{
    if(button==1 && inRect(mx, my))
    {
        isButtonDown = true;
    }
    return inRect(mx, my);
}

bool Button::onMouseMove(int mx, int my)
{
    isMouseIn = inRect(mx, my);
    return isMouseIn;
}

bool Button::onMouseUp(int x, int y, int button)
{
    if(button==1)
    {
        isButtonDown=false;
    }
    if(mListener && inRect(x, y) && button==1)
        mListener->onClick(this);
    return inRect(x, y);
}

void Button::onDraw()
{
    Render& render = getRender();
    if (isMouseIn)
    {
        if (isButtonDown)
            render.setDrawColor(150,150,150);
        else
            render.setDrawColor(200,200,200);
    }
    else
    {
        render.setDrawColor(175,175,175);
    }
    render.drawRect(x, y, w, h);
    render.fillRect(x, y, w, h);
    render.drawImage(textTexture, x+w/2-textW/2, y+h/2-textH/2,
                     textW, textH);
}

void Button::changeText()
{
    if (textTexture)
        SDL_DestroyTexture(textTexture);
    SDL_Surface* srfc = font->Render_Blended(mText, 255,255,255);
    if (srfc)
    {
        textTexture = getRender().createTextureFromSurface(srfc);
        textW = srfc->w;
        textH = srfc->h;
        SDL_FreeSurface(srfc);
    }
}
