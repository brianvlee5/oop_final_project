#include "Map.h"
#include "SDL_image.h" 
#include <stdio.h>
#include <SDL.h> // Using SDL
#include "constants.h"

Map::Map()
{
}

Map::Map(const char* path, SDL_Renderer* renderer)
{
	// Load a surface from a PNG file.	
	SDL_Surface* imgSurface = IMG_Load(path);
	if (imgSurface == NULL)
	{
		// Call IMG_GetError to get the error string.
		printf("SDL_LoadBMP failed: %s\n", IMG_GetError());
		exit(0);
	}
	else
	{
		// Create texture from surface pixels	
		texture = SDL_CreateTextureFromSurface(renderer, imgSurface);

		// Also, you can use IMG_LoadTexture() to replace IMG_Load and SDL_CreateTextureFromSurface
		// texture = IMG_LoadTexture(renderer, path);

		if (texture == NULL)
		{
			printf("SDL_CreateTextureFromSurface failed: %s\n", SDL_GetError());
		}

		width = imgSurface->w;
		height = imgSurface->h;

		// Get rid of old loaded surface
		SDL_FreeSurface(imgSurface);
	}
	camera.h = CAMERAH;
	camera.w = CAMERAW;
}

void Map::set(const char* path, SDL_Renderer* renderer)
{
	// Load a surface from a PNG file.	
	SDL_Surface* imgSurface = IMG_Load(path);
	if (imgSurface == NULL)
	{
		// Call IMG_GetError to get the error string.
		printf("SDL_LoadBMP failed: %s\n", IMG_GetError());
		exit(0);
	}
	else
	{
		// Create texture from surface pixels	
		texture = SDL_CreateTextureFromSurface(renderer, imgSurface);

		// Also, you can use IMG_LoadTexture() to replace IMG_Load and SDL_CreateTextureFromSurface
		// texture = IMG_LoadTexture(renderer, path);

		if (texture == NULL)
		{
			printf("SDL_CreateTextureFromSurface failed: %s\n", SDL_GetError());
		}

		width = imgSurface->w;
		height = imgSurface->h;

		// Get rid of old loaded surface
		SDL_FreeSurface(imgSurface);
	}
}

SDL_Rect Map::getcamera(StaticObject mainch)
{
	camera.x = mainch.getX() - camera.w / 2;
	camera.y = mainch.getY() - camera.h / 2;
//if (camera.x > WIDTH - camera.w / 2)
//	camera.x = WIDTH - camera.w / 2;
//if (camera.y > HEIGHT - camera.h / 2)
//	camera.y = HEIGHT - camera.h / 2;
//if (camera.x < camera.w / 2)
//	camera.x = camera.w / 2;
//if (camera.y < camera.h / 2)
//	camera.y = camera.h / 2;
	return camera;
}

void Map::close()
{
	// Free loaded image	
	SDL_DestroyTexture(texture);
}

void Map::draw(SDL_Renderer* renderer, SDL_Rect dst, SDL_Rect src)
{
	SDL_Rect *d = &dst, *s = &src;
	
	if (dst.x == ALLREGION)
	{
		d = NULL;
	}
	if (src.x == ALLREGION)
	{
		s = NULL;
	}

	SDL_RenderCopy(renderer, texture, s, d);
}

int Map::getWidth()
{
	return width;
}

int Map::getHeight()
{
	return height;
}
