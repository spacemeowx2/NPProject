#ifndef SCENE_H
#define SCENE_H

#include <eventreceiver.h>
#include <SDL2/SDL.h>
#include <vector>
using std::vector;

class Game;
class Render;
class BaseObject;

class Scene
{
    public:
        Scene();
        virtual ~Scene();
        virtual bool onUpdate(){return false;};
        virtual void onDraw(Render*){};
        virtual void onLoadRes(Game*){};
        virtual void onDestroyRes(Game*){};
        EventReceiver* getEventReceiver();
        void setEventReceiver(EventReceiver*);
        void updateAll();
        void drawAll();
        void addObject(BaseObject* obj);
        void removeObject(BaseObject* obj);

        void setResult(int r) { result=r; }
        int getResult() { return result; }
    protected:
        vector<BaseObject*> mObjects;
    private:
        EventReceiver* mEventReceiver;
        int result;
        bool isInUpdating;
        vector<BaseObject*> mToInsert;
        vector< vector<BaseObject*>::iterator > mToRemove;
};

#endif // SCENE_H
