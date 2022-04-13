#include "Object.h"
#include "SDL_image.h" 
#include <stdio.h>
#include <SDL.h>

Object::Object()
{

}

Object::Object(const char* path, SDL_Renderer* renderer)
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


void Object::set(const char* path, SDL_Renderer* renderer)
{
	SDL_Surface* imgSurface = IMG_Load(path);
	if (imgSurface == NULL)
	{
		printf("SDL_LoadBMP failed: %s\n", IMG_GetError());
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

void Object::close()
{
	SDL_DestroyTexture(texture);
}
void Object::draw(SDL_Renderer* renderer, SDL_Rect dst, SDL_Rect src)
{
	SDL_Rect* d = &dst, * s = &src;

	if (dst.x == NULL)
	{
		d = NULL;
	}
	if (src.x == NULL)
	{
		s = NULL;
	}

	SDL_RenderCopy(renderer, texture, s, d);
}

int Object::getWidth()
{
	return width;
}

int Object::getHeight()
{
	return height;
}

/*
Object::Object(const char* path, SDL_Renderer* renderer, Uint8 r, Uint8 g, Uint8 b)
{
	SDL_Surface* imgSurface = IMG_Load(path);
	if (imgSurface == NULL)
	{
		printf("SDL_LoadBMP failed: %s\n", IMG_GetError());
		exit(0);
	}
	else
	{
		SDL_SetColorKey(imgSurface, true, SDL_MapRGB(imgSurface->format, r, g, b));

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
void Object::set(const char* path, SDL_Renderer* renderer, Uint8 r, Uint8 g, Uint8 b)
{
	SDL_Surface* imgSurface = IMG_Load(path);
	if (imgSurface == NULL)
	{
		printf("SDL_LoadBMP failed: %s\n", IMG_GetError());
	}
	else
	{
		SDL_SetColorKey(imgSurface, true, SDL_MapRGB(imgSurface->format, r, g, b));

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