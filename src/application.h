#ifndef APPLICATION_H
#define APPLICATION_H

class Application;
#include "game.h"

class Application
{
    public:
        Application();
        virtual ~Application();
        void start();
    protected:
    private:
        Game* mGame;

};

#endif // APPLICATION_H
