#pragma once
#include "Monster.h"
#include "MAttack.h"

class MonsterB :
    public Monster
{
public:
    MonsterB(const char* path, int n, SDL_Renderer* ren);
    MonsterB(const char* path, int n, SDL_Renderer* ren, Uint8 r, Uint8 g, Uint8 b);
    void setMchptr(AnimeObject2& mainch);
    void setMatkptr(MAttack& matk);
    void startAI(Uint32 t);
    void stopAI();
    void setAImode(int mode);
    void draw(SDL_Rect dst, SDL_Rect src);

private:
    MAttack* MonsFire;
    
    Uint32 AIinterval;
    static Uint32 AIState(Uint32 interval, void* param);
    AnimeObject2* Mchptr;
    int AImode;
    int WANDERmode;
    int WaitTime;
    int WanderTime;

};

