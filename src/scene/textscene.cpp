#include "textscene.h"
#include "font.h"
#include "game.h"
#include "render.h"
#include <cstring>
#include <iostream>
using namespace std;

TextScene::TextScene(const char text[], bool needClick, int size)
{
    quit=false;
    setEventReceiver(this);
    strcpy(mText, text);
    mNeedClick = needClick;
    timeCount=0;
    mSize = size;
}

void TextScene::onLoadRes(Game* game)
{
    font = new Font(mSize);
    char tmpText[1024];
    char* pText;
    char* pLine=tmpText;
    int line=0;
    totalH=0;
    for (pText=mText; ; pText++)
    {
        if ((*pText=='\n') || (*pText==0))
        {
            *pLine=0;
            pLine=tmpText;
            SDL_Surface* srfc = font->Render_Blended(tmpText, 255,255,255);
            if (srfc)
            {
                textTexture[line] = game->getRender()->createTextureFromSurface(srfc);
                textW[line] = srfc->w;
                textH[line] = srfc->h;
                totalH+=srfc->h;
                SDL_FreeSurface(srfc);
            }
            line++;
            if (*pText==0)
                break;
        }
        if (*pText!='\n')
            *pLine++ = *pText;
    }
    lineCount = line;
    cout << lineCount << endl;
}

void TextScene::onDestroyRes(Game* game)
{
    for (int i=0; i<lineCount; i++)
        game->getRender()->destroyImage(textTexture[i]);
}

void TextScene::onDraw(Render* render)
{
    int fH = (render->getHeight()-totalH)/2;
    for (int i=0; i<lineCount; i++)
    {
        render->drawImage(textTexture[i],
                         (render->getWidth()-textW[i])/2,
                         fH,
                         textW[i], textH[i]);
        fH += textH[i];
    }
}

TextScene::~TextScene()
{
    //dtor
}

bool TextScene::onUpdate()
{
    timeCount++;
    if (!mNeedClick && timeCount>=60)
    {
        quit=true;
    }
    return !quit;
}
