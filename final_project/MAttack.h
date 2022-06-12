#pragma once
#include <SDL.h>
#include "SDL2_gfxPrimitives.h"
#include <stdio.h>
#include <math.h>
#include "constants.h"
#include "SDL_image.h"
#include "tile.h"
#include "MonsterAI.h"
#include "AnimeObject2.h"
#include <stdlib.h>

class MAttack 
{
public:
	MAttack(const char* path, int n, SDL_Renderer* ren);
	MAttack(const char* path, int n, SDL_Renderer* ren, Uint8 r, Uint8 g, Uint8 b);
	void close();
	void setPosition(int xx, int yy);
	int getWidth();
	int getHeight();
	int getX() const;
	int getY() const;
	int getHP();
	int getMaxHP();
	int getMapnum();
	int getAF();
	void setHP(int hp);
	void setVX(int x);
	void setVY(int y);
	void setAF(int af);
	void setMapnum(int mapnumm);
	int getVX();
	int getVY();
	//	void draw(SDL_Renderer* renderer);
	void draw(SDL_Rect dst, SDL_Rect src);
	void startTimer(Uint32 t);
	void stopTimer();
	void startCD(Uint32);
	//	void move();
	void move();
	void setdetectCorner();
	void moveOrNot();
	bool xRight();
	bool xLeft();
	bool yUp();
	bool yDown();
	void setJumpFlag(bool f);
	bool getJumpFlag();
	void collisionAABB(AnimeObject2&);
	int getDPX(int a, int b);
	int getDPY(int a, int b);
	void setcdFlag(bool f);
	bool getcdFlag();
	void setDeadFlag(bool f);
	bool getDeadFlag();
	void setShownFlag(bool f);
	bool getShownFlag();
	SDL_Renderer* getRenderer();
	void setMchptr(AnimeObject2& mainch);
	void startST(Uint32 t);

private:
	char path[100];
	int num;
	SDL_Texture** texture;
	SDL_Renderer* renderer;
	int frame;
	int width;
	int height;
	int x;
	int y;
	SDL_TimerID timerID;
	SDL_TimerID damageID;
	SDL_TimerID STID;
	Uint32 time;
	Uint32 hurtT;
	Uint32 STTime;
	static Uint32 changeData(Uint32 interval, void* param);
	static Uint32 damaged(Uint32 interval, void* param);
	static Uint32 Straight(Uint32 interval, void* param);
	int velX;
	int velY;
	int detectCornerX[4][2];
	int detectCornerY[4][2];
	bool jumpFlag;
	bool cdFlag;
	bool deadFlag;
	bool shownFlag;

	int mapnum;

	int health;
	int damageCD;
	int Maxhp;

	int atkFly;
};

