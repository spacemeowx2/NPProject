//请保持UTF8编码
//please keep UTF-8 encoding
#include "scene/titlescene.h"
#include "scene.h"
#include "game.h"
#include "ui/button.h"
#include "render.h"
#include "returncode.h"
#include <iostream>

using namespace std;

TitleScene::TitleScene()
{
    quit=false;
    setEventReceiver(this);
}

TitleScene::~TitleScene()
{
    //dtor
}

void TitleScene::onLoadRes(Game* game)
{
    Render& render = game->getRender();

    mBackground = render.loadImage("res/BattleCity.png");

    int winW = render.getWidth();
    btnStart = new Button(game, (winW-200)/2, 300, 200, 50);
    btnHelp = new Button(game, (winW-200)/2, 300+60, 200, 50);
    btnQuit = new Button(game, (winW-200)/2, 300+120, 200, 50);

    btnStart->setOnClickListener(this);
    btnStart->setText("开始游戏");
    btnHelp->setOnClickListener(this);
    btnHelp->setText("操作说明");
    btnQuit->setOnClickListener(this);
    btnQuit->setText("退出游戏");

    addObject(btnStart); //not need to delete
    addObject(btnHelp);
    addObject(btnQuit);
}

void TitleScene::onDestroyRes(Game* game)
{
    Render& render = game->getRender();
    render.destroyImage(mBackground);
}

bool TitleScene::onUpdate()
{
    updateAll();
    return !quit;
}

void TitleScene::onDraw(Render& render)
{
    //424*131
    render.drawImage(mBackground, (render.getWidth()-424)/2, 100, 424, 131);
    drawAll();
}

void TitleScene::onMouseUp(int x, int y, int button)
{
    //cout << x << " " << y << " " << button << endl;
}

void TitleScene::onClick(Button* btn)
{
    if (btn==btnStart)
    {
        cout << "start" << endl;
        setResult(RETURNCODE_NEXT);
    } else if (btn==btnQuit)
    {
        cout << "quit" <<endl;
        setResult(RETURNCODE_QUIT);
    } else if (btn==btnHelp)
    {
        cout << "help" << endl;
        setResult(RETURNCODE_HELP);
    }
    quit=true;
}
