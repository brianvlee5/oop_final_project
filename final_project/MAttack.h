#pragma once
#include "Monster.h"

class MAttack :
	public Monster
{
public:
	MAttack(const char* path, int n, SDL_Renderer* ren);
	MAttack(const char* path, int n, SDL_Renderer* ren, Uint8 r, Uint8 g, Uint8 b);
	
	int getAF();
	void setAF(int af);
	void draw(SDL_Rect dst, SDL_Rect src);
	void move();
	void moveOrNot();
	void setMchptr(AnimeObject2& mainch);
	void startST(Uint32 t);
	void startAI(Uint32 t);
	void stopAI();
	void stopST();

private:
	
	SDL_TimerID STID;
	
	Uint32 STTime;

	static Uint32 Straight(Uint32 interval, void* param);

	int atkFly;
};

