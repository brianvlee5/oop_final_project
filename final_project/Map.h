#pragma once
#include <SDL.h>
#include "StaticObject.h"

class Map
{
	public:
		Map();
		Map(const char* path, SDL_Renderer* renderer);
		void set(const char* path, SDL_Renderer* renderer);
		void close();
		void draw(SDL_Renderer* renderer, SDL_Rect dst, SDL_Rect src);
		int getWidth();
		int getHeight();
		SDL_Rect getcamera(StaticObject);
	
	private:
		char path[100];
		SDL_Texture* texture;
		int width;
		int height;
		SDL_Rect camera;
};