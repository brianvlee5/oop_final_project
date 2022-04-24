#pragma once
#include <SDL.h>
#include "StaticObject.h"
#include "AnimeObject.h"

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
		SDL_Rect getcamera(AnimeObject);
	
	private:
		char path[100];
		SDL_Texture* texture;
		SDL_Renderer* renderer;
		int width;
		int height;
		SDL_Rect camera;
};