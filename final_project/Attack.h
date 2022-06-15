#pragma once
#include "Object.h"
#include <stdlib.h>
#include "constants.h"
#include <math.h>
#include "tile.h"
#include "MonsterA.h"
#include "MAttack.h"
#include <vector>
//#include "Coordinate.h"

class Attack :
    public Object
{
public:
	/******Initialization******/
	Attack();
	Attack(const char* path, SDL_Renderer* ren);
	Attack(const char* path, SDL_Renderer* ren, Uint8 r, Uint8 g, Uint8 b);
	Attack(const char* path, int n, SDL_Renderer* ren);
	Attack(const char* path, int n, SDL_Renderer* ren, Uint8 r, Uint8 g, Uint8 b);
	void initialize();

	/*******Draw Function******/
	void draw();
	void draw(SDL_Rect src, SDL_Rect dst);

	void startTimerLine(Uint32 t);
	void startTimerParabola(Uint32 t);
	void startTimerBounce(Uint32 t);
	void startTimerRotate(Uint32 t, int r, double d);
	void stopTimer();
	void removeTimerID();
	void startRotateCoolDown(Uint32 t);

	void move();
	void setdetectCorner();
	void moveOrNot();
	void moveWithBounce();
	bool xRight();
	bool xLeft();
	bool yUp();
	bool yDown();

	void collision_mons(std::vector<MonsterA>& mv);
	void collision_mons(std::vector<Monster*>& mv, AnimeObject2& mainch);

	void setMapFlag(bool f);
	bool getMapFlag();
	void setMapnum(int n);
	void setPause(bool f);
	void setDir(int);
	void setCharacterCenter(int x, int y);
	int getRushCD();
	bool getRotateFlag();

private:
	SDL_Renderer* renderer;
	SDL_TimerID timerID;
	SDL_TimerID cd_ID;
	Uint32 time;
	Uint32 cd;
	int cd_count;
	bool rotateFlag;
	static Uint32 changeDataLine(Uint32 interval, void* param);
	static Uint32 changeDataParabola(Uint32 interval, void* param);
	static Uint32 changeDataBounce(Uint32 interval, void* param);
	static Uint32 changeDataRotate(Uint32 interval, void* param);
	static Uint32 rotateCD(Uint32 interval, void* param);

	bool pause;

	bool mapFlag;
	int Mapnum;
	int ii;
	int dir;
	SDL_Point center;
	int radius;
	double phase_angle;

	int detectCornerX[4][2];
	int detectCornerY[4][2];
};


