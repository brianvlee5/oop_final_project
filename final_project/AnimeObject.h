#pragma once
#include <SDL.h>



class AnimeObject
{
public:
	AnimeObject(const char* path, int n, SDL_Renderer* renderer);
	AnimeObject(const char* path, int n, SDL_Renderer* renderer, Uint8 r, Uint8 g, Uint8 b);
	void close();//
	void setPosition(int xx, int yy);//
	int getWidth();//
	int getHeight();//
	int getX();//
	int getY();//
	void setVX(int x);//
	void setVY(int y);//
	int getVX();//
	int getVY();//
	void draw(SDL_Renderer* renderer);//
	void draw(SDL_Renderer* renderer, SDL_Rect, SDL_Rect);
	void startTimer(Uint32 t);//
	void stopTimer();//
//	void move();
	void move(SDL_Rect);
	void setdetectP(SDL_Rect);
	void setdetectCorner(SDL_Rect);
	void moveOrNot();
	

private:
	char path[100];//
	int num;  // 
	SDL_Texture** texture;
	int frame;
	int width;
	int height;
	int x;//
	int y;//
	SDL_TimerID timerID; //
	Uint32 time;//
	static Uint32 changeData(Uint32 interval, void* param);
	int velX;//
	int velY;//
	int detectP[4][2];
	int detectCorner[4][2];
};

