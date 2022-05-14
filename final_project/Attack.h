#pragma once
#include "Object.h"
#include <stdlib.h>
#include "constants.h"
#include <math.h>
class Attack :
    public Object
{
public:
	Attack();
	Attack(const char* path, SDL_Renderer* ren);
	Attack(const char* path, int n, int hhn, int wwn, SDL_Renderer* ren);
	Attack(const char* path, int n, int hhn, int wwn, SDL_Renderer* ren, Uint8 r, Uint8 g, Uint8 b);
	Attack set(const char* path, int n, int hhn, int wwn, SDL_Renderer* ren, Uint8 r, Uint8 g, Uint8 b);
	void draw();
	void draw(SDL_Rect d);
//	void draw(SDL_Rect s, SDL_Rect d);

	void startTimerLine(Uint32 t);
	void startTimerParabola(Uint32 t);
	Uint32 getTime();
	void stopTimer();

	void setdetectCorner();
	void moveOrNot();
	bool xRight();
	bool xLeft();
	bool yUp();
	bool yDown();

	void setShownFlag(bool b);
	bool getShownFlag();
	void setDir(int);
	void setVy(int vyy);
	void setVx(int vxx);
	SDL_Point getSelfCenter();

private:
	SDL_Renderer* renderer;
	SDL_TimerID timerID;
	Uint32 time;
	static Uint32 changeDataLine(Uint32 interval, void* param);
	static Uint32 changeDataParabola(Uint32 interval, void* param);
	bool shownFlag;
	int ii;
	int dir;
	int vx;
	int vy;
};

