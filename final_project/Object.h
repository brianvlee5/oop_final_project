#pragma once
#include <SDL.h> // Using SDL

class Object
{
public:
	Object();
	Object(const char* path, SDL_Renderer* renderer);
	Object(const char* path, SDL_Renderer* renderer, Uint8 r, Uint8 g, Uint8 b);

	void set(const char* path, SDL_Renderer* renderer);
	void set(const char* path, SDL_Renderer* renderer, Uint8 r, Uint8 g, Uint8 b);
	void close();
	void draw(SDL_Renderer* renderer, SDL_Rect dst, SDL_Rect src);
	int getWidth();
	int getHeight();

private:
	char path[100];
	SDL_Texture* texture;
	int width;
	int height;
};