#include "StaticObject.h"
#include "SDL_image.h" 
#include "constants.h"
#include <SDL.h>
#include <stdio.h>

StaticObject::StaticObject() {
}

StaticObject::StaticObject(const char* path, SDL_Renderer* renderer)
{
	SDL_Surface* imgSurface = IMG_Load(path);
	if (imgSurface == NULL)
	{
		printf("SDL_LoadBMP failed: %s\n", IMG_GetError());
		exit(0);
	}
	else
	{
		texture = SDL_CreateTextureFromSurface(renderer, imgSurface);
		if (texture == NULL)
		{
			printf("SDL_CreateTextureFromSurface failed: %s\n", SDL_GetError());
		}
		width = imgSurface->w;
		height = imgSurface->h;

		SDL_FreeSurface(imgSurface);

	}
}

void StaticObject::setPosition(int xx, int yy) {
	x = xx;
	y = yy;
}

void StaticObject::close()
{
	SDL_DestroyTexture(texture);
}

void StaticObject::draw(SDL_Renderer* renderer, SDL_Rect dst, SDL_Rect src) {
	SDL_Rect* d = &dst, * s = &src;
	        //
//	if (dst.x == NULL)
//	{
//		d = NULL;
//	}
	if (src.x == NULL)
	{
		s = NULL;
	}

	SDL_RenderCopy(renderer, texture, s, d);
}

void StaticObject::draw(SDL_Renderer* renderer) {
	SDL_Rect d, s;
	d.x = x;
	d.y = y;
	d.w = getWidth() - 20;
	d.h = getHeight() - 5;

	draw(renderer, d, { NULL });
}

int StaticObject::getWidth() {
	return width;
}
int StaticObject::getHeight() {
	return height;
}
int StaticObject::getX() {
	return x;
}
int StaticObject::getY() {
	return y;
}
void StaticObject::move() {
	x += velX;
	y += velY;
	if (x + width/10 >= 2*WIDTH-CAMERAW)
		x = WIDTH - width/10;
	if (y + height/10 >= 2*HEIGHT+CAMERAH)
		y = HEIGHT - height/10;
	if (x < 0)
		x = 0;
	if (y < 0)
		y = 0;
}
int StaticObject::getVY() {
	return velY;
}
void StaticObject::setVY(int yy) {
	velY = yy;
}
int StaticObject::getVX() {
	return velX;
}
void StaticObject::setVX(int xx) {
	velX = xx;
}
/*
void StaticObject::set(const char* path, SDL_Renderer* renderer)
{
	SDL_Surface* imgSurface = IMG_Load(path);
	if (imgSurface == NULL)
	{
		printf("SDL_LoadBMP failed: %s\n", IMG_GetError());
		exit(0);
	}
	else
	{
		texture = SDL_CreateTextureFromSurface(renderer, imgSurface);
		if (texture == NULL)
		{
			printf("SDL_CreateTextureFromSurface failed: %s\n", SDL_GetError());
		}
		width = imgSurface->w;
		height = imgSurface->h;

		SDL_FreeSurface(imgSurface);

	}
}
*/