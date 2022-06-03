#pragma once
#include <SDL.h>
//#include "Object.h"
class StaticObject 
    //:protected Object
{
public:
    StaticObject();
    StaticObject(const char* path, SDL_Renderer* renderer);
    //StaticObject(const char* path, SDL_Renderer* renderer, Uint8 r, Uint8 g, Uint8 b);
    //void set(const char* path, SDL_Renderer* renderer);
    void setPosition(int xx, int yy);
    void close();
    void draw(SDL_Renderer* renderer, SDL_Rect dst, SDL_Rect src);
    void draw(SDL_Renderer* renderer);
    int getWidth();
    int getHeight();
    int getX();
    int getY();
    int getVX();
    int getVY();
    void setVX(int x);
    void setVY(int y);
    void move();

private:
    char path[100];
    SDL_Texture* texture;
    int width;
    int height;
    int x;
    int y;
    int velX;//
    int velY;//
};