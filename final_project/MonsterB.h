#pragma once
#include "Monster.h"
class MonsterB :
    public Monster
{
public:
    MonsterB(const char* path, int n, SDL_Renderer* ren);
    MonsterB(const char* path, int n, SDL_Renderer* ren, Uint8 r, Uint8 g, Uint8 b);
    void AIstate(AnimeObject2& mainch);
    void draw(SDL_Rect dst, SDL_Rect src);
private:
    int AImode;
    int WANDERmode;

};

