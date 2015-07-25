#include "bullet.h"
#include "tank.h"
#include "render.h"

Bullet::Bullet(Game* game, Tank* o, double x, double y, double vx, double vy):
    BaseObject(game), owner(o), posX(x), posY(y), vX(vx), vY(vy)
{
//    debugInfo=2;
}

Bullet::~Bullet()
{
    //dtor
}

void Bullet::onUpdate()
{
    posX += vX;
    posY += vY;
}

void Bullet::onDraw()
{
    getRender().drawRect(posX-2, posY-2, 2, 2);
}
