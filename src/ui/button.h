#ifndef BUTTON_H
#define BUTTON_H

#include "baseobject.h"
#include "eventreceiver.h"
#include <string>
using std::string;
class Game;
class Render;
class Font;

class Button: public BaseObject, virtual public EventReceiver
{
    public:
        class onClickListener
        {
            public: virtual void onClick(Button*) {};
        };
        Button(Game*, int ix, int iy, int iw, int ih);
        virtual ~Button();
        bool onMouseMove(int x, int y);
        bool onMouseDown(int x, int y, int button);
        bool onMouseUp(int x, int y, int button);
        void onDraw();
        void setOnClickListener(onClickListener* l) {mListener=l;}
        void setText(string text) { mText=text; changeText(); }
        string getText() { return mText; }
    protected:
    private:
        void changeText();
        int x, y, w, h;
        bool isMouseIn, isButtonDown;
        onClickListener* mListener;
        string mText;
        SDL_Texture* textTexture;
        int textW, textH;
        Font* font;
        bool inRect(int, int);
};

#endif // BUTTON_H
