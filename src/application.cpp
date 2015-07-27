#include "application.h"
#include "scene/titlescene.h"
#include "render.h"
#include "game.h"
#include "scene/returncode.h"
#include "scene/gamescene.h"
#include "scene/textscene.h"
#include <iostream>
#include <string>
#include <cstdlib>
#include <cstdio>
using namespace std;

Application::Application()
{
    mGame = new Game(1024, 600);
}

Application::~Application()
{
    //dtor

    delete mGame;
}

void Application::start()
{
    Scene* currentScene = new TitleScene;
    currentScene->onLoadRes(mGame);
    int level=0;
    int switchMethod=SWITCH_RANDOM;
    while (currentScene)
    {
        Scene* nextScene = NULL;
        mGame->run(currentScene);
        switch (currentScene->getResult())
        {
        case RETURNCODE_QUIT:
            //quit

            break;
        case RETURNCODE_BEGIN:
            nextScene = new GameScene(level);
            break;
        case RETURNCODE_NEXT:
            char ls[50];
            level++;
            sprintf(ls, "%d", level);
            nextScene = new TextScene((string("第")+ls+"关").c_str(), false);
            nextScene->setResult(RETURNCODE_BEGIN);
            break;
        case RETURNCODE_LOSE:
            level=0;
            nextScene = new TextScene("GAME OVER");
            break;
        case RETURNCODE_HELP:
            nextScene = new TextScene("操作说明:\nW,S,A,D控制坦克前进, 后退\n左右 旋转, 空格键或鼠标左\n键发射子弹",true, 60);
            break;
        default:
            nextScene = new TitleScene();
            break;
        }
        if (nextScene)
        {
            nextScene->onLoadRes(mGame);
            //switching scene
            mGame->switchScene(currentScene, nextScene);
        }

        currentScene->onDestroyRes(mGame);
        delete currentScene;
        currentScene = nextScene;
    }
}
