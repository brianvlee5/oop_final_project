#pragma once
#include <SDL.h>



class AnimeObject
{
public:
	AnimeObject(const char* path, int n, SDL_Renderer* ren);
	AnimeObject(const char* path, int n, SDL_Renderer* ren, Uint8 r, Uint8 g, Uint8 b);
	void close();
	void setPosition(int xx, int yy);
	int getWidth();
	int getHeight();
	int getX();
	int getY();
	void setVX(int x);
	void setVY(int y);
	int getVX();
	int getVY();
//	void draw(SDL_Renderer* renderer);
	void draw(SDL_Rect, SDL_Rect);
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
};

