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
	int  getVX();
	int  getVY();

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
	void setMapnum(int);
	int getMapnum();
	bool getMapFlag();
	void startTimer(Uint32 t);
	void stopTimer();

private:

	int velX;
	int velY;
	int detectCornerX[4][2];
	int detectCornerY[4][2];
	bool jumpFlag;
	bool mapFlag;
	int Mapnum;
	SDL_TimerID timerID;
	Uint32 time;
	static Uint32 changeData(Uint32 interval, void* param);

};

