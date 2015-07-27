#ifndef TEXTSCENE_H
#define TEXTSCENE_H

#include "scene.h"
#include "eventreceiver.h"
class Font;
class Render;

const int LINE_LIMIT=10;

class TextScene:
    public Scene,
    virtual public EventReceiver
{
    public:
        TextScene(const char[], bool needClick = true, int size=100);
        virtual ~TextScene();
        void onLoadRes(Game*);
        void onDestroyRes(Game*);
        bool onUpdate();
        void onDraw(Render*);
        bool onMouseUp(int,int,int) {quit=true;};
        bool onKeyUp(SDL_Keycode) {quit=true;};
    protected:
    private:

        Font* font;
        SDL_Texture* textTexture[LINE_LIMIT];
        int textW[LINE_LIMIT], textH[LINE_LIMIT];
        int totalH;
        int lineCount;
        bool quit;
        char mText[1024];
        bool mNeedClick;
        int timeCount;
        int mSize;
};

#endif // TEXTSCENE_H
