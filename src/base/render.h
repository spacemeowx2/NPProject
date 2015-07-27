#ifndef RENDER_H
#define RENDER_H
#include <string>
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"

using std::string;
class Render
{
    public:
        Render(int width, int height);
        virtual ~Render();
        int getWidth() { return mWidth; }
        int getHeight() { return mHeight; }
        SDL_Texture* createTextureFromSurface(SDL_Surface* surface);
        SDL_Texture* createTargetTexture();
        void setTarget(SDL_Texture* target);
        SDL_Texture* getTarget();
        void setDrawColor(Uint8 R, Uint8 G, Uint8 B, Uint8 A=255);
        void setBackground(Uint8 R, Uint8 G, Uint8 B, Uint8 A=255);
        void drawLine(int x1,int y1,int x2,int y2);
        void drawImage(SDL_Texture* image, int x, int y, int w=-1, int h=-1, double angle=0, SDL_RendererFlip flip=SDL_FLIP_NONE);
        void drawRect(SDL_Rect* rect);
        void drawRect(int x, int y, int w, int h) {SDL_Rect r = {x,y,w,h};drawRect(&r);};
        void fillRect(SDL_Rect* rect);
        void fillRect(int x, int y, int w, int h) {SDL_Rect r = {x,y,w,h};fillRect(&r);};
        void present();
        void clear();
        SDL_Texture* loadImage(string);
        void destroyImage(SDL_Texture*);
    protected:
    private:
        int mWidth, mHeight;
        SDL_Window *mWin;
        SDL_Renderer *mRender;
        Uint8 bgR, bgG, bgB, bgA;
};

#endif // RENDER_H
