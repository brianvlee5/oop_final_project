#pragma once
#include "Object.h"
#include <stdlib.h>
#include "constants.h"
#include <math.h>
#include <vector>

class Test
	:public Object
{
public:
	/******Initialization******/
	Test();
	Test(const char* path, SDL_Renderer* ren);
	Test(const char* path, SDL_Renderer* ren, Uint8 r, Uint8 g, Uint8 b);
	Test(const char* path, int n, SDL_Renderer* ren);
	Test(const char* path, int n, SDL_Renderer* ren, Uint8 r, Uint8 g, Uint8 b);
	void initialize();

	/*******Draw Function******/
//	void draw();
//	void draw(SDL_Rect src, SDL_Rect dst);


	void startTimerLine(Uint32 t);
	void startTimerParabola(Uint32 t);
	Uint32 getTime();
	void stopTimer();

	void move();
	void moveOrNot();
	bool xRight();
	bool xLeft();
	bool yUp();
	bool yDown();


	void setDir(int);

private:
	SDL_Renderer* renderer;
	SDL_TimerID timerID;
	Uint32 time;
	static Uint32 changeDataLine(Uint32 interval, void* param);
	static Uint32 changeDataParabola(Uint32 interval, void* param);

	int ii;
	int dir;

};

