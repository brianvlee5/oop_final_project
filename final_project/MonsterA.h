#pragma once
#include "Monster.h"
class MonsterA :
    public Monster
{
public:
    MonsterA(const char* path, int n, SDL_Renderer* ren);
    MonsterA(const char* path, int n, SDL_Renderer* ren, Uint8 r, Uint8 g, Uint8 b);
    void AIstart(AnimeObject2&);
    void StartWait(Uint32 t);
private:
    SDL_TimerID WaitID;
    Uint32 waitT;
    static Uint32 WaitaMoment(Uint32 interval, void* param);
    int AImode;
    int WANDERmode;
    int waitTime;
};

