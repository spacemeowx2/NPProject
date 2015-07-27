#include "gamescene.h"
#include "returncode.h"
#include "game.h"
#include "game/tank.h"
#include "render.h"
#include "game/aitank.h"
#include <iostream>
#include <cstdlib>
#include <cmath>
using namespace std;
const int GROUP_PLAYER = 0;
const int GROUP_AI = 1;

template<typename T>
void removeFromVector(vector<T>* v, T i)
{
    typename vector<T>::iterator itr;
    for (itr = v->begin(); itr!=v->end(); itr++)
    {
        if (*itr == i)
        {
            v->erase(itr);
            break;
        }
    }
}

double mrand()
{
    return 1.0*rand()/RAND_MAX;
}

void GameScene::onPlayerDie()
{
    tankPlayer->die();
    tankPlayer->shouldUpdate = false;
    tankPlayer->shouldDraw = false;
    setResult(RETURNCODE_LOSE);
    quit=true;
}

GameScene::GameScene(int level)
{
    quit=false;
    setEventReceiver(this);
    mLevel = level;
}

GameScene::~GameScene()
{
    //dtor
}

void GameScene::onLoadRes(Game* game)
{
    Render* render = game->getRender();
    bX = bY = 20;
    bW = render->getWidth() - 40; // 右边留着显示信息
    bH = render->getHeight() - 40;

    tankPlayer = new Tank(game, bX + bW/2.0, bY + bH-TANK_HEIGHT/2.0);
    tankPlayer->setColor(0,255,0);
    tankPlayer->group = GROUP_PLAYER;
    tankPlayer->setListener(this);
    tankPlayer->HP=tankPlayer->MaxHP=3*mLevel;
    tankPlayer->showBar=true;
    game->addEventReceiver(tankPlayer);

    tanks.push_back(tankPlayer);
    addObject(tankPlayer);

    for (int i=0; i<mLevel*3+2; i++)
    {
        Tank* tTank = new AITank(game,
                                 mrand()*render->getWidth(),
                                 mrand()*render->getHeight());
        tTank->HP=tTank->MaxHP=3;
        tTank->showBar=true;
        tTank->group=GROUP_AI;
        tTank->setListener(this);
        tanks.push_back(tTank);
        addObject(tTank);
    }
    onUpdate();
}

void GameScene::onDestroyRes(Game* game)
{
    /*
    removeFromVector(tanks, tankPlayer);
    game->removeEventReceiver(tankPlayer);
    removeObject(tankPlayer);
    delete tankPlayer;
    */
    vector<Tank*>::iterator itr;
    for (itr=tanks.begin(); itr!=tanks.end(); itr++)
    {
        Tank* tTank = *itr;
        game->removeEventReceiver(tTank);
        removeObject(tTank);
        delete tTank;
    }
    tanks.clear();
}

void GameScene::removeBullet(Bullet* b)
{
    removeObject(b);
    removeFromVector(&bullets, b);
    delete b;
}

void GameScene::removeTank(Tank* t)
{
    removeObject(t);
    removeFromVector(&tanks, t);
    delete t;
}

bool GameScene::onUpdate()
{
    {
        vector<Bullet*>::iterator itr;
        for (itr = bullets.begin(); itr != bullets.end(); )
        {
            Bullet* b = *itr;
            double x = b->getPosX();
            double y = b->getPosY();
            if ((x<=bX) || (x>=bX+bW) || (y<=bY) || (y>=bY+bH))
            {
                removeBullet(b);
            } else {
                itr++;
            }
        }
    }
    {
        vector<Tank*>::iterator itr;
        for (itr = tanks.begin(); itr!=tanks.end();)
        {
            bool removed=false;
            Tank* tank = *itr;
            double tr = tank->getTestRadius();
            double x = tank->getPosX();
            double y = tank->getPosY();
            if (x<=bX+tr)
                tank->setPosX(bX+tr);
            if (x>=bX+bW-tr)
                tank->setPosX(bX+bW-tr);
            if (y<=bY+tr)
                tank->setPosY(bY+tr);
            if (y>=bY+bH-tr)
                tank->setPosY(bY+bH-tr);
            vector<Bullet*>::iterator bitr;
            for (bitr = bullets.begin(); bitr != bullets.end();)
            {
                Bullet* b=*bitr;
                if (!tank->isDead() && (b->getOwner()!=tank) && (tank->isHitByBullet(b)))
                {
                    int bGroup = b->getOwner()->group;
                    removeBullet(b);
                    //cout << "hit" << endl;
                    if (tank->group!=bGroup)
                    {
                        if (--tank->HP==0)
                        {
                            tank->die();
                            break;
                        }
                    }
                } else {
                    bitr++;
                }
            }
            if (!removed)
                itr++;
        }
    }
    {
        vector<Tank*>::iterator itr;
        vector<Tank*>::iterator itr2;
        for (itr = tanks.begin(); itr!=tanks.end();itr++)
        {
            for (itr2=itr+1; itr2!=tanks.end();itr2++)
            {
                Tank* t1 = *itr;
                Tank* t2 = *itr2;
                double tr1=t1->getTestRadius(),tr2=t2->getTestRadius();
                double x1=t1->getPosX(),y1=t1->getPosY();
                double x2=t2->getPosX(),y2=t2->getPosY();
                double d2=(x1-x2)*(x1-x2)+(y1-y2)*(y1-y2);
                if (d2<=pow(tr1+tr2,2))
                {
                    double cx=(x1+x2)/2, cy=(y1+y2)/2;
                    double d1=sqrt((x1-cx)*(x1-cx)+(y1-cy)*(y1-cy));
                    double uvx=(x1-cx)/d1, uvy=(y1-cy)/d1;
                    t1->setPosX(cx+uvx*tr1);
                    t1->setPosY(cy+uvy*tr1);
                    t2->setPosX(cx-uvx*tr2);
                    t2->setPosY(cy-uvy*tr2);
                }
            }
        }
    }

    updateAll();
    // collision detection
    return !quit;
}

void GameScene::onDraw(Render* render)
{
    drawAll();
    render->drawRect(bX, bY, bW, bH);
}

bool GameScene::onMouseUp(int x, int y, int button)
{
    //if (button == 2)
    //    quit = true;
    return false;
}

bool GameScene::onKeyUp(SDL_Keycode kc)
{
    if (kc == SDLK_ESCAPE)
        quit = true;
    return true;
}

void GameScene::onFire(Tank* tank, Bullet* new_bullet)
{
    bullets.push_back(new_bullet);
    addObject(new_bullet);
}

void GameScene::onDestroy(Tank* tank)
{
    if (tank==tankPlayer)
    {
        onPlayerDie();
    } else {
        removeTank(tank);
        if (tanks.size() == 1)
        {
            setResult(RETURNCODE_NEXT);
            quit=true;
        }
    }
}
