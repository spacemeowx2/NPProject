#ifndef GAMESCENE_H
#define GAMESCENE_H

class Render;
class Game;
#include "game/tank.h"
#include "scene.h"
#include "ui/button.h"
#include <vector>
using std::vector;
const int AI_COUNT = 20;

class GameScene:
    public Scene,
    virtual public EventReceiver,
    virtual Tank::onTankEventListener
{
    public:
        GameScene(int level=1);
        virtual ~GameScene();
        void onLoadRes(Game*);
        bool onUpdate();
        void onDraw(Render*);
        void onDestroyRes(Game*);
        bool onMouseUp(int x, int y, int button);
        bool onKeyUp(SDL_Keycode);
        void onFire(Tank*, Bullet*);
        void onPlayerDie();
        void onDestroy(Tank*);
    protected:
    private:
        bool quit;
        Tank* tankPlayer;
        int bX, bY, bW, bH; //边界
        vector<Tank*> tanks;
        vector<Bullet*> bullets;
        Game* mGame;
        void removeBullet(Bullet* b);
        void removeTank(Tank* t);
        int mLevel;
};

#endif // GAMESCENE_H
