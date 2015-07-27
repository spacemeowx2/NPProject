#ifndef TITLESCENE_H
#define TITLESCENE_H

#include "eventreceiver.h"
#include "scene.h"
#include "ui/button.h"


class TitleScene:
    public Scene,
    virtual public EventReceiver,
    virtual Button::onClickListener
{
    public:
        TitleScene();
        virtual ~TitleScene();
        void onLoadRes(Game*);
        bool onUpdate();
        void onDraw(Render*);
        void onDestroyRes(Game*);
        bool onMouseUp(int x, int y, int button);
        void onClick(Button*);
    protected:
    private:
        SDL_Texture* mBackground;
        Button* btnStart;
        Button* btnQuit;
        Button* btnHelp;
        bool quit;
};
#endif // TITLESCENE_H
