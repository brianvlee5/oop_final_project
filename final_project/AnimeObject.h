#pragma once
#include <SDL.h>
class AnimeObject
{
public:
	AnimeObject(const char* path, int n, SDL_Renderer* renderer);

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
	void startTimer(Uint32 t);//
	void stopTimer();//
	void move();//

private:
	char path[100];//
	int num;  // 
	SDL_Texture** texture;
	int frame;
	int x;//
	int y;//
	SDL_TimerID timerID; //
	Uint32 time;//
	static Uint32 changeData(Uint32 interval, void* param);
	int velX;//
	int velY;//
};

