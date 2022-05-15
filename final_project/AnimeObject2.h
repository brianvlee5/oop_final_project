#pragma once
#include "Object.h"
#include <SDL.h>
#include "tile.h"
#include "SDL2_gfxPrimitives.h"
#include <stdio.h>

#include "constants.h"
#include "SDL_image.h"

class AnimeObject2 :
    public Object
{
public:
	AnimeObject2(const char* path, SDL_Renderer* ren);
	AnimeObject2(const char* path, int n, int hhn, int wwn, SDL_Renderer* ren);
	AnimeObject2(const char* path, int n, int hhn, int wwn, SDL_Renderer* ren, Uint8 r, Uint8 g, Uint8 b);
	
	void setVX(int x);
	void setVY(int y);
	void setIVT(int ivt);
	void setHP(int hp);
	int  getVX();
	int  getVY();
	int getIVT();
	int getHP();

	void draw();
	void draw(SDL_Rect d);
//	void draw(SDL_Rect s, SDL_Rect d);

	void move();
	void setdetectCorner();
	void moveOrNot();
	bool xRight();
	bool xLeft();
	bool yUp();
	bool yDown();

	void setJumpFlag(bool f);
	void setMapFlag(bool f);
	void setShownFlag(bool f);
	void setIVFlag(bool f);
	void setDeadFlag(bool f);
	void setMapnum(int);
	int getMapnum();
	bool getIVFlag();
	bool getMapFlag();
	bool getShownFlag();
	bool getDeadFlag();
	void startTimer(Uint32 t);
	void stopTimer();
	void startHurt(Uint32 t);

private:

	int velX;
	int velY;
	int detectCornerX[4][2];
	int detectCornerY[4][2];
	bool shownflag;
	bool invinceflag;
	bool jumpFlag;
	bool mapFlag;
	bool deadFlag;
	int Mapnum;
	int health;
	SDL_TimerID timerID;
	SDL_TimerID HurtID;
	Uint32 time;
	Uint32 hurtt;
	int invincet;
	static Uint32 changeData(Uint32 interval, void* param);
	static Uint32 invincible(Uint32 interval, void* param);
};

