#pragma once
#include "Monster.h"
class MonsterI :
    public Monster
{
public:
    MonsterI(const char* path, int n, SDL_Renderer* ren);
    MonsterI(const char* path, int n, SDL_Renderer* ren, Uint8 r, Uint8 g, Uint8 b);
    void gotKey(AnimeObject2& mainch);
private:

};

