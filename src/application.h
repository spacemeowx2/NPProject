#ifndef APPLICATION_H
#define APPLICATION_H

class Game;
class Render;

class Application
{
    public:
        Application();
        virtual ~Application();
        unsigned int GetCounter() { return m_Counter; }
        void SetCounter(unsigned int val) { m_Counter = val; }
        void start();
    protected:
    private:
        unsigned int m_Counter;
        Render* mRen;
        Game* mGame;

};

#endif // APPLICATION_H
