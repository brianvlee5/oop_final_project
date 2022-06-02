#pragma once
#include <SDL.h>
#include "AnimeObject2.h"
#include "MonsterA.h"
#include <vector>
#include "SDL_image.h" 
#include <stdio.h>
#include "constants.h"
#include "MonsterP.h"

class Map
{
	public:
		Map();
		Map(const char* path, SDL_Renderer* ren);
		void set(const char* path, SDL_Renderer* ren);
		//void set(const char* path, SDL_Renderer* ren, int num);
		void close();
		void draw(SDL_Rect dst, SDL_Rect src);
		int getWidth();
		int getHeight();
		void setcamera(AnimeObject2 &mainch);
		SDL_Rect getcamera();
		void changemap(AnimeObject2& mainch, std::vector<MonsterA>& mv);
		void setmap(std::vector<MonsterA> mv);
		void setmapnum(int);
		int getmapnum();

		startP startR[7];
		startP startL[7];
	private:
		char path[100];
		SDL_Texture* texture;
		SDL_Renderer* renderer;
		int width;
		int height;
		SDL_Rect camera;
		int mapnum;
		
};