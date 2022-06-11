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
	/******Initialization******/
	AnimeObject2();
	AnimeObject2(const char* path, SDL_Renderer* ren);
	AnimeObject2(const char* path, SDL_Renderer* ren, Uint8 r, Uint8 g, Uint8 b);
	AnimeObject2(const char* path, int n, SDL_Renderer* ren);
	AnimeObject2(const char* path, int n, SDL_Renderer* ren, Uint8 r, Uint8 g, Uint8 b);
	void initialize();

	void setMapnum(int n);
	void setRush(int ru);
	void setIVT(int ivt);
	void setHP(int hp);
	void setDir(int d);
	void setPotionNum(int n);
	int getMapnum();
	int getRush();
	int getIVT();
	int getHP();
	int getDir();
	int getPotionNum();

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

	/*****Flag*****/
	void setJumpFlag(bool f);  //flag 1
	void setMapFlag(bool f);   //flag 2 (both static and anime need it, which should be added to base class)
	void setIVFlag(bool f);    //flag 3
	void setDeadFlag(bool f);  //flag 4
	void setKey(bool f);
	void setGateFlag(bool f);
	bool getIVFlag();
	bool getMapFlag();
	bool getDeadFlag();
	bool getKey();
	bool getGateFlag();

	/*****Item*****/
	void usePotion();
	void setCoin(int c);
	int getCoin();

	/*****Timer*****/
	void startFrameTimer(Uint32 t);
	void stopFrameTimer();
	void startHurt(Uint32 t);
	void stopHurtTimer();
	void startRush(Uint32 t);
	void stopRushTimer();
	void startRushCD(Uint32 t);

private:

	int detectCornerX[4][2];
	int detectCornerY[4][2];

	bool mapFlag;			   // (both static and anime need it, which should be added to base class)
	bool invinceFlag;
	bool jumpFlag;
	bool deadFlag;
	bool rushFlag;
	bool gravityFlag;
	bool gateFlag;
	bool key;

	int coin;
	int dir;
	int init_vx;
	int Mapnum;
	int health;
	int num_potion;
	SDL_TimerID timerID;
	SDL_TimerID HurtID;
	SDL_TimerID RushID;
	SDL_TimerID cd_ID;
	Uint32 time;
	Uint32 hurtt;
	Uint32 rush;
	Uint32 cd;
	int invincet;
	int rush_count;
	int cd_count;
	static Uint32 changeFrame(Uint32 interval, void* param);
	static Uint32 invincible(Uint32 interval, void* param);
	static Uint32 rushing(Uint32 interval, void* param);
	static Uint32 rushCD(Uint32 intercal, void* param);
};

