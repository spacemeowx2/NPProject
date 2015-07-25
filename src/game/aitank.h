#ifndef AITANK_H
#define AITANK_H

#include <game/tank.h>


class AITank : public Tank
{
    public:
        AITank(Game* game, double x, double y);
        void onUpdate();
        virtual ~AITank();
    protected:
    private:
        int timerCount;
        int timerMax;
        int state;
        int cParam;
};

#endif // AITANK_H
