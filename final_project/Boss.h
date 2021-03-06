#pragma once
#include "Monster.h"
class Boss :
    public Monster
{
public:
    Boss(const char* path, int n, SDL_Renderer* ren);
    Boss(const char* path, int n, SDL_Renderer* ren, Uint8 r, Uint8 g, Uint8 b);
    void setMchptr(AnimeObject2& mainch);
    void startAI(Uint32 t);
    void stopAI();
    void draw(SDL_Rect dst, SDL_Rect src);
private:
    SDL_TimerID AIID;
    Uint32 AIinterval;
    static Uint32 AIState(Uint32 interval, void* param);
    AnimeObject2* Mchptr;
    int AImode;
    int WANDERmode;
    int WaitTime;
    int WanderTime;
};

