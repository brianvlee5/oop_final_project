#pragma once
#include "Object.h"
#include <stdlib.h>
#include "constants.h"
class Attack :
    public Object
{
public:

	Attack(const char* path, SDL_Renderer* ren);
	Attack(const char* path, int n, int hhn, int wwn, SDL_Renderer* ren);
	Attack(const char* path, int n, int hhn, int wwn, SDL_Renderer* ren, Uint8 r, Uint8 g, Uint8 b);
	void draw();
	void draw(SDL_Rect s, SDL_Rect d);
	void startTimerLine(Uint32 t);
	void stopTimer();
	void setShownFlag(bool b);
	void setDir(int);

private:
	SDL_Renderer* renderer;
	SDL_TimerID timerID;
	Uint32 time;
	static Uint32 changeDataLine(Uint32 interval, void* param);
	bool shownFlag;
	int ii;
	int dir;
};

