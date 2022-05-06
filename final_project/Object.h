#pragma once
#include <SDL.h> // Using SDL
#include "Image.h"
#include <stdio.h>
#include "constants.h"

class Object
{
public:
	Object(const char* path, SDL_Renderer* ren);
	Object(const char* path, int n, int hhn, int wwn, SDL_Renderer* ren);
	Object(const char* path, int n, int hhn, int wwn, SDL_Renderer* ren, Uint8 r, Uint8 g, Uint8 b);
	void close();
	void setPosition(int xx, int yy);
	int getWidth();
	int getHeight();
	int getX();
	int getY();
	void setCenterAngle(SDL_Point c, double a);
	void setFlip(SDL_RendererFlip f);
	void setAlpha(int a);
	double getAngle();
	int getAlpha();

	void startTimer(Uint32 t);
	void stopTimer();

	/* New in this example*/
	virtual void draw();  // change into virtual function
	virtual ~Object();
	/*********************/
	virtual void draw(SDL_Rect s, SDL_Rect d);

	/* New in this example*/
protected:
	SDL_Renderer* renderer; // change into protected data member
	/*********************/
	int frame;
	int num;
	int x;
	int y;
	int wn; // image number in width
	int hn; // image number in height
	Image image;

private:

	SDL_TimerID timerID;
	Uint32 time;
	static Uint32 changeData(Uint32 interval, void* param);

};
