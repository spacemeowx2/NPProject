#include "scene.h"
#include "render.h"
#include "eventreceiver.h"
#include "game.h"
#include "baseobject.h"
#include "scene/returncode.h"
#include <iostream>
#include <algorithm>
using namespace std;

Scene::Scene()
{
    mEventReceiver = NULL;
    setResult(RETURNCODE_NONE);
    isInUpdating=false;
}

Scene::~Scene()
{
    vector<BaseObject*>::iterator itr;
    for (itr = mObjects.begin(); itr!=mObjects.end(); itr++)
    {
        delete *itr;
    }
    mObjects.clear();
}

EventReceiver* Scene::getEventReceiver()
{
    return mEventReceiver;
}

void Scene::setEventReceiver(EventReceiver* er)
{
    mEventReceiver = er;
}

void Scene::updateAll()
{
    isInUpdating=true;
    vector<BaseObject*>::iterator itr;
    for (itr = mObjects.begin(); itr!=mObjects.end(); itr++)
    {
        if ((*itr)->shouldUpdate)
            (*itr)->onUpdate();
    }
    isInUpdating=false;
    if (mToInsert.size()>0)
    {
        mObjects.insert(mObjects.end(),
                        mToInsert.begin(),
                        mToInsert.end());
        mToInsert.clear();
    }
    if (mToRemove.size()>0)
    {
        for (unsigned int i=0; i<mToRemove.size(); i++)
        {
            mObjects.erase(mToRemove[i]);
        }
        mToRemove.clear();
    }
}

void Scene::drawAll()
{
    vector<BaseObject*>::iterator itr;
    for (itr = mObjects.begin(); itr!=mObjects.end(); itr++)
    {
        if ((*itr)->shouldDraw)
            (*itr)->onDraw();
    }
}

void Scene::addObject(BaseObject* obj)
{
    if (isInUpdating)
    {
        mToInsert.push_back(obj);
    } else {
        mObjects.push_back(obj);
    }
}

void Scene::removeObject(BaseObject* obj)
{
    vector<BaseObject*>::iterator itr;
    for (itr = mObjects.begin(); itr!=mObjects.end(); itr++)
    {
        if ((*itr)==obj)
        {
            if (isInUpdating)
            {
                mToRemove.push_back(itr);
            } else {
                mObjects.erase(itr);
            }
            break;
        }
    }
}
