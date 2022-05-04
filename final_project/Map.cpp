#include "Map.h"
#include "SDL_image.h" 
#include <stdio.h>
#include <SDL.h> // Using SDL
#include "constants.h"

Map::Map()
{
}

Map::Map(const char* path, SDL_Renderer* ren)
{
	renderer = ren;
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

void Map::set(const char* path, SDL_Renderer* ren)
{
	renderer = ren;
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
	camera.x = (mainch.getX()+mainch.getWidth()/2/SHRINK  - camera.w);
	camera.y = (mainch.getY()+mainch.getHeight()/2 / SHRINK - camera.h);
	//camera.x = (int)(WIDTH * (WIDTH / (double)mainch.getX())) ;
	if (camera.x > WINDOWW - camera.w )
		camera.x = WINDOWW - camera.w ;
	if (camera.y > WINDOWH - camera.h )
		camera.y = WINDOWH - camera.h ;
	if (camera.x < 0)
		camera.x = 0;
	if (camera.y < 0)
		camera.y = 0;
	return camera;
}

void Map::setcamera(AnimeObject mainch)
{
	camera.x = (mainch.getX() + mainch.getWidth() / 2 / SHRINK - camera.w/2);
	camera.y = (mainch.getY() + mainch.getHeight() / 2 / SHRINK - camera.h/2);
	//camera.x = (int)(WIDTH * (WIDTH / (double)mainch.getX())) ;
	if (camera.x > WIDTH - camera.w)
		camera.x = WIDTH - camera.w;
	if (camera.y > HEIGHT - camera.h)
		camera.y = HEIGHT - camera.h;
	if (camera.x < 0)
		camera.x = 0;
	if (camera.y < 0)
		camera.y = 0;

	
	
}

SDL_Rect Map::getcamera()
{
	return camera;
}

void Map::close()
{
	// Free loaded image	
	SDL_DestroyTexture(texture);
}

void Map::draw(SDL_Rect dst, SDL_Rect src)
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
