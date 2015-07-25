#include "aitank.h"
#include <cstdlib>

AITank::AITank(Game* game, double x, double y):
    Tank(game, x, y)
{
    //ctor
    timerCount=timerMax=0;
    cParam=0;
//    debugInfo=3;
    Tank::onKeyDown(TKEY_UP);
}

AITank::~AITank()
{
    //dtor
}

void AITank::onUpdate()
{
    Tank::onUpdate();
    if (rand() % 20<10)
    {
        Tank::onKeyDown(TKEY_SHOT);
    } else {
        Tank::onKeyUp(TKEY_SHOT);
    }
    if (timerCount++==timerMax)
    {
        timerCount=0;
        timerMax = 30+30.0*rand()/RAND_MAX;
        switch (state)
        {
        case 0:
            Tank::onKeyUp(cParam);
            break;
        case 1:
            break;
        }
        state = rand() % 2;
        switch (state)
        {
        case 0: //change direction
            if (rand()%2==0)
            {
                cParam = TKEY_LEFT;
            } else {
                cParam = TKEY_RIGHT;
            }
            Tank::onKeyDown(cParam);
            break;
        case 1: //do nothing
            break;
        }
    }
}
