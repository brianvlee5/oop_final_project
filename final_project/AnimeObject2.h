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
	AnimeObject2();
	AnimeObject2(const char* path, SDL_Renderer* ren);
	AnimeObject2(const char* path, SDL_Renderer* ren, Uint8 r, Uint8 g, Uint8 b);
	AnimeObject2(const char* path, int n, SDL_Renderer* ren);
	AnimeObject2(const char* path, int n, SDL_Renderer* ren, Uint8 r, Uint8 g, Uint8 b);
	void initialize();
	
	void setVX(int vvx);
	void setVY(int vvy);
	void setIVT(int ivt);
	void setHP(int hp);
	int  getVX();
	int  getVY();
	int getIVT();
	int getHP();

	void draw();
//	void draw(SDL_Rect src);
//	void draw(SDL_Rect dst);
	void draw(SDL_Rect src, SDL_Rect dst);

	void move();
	void setdetectCorner();
	void moveOrNot();
	bool xRight();
	bool xLeft();
	bool yUp();
	bool yDown();

	void setJumpFlag(bool f);  //flag 1
	void setMapFlag(bool f);   //flag 2 (both static and anime need it, which should be added to base class)
	void setShownFlag(bool f); //flag 3 (both static and anime need it, which should be added to base class)
	void setIVFlag(bool f);    //flag 4
	void setDeadFlag(bool f);  //flag 5
	void setMapnum(int n);
	int getMapnum();
	bool getIVFlag();
	bool getMapFlag();
	bool getShownFlag();       // (both static and anime need it, which should be added to base class)
	bool getDeadFlag();

	void startFrameTimer(Uint32 t);
	void stopFrameTimer();
	void startHurt(Uint32 t);
	void stopHurtTimer();

private:

	int velX;
	int velY;
	int detectCornerX[4][2];
	int detectCornerY[4][2];
	bool shownflag;			   // (both static and anime need it, which should be added to base class)
	bool mapFlag;			   // (both static and anime need it, which should be added to base class)
	bool invinceflag;
	bool jumpFlag;
	bool deadFlag;
	int Mapnum;
	int health;
	SDL_TimerID timerID;
	SDL_TimerID HurtID;
	Uint32 time;
	Uint32 hurtt;
	int invincet;
	static Uint32 changeFrame(Uint32 interval, void* param);
	static Uint32 invincible(Uint32 interval, void* param);
};

