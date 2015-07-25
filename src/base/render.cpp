#include "render.h"
#include <string>
#include <iostream>

using namespace std;

Render::Render(int width, int height)
:mWidth(width), mHeight(height)
{
    setBackground(0, 0, 0);
    mWin = SDL_CreateWindow("Tank Battle", 100, 100, mWidth, mHeight, SDL_WINDOW_SHOWN);
    if (mWin == NULL){
		throw (string("Failed: CreateWindow: ") + SDL_GetError());
		return;
	}
	mRender = SDL_CreateRenderer(mWin, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (mRender == NULL){
		throw (string("Failed: CreateRenderer: ") + SDL_GetError());
		return;
	}
}

Render::~Render()
{
    //dtor
}

SDL_Texture* Render::createTextureFromSurface(SDL_Surface* surface)
{
    return SDL_CreateTextureFromSurface(mRender, surface);
}

SDL_Texture* Render::createTargetTexture()
{
    return SDL_CreateTexture(mRender, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_TARGET, mWidth, mHeight);
}

void Render::setTarget(SDL_Texture* target)
{
    SDL_SetRenderTarget(mRender, target);
    SDL_SetTextureBlendMode(target, SDL_BLENDMODE_BLEND);
}

SDL_Texture* Render::getTarget()
{
    return SDL_GetRenderTarget(mRender);
}

void Render::setBackground(Uint8 R, Uint8 G, Uint8 B, Uint8 A)
{
    bgR = R;
    bgG = G;
    bgB = B;
    bgA = A;
}

void Render::setDrawColor(Uint8 R, Uint8 G, Uint8 B, Uint8 A)
{
    SDL_SetRenderDrawColor(mRender, R, G, B, A);
}

void Render::drawLine(int x1,int y1,int x2,int y2)
{
    SDL_RenderDrawLine(mRender, x1, y1, x2, y2);
}

void Render::drawImage(SDL_Texture* image, int x, int y, int w, int h, double angle, SDL_RendererFlip flip)
{
    SDL_Rect dstRect = {x, y, w, h};
    //SDL_Point dstCenter = {ctrX, ctrY};
    SDL_Rect* pDstRect=NULL;
    if (w!=-1 && h!=-1)
        pDstRect = &dstRect;
    SDL_RenderCopyEx(mRender, image, NULL, pDstRect, angle, NULL, flip);
}

void Render::drawRect(SDL_Rect* r)
{
    SDL_RenderDrawRect(mRender, r);
}

void Render::fillRect(SDL_Rect* r)
{
    SDL_RenderFillRect(mRender, r);
}

void Render::present()
{
    SDL_RenderPresent(mRender);
}

void Render::clear()
{
    SDL_SetRenderDrawColor(mRender, bgR, bgG, bgB, bgA);
    SDL_RenderClear(mRender);
}

SDL_Texture* Render::loadImage(string fileName)
{
    SDL_Texture* texture = NULL;
	SDL_Surface *srfc = IMG_Load(fileName.c_str());
	if (srfc)
	{
		texture = SDL_CreateTextureFromSurface(mRender, srfc);
		SDL_FreeSurface(srfc);
	} else {
        cout << "loadImage failed: " << fileName << endl;
	}
	return texture;
}

void Render::destroyImage(SDL_Texture* image)
{
    SDL_DestroyTexture(image);
}
