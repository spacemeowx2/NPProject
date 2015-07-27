#include "game.h"
#include "render.h"
#include "scene.h"
#include "scene/returncode.h"
#include <iostream>
#include <cstdlib>

using namespace std;

#define invokeEvent(method, ...) for(auto itr=mEventReceivers.begin(); \
    itr!=mEventReceivers.end(); itr++) if((*itr)->method(__VA_ARGS__)) break;

Game::Game(int w, int h)
{
    mRen = new Render(w, h);
    mouseX = mouseY=0;
}

Game::~Game()
{
    delete mRen;
    //dtor
}

void Game::addEventReceiver(EventReceiver* er)
{
    mEventReceivers.push_back(er);
}

void Game::removeEventReceiver(EventReceiver* er)
{
    vector<EventReceiver*>::iterator itr;
    for (itr = mEventReceivers.begin(); itr!=mEventReceivers.end(); itr++)
    {
        if ((*itr) == er)
        {
            mEventReceivers.erase(itr);
            break;
        }
    }
}

void Game::run(Scene* scene)
{
    //scene.onLoadRes(this);
    SDL_Event e;
    bool quit=false;
    EventReceiver* er = scene->getEventReceiver();
    if (er!=NULL)
        addEventReceiver(er);
    cout << mouseX << " " << mouseY << endl;;
    invokeEvent(onMouseMove, mouseX, mouseY);
    while(!quit)
    {
        while (SDL_PollEvent(&e) != 0)
        {
            switch (e.type)
            {
            case SDL_QUIT:
                quit=true;
                scene->setResult(RETURNCODE_QUIT);
                break;
            }
            switch (e.type)
            {
            case SDL_KEYDOWN:
                invokeEvent(onKeyDown, e.key.keysym.sym);
                break;
            case SDL_KEYUP:
                invokeEvent(onKeyUp, e.key.keysym.sym);
                break;
            case SDL_MOUSEBUTTONDOWN:
                invokeEvent(onMouseDown, e.button.x, e.button.y, e.button.button);
                break;
            case SDL_MOUSEBUTTONUP:
                invokeEvent(onMouseUp, e.button.x, e.button.y, e.button.button);
                break;
            case SDL_MOUSEMOTION:
                mouseX = e.motion.x;
                mouseY = e.motion.y;
                invokeEvent(onMouseMove, e.motion.x, e.motion.y);
                break;
            }
        }
        mRen->clear();
        if (!scene->onUpdate())
            quit=true;
        scene->onDraw(mRen);
        mRen->present();
        SDL_Delay(16);
    }
    if (er!=NULL)
        removeEventReceiver(er);
    //scene.onDestroyRes(this);
}

void Game::switchScene(Scene* s1, Scene* s2, int method)
{
    const double ANI_FRAME = 32.0;
    double cx=mRen->getWidth()/2, cy=mRen->getHeight()/2;
    if (method==-1)
        method=rand()%SWITCH_COUNT;
    SDL_Event e;
    SDL_Texture* t1 = mRen->createTargetTexture();
    SDL_Texture* t2 = mRen->createTargetTexture();
    mRen->setTarget(t2);
    s2->onDraw(mRen);
    for (int i = 0; i <= ANI_FRAME; i++) //about half a second
    {
        while (SDL_PollEvent(&e) != 0); //ignore all event

        mRen->setTarget(t1);
        mRen->clear();
        s1->onUpdate();
        s1->onDraw(mRen);
        mRen->setTarget(NULL);

        double scale = i/ANI_FRAME;
        mRen->clear();
        switch (method)
        {
        case SWITCH_FADE:
            SDL_SetTextureAlphaMod(t1, 255*(1-scale));
            SDL_SetTextureAlphaMod(t2, 255*scale);
            mRen->drawImage(t1, 0, 0);
            mRen->drawImage(t2, 0, 0);
            break;
        case SWITCH_POP:
            scale *= scale;
            SDL_SetTextureAlphaMod(t1, 255*(1-scale));
            SDL_SetTextureAlphaMod(t2, 255*scale);
            mRen->drawImage(t2,
                           (1-scale)*cx,
                           (1-scale)*cy,
                           scale*mRen->getWidth(),
                           scale*mRen->getHeight());
            mRen->drawImage(t1,
                            -(scale)*mRen->getWidth(),
                            -(scale)*mRen->getHeight(),
                            (1+2*scale)*mRen->getWidth(),
                            (1+2*scale)*mRen->getHeight());
            break;
        case SWITCH_PUSH:
            scale *= scale;
            mRen->drawImage(t1,(-scale)*mRen->getWidth(),0,
                           mRen->getWidth(),mRen->getHeight());
            mRen->drawImage(t2,(1-scale)*mRen->getWidth(),0,
                           mRen->getWidth(),mRen->getHeight());
            break;
        }

        mRen->present();
        SDL_Delay(16);
    }
}
