#pragma once
#include "Monster.h"
class MonsterA :
    public Monster
{
public:
    MonsterA(const char* path, int n, SDL_Renderer* ren);
    MonsterA(const char* path, int n, SDL_Renderer* ren, Uint8 r, Uint8 g, Uint8 b);
    void setMchptr(AnimeObject2& mainch);
    void startAI(Uint32 t);
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

