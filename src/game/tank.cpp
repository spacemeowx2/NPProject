#include <iostream>
#include <cmath>
#include "tank.h"
#include "render.h"
#include "bullet.h"

using namespace std;
const double Tank::PI = 3.1415926535;
#undef PIPEFOLLOWMOUSE
/*Tank::Tank(Game* game, double _pipe_h,double _pipe_w,double _movingAngle):
    BaseObject(game), pipe_h(_pipe_h), pipe_w(_pipe_w) ,movingAngle(_movingAngle)
{
    Render& render = getRender();
    pic_tank = render.loadImage("res/tank.png");
}*/

Tank::Tank(Game* game, double x, double y):
    BaseObject(game), posX(x), posY(y)
{
    init();
    //Render& render = getRender();
    //pic_tank = render.loadImage("res/tank.png");
//    debugInfo=1;
}

void Tank::init()
{
    showBar=false;
    cR=cG=cB=255;

    mIsDead = false;
    HP = 3;
    group = 0;
    fireCount = 0;
    fireInterval = 15;

    hW = TANK_WIDTH / 2.0;
    hH = TANK_HEIGHT / 2.0;
    //vX = vY = 0;
    v=0;
    headAngle = -PI / 2;
    pipeX = 0;
    pipeY = -1;

    mouseX = posX;
    mouseY = 0;

    firing = false;

    keyUp = keyLeft = keyRight = keyDown = keyShot = false;

    mListener = NULL;

    tR = 28.28;
    testRadius = 24.14;
}


Tank::~Tank()
{
    //getRender().destroyImage(pic_tank);
    //dtor
}

void Tank::onDraw()
{
    Render& render = getRender();
    render.setDrawColor(cR,cG,cB);
    if (mIsDead)
    {
        double tnR;
        if (dieAniIndex<10)
        {
            tnR = tR*(1-dieAniIndex/10.0);
        } else {
            tnR = tR*3*(dieAniIndex-10)/10.0;
        }
        if (dieAniIndex<=20)
        {
            double tX = cos(headAngle-PI/4) * tnR;
            double tY = sin(headAngle-PI/4) * tnR;
            render.drawLine(posX+tX, posY+tY, posX-tY, posY+tX);
            render.drawLine(posX-tY, posY+tX, posX-tX, posY-tY);
            render.drawLine(posX-tX, posY-tY, posX+tY, posY-tX);
            render.drawLine(posX+tY, posY-tX, posX+tX, posY+tY);
        }
    } else {
        if (showBar)
        {

            render.drawRect(posX-TANK_WIDTH/2, posY-tR-4, TANK_WIDTH, 4);
            render.fillRect(posX-TANK_WIDTH/2, posY-tR-4, TANK_WIDTH*HP/MaxHP, 4);
        }
        double tX = cos(headAngle-PI/4) * tR;
        double tY = sin(headAngle-PI/4) * tR;
        render.drawLine(posX+tX, posY+tY, posX-tY, posY+tX);
        render.drawLine(posX-tY, posY+tX, posX-tX, posY-tY);
        render.drawLine(posX-tX, posY-tY, posX+tY, posY-tX);
        render.drawLine(posX+tY, posY-tX, posX+tX, posY+tY);
#ifdef PIPEFOLLOWMOUSE
        render.drawLine(posX, posY, posX+cos(headAngle) * 20, posY+sin(headAngle)*20);
        render.drawLine(posX, posY, posX+pipeX*40, posY+pipeY*40);
#else
        render.drawLine(posX, posY, posX+cos(headAngle)*35, posY+sin(headAngle)*35);
#endif // PIPEFOLLOWMOUSE
    }

}

void Tank::onUpdate()
{
    const double ANGLESTEP = PI/60;
#ifdef PIPEFOLLOWMOUSE
    pipeX = mouseX-posX;
    pipeY = mouseY-posY;
    double d = sqrt(pipeX*pipeX + pipeY*pipeY);
    pipeX /= d;
    pipeY /= d;
#endif // PIPEFOLLOWMOUSE
    if (mIsDead)
    {
        dieAniIndex++;
        if (dieAniIndex>=20 && mListener)
            mListener->onDestroy(this);
    } else {
        if ((fireCount++>fireInterval) && keyShot)
        {
            fire();
            fireCount=0;
        }
        if (keyLeft)
            headAngle-=ANGLESTEP;
        if (keyRight)
            headAngle+=ANGLESTEP;
        if (keyUp)
            v += 1.0;
        if (keyDown)
            v -= 1.0;
        v *= 0.7;
        double headX, headY;
        headX = cos(headAngle);
        headY = sin(headAngle);

        posX += v*headX;
        posY += v*headY;
    }
}

bool Tank::onKeyDown(SDL_Keycode kc)
{
    switch(kc)
    {
    case TKEY_UP:
        keyUp = true;
        break;
    case TKEY_LEFT:
        keyLeft = true;
        break;
    case TKEY_RIGHT:
        keyRight = true;
        break;
    case TKEY_DOWN:
        keyDown = true;
        break;
    case TKEY_SHOT:
        keyShot = true;
        break;
    }
    return true;
}

bool Tank::onKeyUp(SDL_Keycode kc)
{
    switch(kc)
    {
    case TKEY_UP:
        keyUp = false;
        break;
    case TKEY_LEFT:
        keyLeft = false;
        break;
    case TKEY_RIGHT:
        keyRight = false;
        break;
    case TKEY_DOWN:
        keyDown = false;
        break;
    case TKEY_SHOT:
        keyShot = false;
        break;
    default:
        return false;
        break;
    }
    return true;
}

bool Tank::onMouseMove(int x, int y)
{
    mouseX = x;
    mouseY = y;
    return false;
}

bool Tank::onMouseUp(int x, int y, int button)
{
    if (button==1)
        keyShot=false;
    return false;
}

bool Tank::onMouseDown(int x, int y, int button)
{
    if (button==1)
        keyShot=true;
    return false;
}

void Tank::fire(int vl)
{
    const int v = 5;
#ifndef PIPEFOLLOWMOUSE
    pipeX = cos(headAngle);
    pipeY = sin(headAngle);
#endif // PIPEFOLLOWMOUSE
    Bullet* bullet = new Bullet(&getGame(), this, posX+pipeX*40, posY+pipeY*40, pipeX*v, pipeY*v);
    // fire
    if (mListener)
        mListener->onFire(this, bullet);
}

double calcSquare(double x1,double y1,
                  double x2,double y2,
                  double x3,double y3)
{
    return abs(x1*(y2-y3)+x2*(y3-y1)+x3*(y1-y2))*0.5;
}
bool Tank::isHitByBullet(Bullet* b)
{
    double x = b->getPosX(), y = b->getPosY();

    double tX = cos(headAngle-PI/4) * tR;
    double tY = sin(headAngle-PI/4) * tR;
    double x1=posX+tX, y1=posY+tY;
    double x2=posX-tY, y2=posY+tX;
    double x3=posX-tX, y3=posY-tY;
    double x4=posX+tY, y4=posY-tX;

    double s=
        calcSquare(x,y,x1,y1,x2,y2)+
        calcSquare(x,y,x2,y2,x3,y3)+
        calcSquare(x,y,x3,y3,x4,y4)+
        calcSquare(x,y,x1,y1,x4,y4);
    return abs(s-TANK_HEIGHT*TANK_WIDTH)<4;
}

void Tank::die()
{
    if (mListener)
        mListener->onDie(this);
    mIsDead = true;
    dieAniIndex=0;
}
