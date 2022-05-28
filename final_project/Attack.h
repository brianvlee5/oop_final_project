#pragma once
#include "Object.h"
#include <stdlib.h>
#include "constants.h"
#include <math.h>
#include "tile.h"
#include "MonsterA.h"
#include <vector>

class Attack :
    public Object
{
public:
	Attack();
	Attack(const char* path, SDL_Renderer* ren);
	Attack(const char* path, SDL_Renderer* ren, Uint8 r, Uint8 g, Uint8 b);
	Attack(const char* path, int n, SDL_Renderer* ren);
	Attack(const char* path, int n, SDL_Renderer* ren, Uint8 r, Uint8 g, Uint8 b);
	void initialize();

	void draw();
	void draw_src(SDL_Rect src);
	void draw_dst(SDL_Rect dst);
	void draw(SDL_Rect src, SDL_Rect dst);

	void startTimerLine(Uint32 t);
	void startTimerParabola(Uint32 t);
	void startTimerBounce(Uint32 t);
	Uint32 getTime();
	void stopTimer();

	void move();
	void setdetectCorner();
	void moveOrNot();
	void moveWithBounce();
	bool xRight();
	bool xLeft();
	bool yUp();
	bool yDown();

	void collision_mons(std::vector<MonsterA>&);

	void setMapFlag(bool f);
	bool getMapFlag();
	void setMapnum(int);
	void setShownFlag(bool b);
	bool getShownFlag();
	void setDir(int);
	void setVy(int vyy);
	void setVx(int vxx);

private:
	SDL_Renderer* renderer;
	SDL_TimerID timerID;
	Uint32 time;
	static Uint32 changeDataLine(Uint32 interval, void* param);
	static Uint32 changeDataParabola(Uint32 interval, void* param);
	static Uint32 changeDataBounce(Uint32 interval, void* param);
	bool shownFlag;
	bool mapFlag;
	int Mapnum;
	int ii;
	int dir;
	int velX;
	int velY;
	int detectCornerX[4][2];
	int detectCornerY[4][2];
};


