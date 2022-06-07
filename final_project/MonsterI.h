#pragma once
#include "Monster.h"
class MonsterI :
    public Monster
{
public:
    MonsterI(const char* path, int n, SDL_Renderer* ren);
    MonsterI(const char* path, int n, SDL_Renderer* ren, Uint8 r, Uint8 g, Uint8 b);
    void gotKey(AnimeObject2& mainch);
    void setMchptr(AnimeObject2& mainch);
    void startAI(Uint32 t);
    void stopAI();
    void gateAABB(AnimeObject2& mainch);
    void princessAABB(AnimeObject2& mainch);
    void setWinFlag(bool f);
    bool getWinFlag();
private:

    bool winFlag;
};

