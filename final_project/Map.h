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
		void close();
		void draw(SDL_Rect dst, SDL_Rect src);
		int getWidth();
		int getHeight();
		SDL_Rect getcamera(StaticObject);
		void setcamera(AnimeObject&);
		void setcamera(AnimeObject2&);
		SDL_Rect getcamera();
	
	private:
		char path[100];
		SDL_Texture* texture;
		SDL_Renderer* renderer;
		int width;
		int height;
		SDL_Rect camera;
};