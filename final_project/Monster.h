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



class Monster
{
public:
	Monster(const char* path, int n, SDL_Renderer* ren);
	Monster(const char* path, int n, SDL_Renderer* ren, Uint8 r, Uint8 g, Uint8 b);
	void close();
	void setPosition(int xx, int yy);
	int getWidth();
	int getHeight();
	int getX() const;
	int getY() const;
	void setVX(int x);
	void setVY(int y);
	int getVX();
	int getVY();
	//	void draw(SDL_Renderer* renderer);
	void draw(SDL_Rect dst, SDL_Rect src);
	void startTimer(Uint32 t);
	void stopTimer();
	//	void move();
	void move();
	void setdetectCorner();
	void moveOrNot();
	bool xRight();
	bool xLeft();
	bool yUp();
	bool yDown();
	void setJumpFlag(bool f);
	void collisionAABB(AnimeObject2&);
	void AIstart(AnimeObject2&);

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
	Uint32 time;
	static Uint32 changeData(Uint32 interval, void* param);
	int velX;
	int velY;
	int detectCornerX[4][2];
	int detectCornerY[4][2];
	bool jumpFlag;
	int AImode;
	int WANDERmode;
};
