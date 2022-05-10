#pragma once
#include <SDL.h>
#include "StaticObject.h"
#include "AnimeObject.h"
#include "AnimeObject2.h"

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
		SDL_Rect getcamera(StaticObject);
		void setcamera(AnimeObject&);
		void setcamera(AnimeObject2 &mainch);
		SDL_Rect getcamera();
		void changemap(AnimeObject2&);
		void setmapnum(int);
		int getmapnum();

		startP start[2];
	private:
		char path[100];
		SDL_Texture* texture;
		SDL_Renderer* renderer;
		int width;
		int height;
		SDL_Rect camera;
		int mapnum;
		
};