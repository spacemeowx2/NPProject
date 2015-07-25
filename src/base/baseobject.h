#ifndef BASEOBJECT_H
#define BASEOBJECT_H
class Game;
class Render;

class BaseObject
{
    public:
        BaseObject(Game*);
        virtual ~BaseObject();
        virtual void onUpdate(){}
        virtual void onDraw(){}
        Game& getGame() { return *mGame; }
        Render& getRender() { return *mRen; }
        bool shouldUpdate;
        bool shouldDraw;
    protected:
    private:
        Render* mRen;
        Game* mGame;
};

#endif // BASEOBJECT_H
