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
        void onMouseMove(int x, int y);
        void onMouseDown(int x, int y, int button){if(button==1)isButtonDown=true;};
        void onMouseUp(int x, int y, int button);
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
};

#endif // BUTTON_H
