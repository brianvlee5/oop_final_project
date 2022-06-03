#pragma once
#include <SDL.h> // Using SDL
#include "Image.h"
#include <stdio.h>
#include "constants.h"

class Object
{
public:
	/******Initialization******/
	Object();
	Object(const char* path, SDL_Renderer* ren);
	Object(const char* path, SDL_Renderer* ren, Uint8 r, Uint8 g, Uint8 b);
	Object(const char* path, int n, SDL_Renderer* ren);
	Object(const char* path, int n, SDL_Renderer* ren, Uint8 r, Uint8 g, Uint8 b);
	~Object();
	void close();

	void setPosition(int xx, int yy);
	int getWidth();
	int getHeight();

	int getX();
	int getY();
	void setVy(int vyy);
	void setVx(int vxx);
	int getVx();
	int getVy();

	void setCenterAngle(SDL_Point c, double a);
	void setFlip(SDL_RendererFlip f);
	void setAlpha(int a);
	double getAngle();
	int getAlpha();

	void startFrameTimer(Uint32 t);
	void stopFrameTimer();

	/* New in this example*/
	void draw();
	void draw(SDL_Rect src, SDL_Rect dst);
	/*********************/

	void setMapFlag(bool f);   //flag 1
	void setShownFlag(bool f); //flag 2
	bool getShownFlag();

protected:
	SDL_Renderer* renderer; 

	bool shownFlag;

	int frame;
	int num;
	int x;
	int y;
	int velX;
	int velY;
	Image* image; // Wanting to set data in Image, 
				  // we have to use loop to set every image[frame]

private:

	SDL_TimerID timerID;
	Uint32 time;
	static Uint32 changeFrame(Uint32 interval, void* param);

};
