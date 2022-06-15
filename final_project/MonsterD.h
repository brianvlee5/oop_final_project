#pragma once
#include "Monster.h"
class MonsterD :
    public Monster
{
public:
    MonsterD();
    MonsterD(const char* path, int n, SDL_Renderer* ren);
    MonsterD(const char* path, int n, SDL_Renderer* ren, Uint8 r, Uint8 g, Uint8 b);
    void initialize();
    void setMchptr(AnimeObject2& mainch);
    void startAI(Uint32 t);
    void stopAI();
    void draw(SDL_Rect dst, SDL_Rect src);
    void setAImode(int mode);
    void move();
    void setBase(int xx, int yy);
    void setHPP();
    void operator<<(AnimeObject2& mainch);
    
private:
    
    Uint32 AIinterval;
    static Uint32 AIState(Uint32 interval, void* param);
    AnimeObject2* Mchptr;
    int AImode;
    int WANDERmode;
    int XBase;
    int YBase;
    int XFly;
    int YFly;
    int Flycd;
    int FlyTime;
};

