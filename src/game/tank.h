#ifndef TANK_H
#define TANK_H
#include "baseobject.h"
#include "SDL.h"
#include "eventreceiver.h"
#include "bullet.h"
const int TANK_HEIGHT = 40;
const int TANK_WIDTH = 40;
#define WSAD
#ifdef WSAD
const int TKEY_UP = SDLK_w;
const int TKEY_LEFT = SDLK_a;
const int TKEY_RIGHT = SDLK_d;
const int TKEY_DOWN = SDLK_s;
const int TKEY_SHOT = SDLK_SPACE;
#else
const int TKEY_UP = SDLK_UP;
const int TKEY_LEFT = SDLK_LEFT;
const int TKEY_RIGHT = SDLK_RIGHT;
const int TKEY_DOWN = SDLK_DOWN;
const int TKEY_SHOT = SDLK_SPACE;
#endif // WSAD
class Tank:
    public BaseObject,
    virtual public EventReceiver
{
    public:
        class onTankEventListener
        {
        public:
            virtual void onFire(Tank*, Bullet*) {};
            virtual void onDestroy(Tank*) {};
            virtual void onDie(Tank*) {};
        };
        const static double PI;
        //Tank(Game* game, double _pipe_h,double _pipe_w ,double _movingAngle=0);
        Tank(Game* game, double x, double y);
        virtual ~Tank();
        /*MOVEMENT*/
        void Move();
        double getPosX() { return posX; }
        double getPosY() { return posY; }
        void setPosX(double val) { posX = val; }
        void setPosY(double val) { posY = val; }
        void fire(int vl=1);
        void die();
        void onDraw();
        void onUpdate();
        void onKeyDown(SDL_Keycode kc);
        void onKeyUp(SDL_Keycode kc);
        void onMouseMove(int x, int y);
        void onMouseDown(int x, int y, int button);
        void onMouseUp(int x, int y, int button);
        void setListener(onTankEventListener* l) {mListener=l;}
        bool isHitByBullet(Bullet*);
        bool isDead() {return mIsDead; }
        double getTestRadius() {return testRadius;}
        int HP;
        int MaxHP;
        int group;
        bool showBar;
        void setColor(Uint8 r, Uint8 g, Uint8 b) {cR=r;cG=g;cB=b;}
    protected:
    private:
        void init();
        bool mIsDead;
        float hW, hH; //half of width and height
        double posX, posY;//position center
        double headAngle; //facing where
        double pipeX, pipeY; //where to shot, unit vector
        double mouseX, mouseY; //the position of mouse point
        double v; //speed
        bool canShoot;
        int speed;
        SDL_Texture* pic_tank;
        int fireInterval;
        int fireCount;
        bool keyUp, keyLeft, keyRight, keyDown, keyShot;
        bool firing;
        onTankEventListener* mListener;
        double tR;
        double testRadius;
        Uint8 cR, cG, cB;
        int dieAniIndex;
};
#endif // TANK_H
