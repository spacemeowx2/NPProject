#ifndef BULLET_H
#define BULLET_H

#include "baseobject.h"
class Tank;
class Game;

class Bullet : public BaseObject
{
    public:
        Bullet(Game*, Tank* o, double x, double y, double vx, double vy);
        virtual ~Bullet();
        Tank* getOwner() { return owner; }
        void onUpdate();
        void onDraw();
        double getPosX() { return posX; }
        double getPosY() { return posY; }
    protected:
    private:
        Tank* owner;
        double posX, posY;
        double vX, vY;
};

#endif // BULLET_H

