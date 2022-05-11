#include "Map.h"
#include "SDL_image.h" 
#include <stdio.h>
#include <SDL.h> // Using SDL
#include "constants.h"

Map::Map()
{
	mapnum = 0;
	camera.h = CAMERAH;
	camera.w = CAMERAW;
	startR[0] = { 116*WIDTH/MAPTILEX, 74*HEIGHT/MAPTILEY };
	startR[1] = { 115 * WIDTH / MAPTILEX, 74 * HEIGHT / MAPTILEY };
	startL[0] = { 5 * WIDTH / MAPTILEX, 75 * HEIGHT / MAPTILEY };
	startL[1] = { 5 * WIDTH / MAPTILEX, 75 * HEIGHT / MAPTILEY };
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
	mapnum = 0;
}

void Map::set(const char* pth, SDL_Renderer* ren)
{
	SDL_DestroyTexture(texture);
	renderer = ren;
	strcpy_s(path, pth);
	// Load a surface from a PNG file.	
	char file[100];
	sprintf_s(file, 100, "%s%02d.png", pth, mapnum+1);
	SDL_Surface* imgSurface = IMG_Load(file);

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

void Map::changemap(AnimeObject2& mainch)
{
	if (mainch.getMapFlag())
	{
		if (tile[mapnum][mainch.getY() * MAPTILEY / HEIGHT][mainch.getX() * MAPTILEX / WIDTH] == 8)
		{
			SDL_DestroyTexture(texture);
			mapnum--;
			mainch.setMapnum(mapnum);
			char file[100];
			sprintf_s(file, 100, "%s%02d.png", path, mapnum + 1);
			printf("oymg\n");
			SDL_Surface* imgSurface = IMG_Load(file);

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
			mainch.setPosition(startR[getmapnum()].x, startR[getmapnum()].y);
		}
		else if (tile[mapnum][(mainch.getY() + mainch.getHeight()) * MAPTILEY / HEIGHT][(mainch.getX() + mainch.getWidth()) * MAPTILEX / WIDTH] == 9)
		{
			//clearing last map
			SDL_DestroyTexture(texture);
			//switch to next map
			mapnum++;
			mainch.setMapnum(mapnum);
			char file[100];
			sprintf_s(file, 100, "%s%02d.png", path, mapnum + 1);

			printf("%s%02d.png", path, mapnum);
			SDL_Surface* imgSurface = IMG_Load(file);

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
			mainch.setPosition(startL[getmapnum()].x, startL[getmapnum()].y);
		}
	}
	
}

void Map::setmapnum(int n)
{
	mapnum = n;
}

int Map::getmapnum()
{
	return mapnum;
}


void Map::setcamera(AnimeObject& mainch)
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

void Map::setcamera(AnimeObject2& mainch)
{
	camera.x = (mainch.getX() + mainch.getWidth() / 2 / SHRINK - camera.w / 2);
	camera.y = (mainch.getY() + mainch.getHeight() / 2 / SHRINK - camera.h / 2);
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
