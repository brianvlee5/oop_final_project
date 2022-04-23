#include "AnimeObject.h"
#include <SDL.h>
#include <stdio.h>
#include "constants.h"
#include "SDL_image.h"
#include "tile.h"


AnimeObject::AnimeObject(const char* path, int n, SDL_Renderer* renderer, Uint8 r, Uint8 g, Uint8 b)
{
	num = n;
	texture = new SDL_Texture * [num];

	for (int i = 0; i < num; i++)
	{

		char file[100];
		sprintf_s(file, 100, "%s%02d.png", path, i + 1);

		SDL_Surface* imgSurface = IMG_Load(file);
		if (imgSurface == NULL)
		{
			printf("SDL_LoadBMP failed: %s\n", IMG_GetError());
			exit(0);
		}
		else
		{
			SDL_SetColorKey(imgSurface, true, SDL_MapRGB(imgSurface->format, r, g, b));
			// Create texture from surface pixels	
			texture[i] = SDL_CreateTextureFromSurface(renderer, imgSurface);
			// Also, you can use IMG_LoadTexture() to replace IMG_Load and SDL_CreateTextureFromSurface
			// texture = IMG_LoadTexture(renderer, path);
			if (texture[i] == NULL)
			{
				printf("SDL_CreateTextureFromSurface failed: %s\n", SDL_GetError());
			}
			width = imgSurface->w;
			height = imgSurface->h;

			// Get rid of old loaded surface
			SDL_FreeSurface(imgSurface);
		}
	}

}
AnimeObject::AnimeObject(const char* path, int n, SDL_Renderer* renderer)
{
	num = n;
	texture = new SDL_Texture * [num];

	
	for (int i = 0; i < num; i++) 
	{

		char file[100];
		sprintf_s(file, 100, "%s%02d.png", path, i + 1);

		SDL_Surface * imgSurface = IMG_Load(file);
		if (imgSurface == NULL)
		{
			printf("SDL_LoadBMP failed: %s\n", IMG_GetError());
			exit(0);
		}
		else
		{
			// Create texture from surface pixels	
			texture[i] = SDL_CreateTextureFromSurface(renderer, imgSurface);
			// Also, you can use IMG_LoadTexture() to replace IMG_Load and SDL_CreateTextureFromSurface
			// texture = IMG_LoadTexture(renderer, path);
			if (texture[i] == NULL)
			{
				printf("SDL_CreateTextureFromSurface failed: %s\n", SDL_GetError());
			}
			width = imgSurface->w;
			height = imgSurface->h;

			// Get rid of old loaded surface
			SDL_FreeSurface(imgSurface);
		}
	}

}



Uint32 AnimeObject::changeData(Uint32 interval, void* param)
{
	AnimeObject* p = (AnimeObject*)param;
	if (p->time != 0)
	{
		p->frame = (p->frame + 1) % p->num;
		return interval;
	}
	else
	{
		return 0;
	}
}

void AnimeObject::startTimer(Uint32 t)
{
	time = t;
	timerID = SDL_AddTimer(time, changeData, this); // Set Timer callback
}

void AnimeObject::stopTimer()
{
	time = 0;
}

void AnimeObject::close()
{
	for (int i = 0; i < num; i++) {
		SDL_DestroyTexture(texture[i]);
	}
}

void AnimeObject::draw(SDL_Renderer* renderer, SDL_Rect dst, SDL_Rect src) {
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

	SDL_RenderCopy(renderer, texture[frame], s, d);
}

void AnimeObject::draw(SDL_Renderer* renderer)
{
	
	SDL_Rect dst, src;
	dst.x = x;
	dst.y = y;
	dst.w = width;
	dst.h = height;

	//(texture)[frame].draw(renderer, dst, { NULL });
	
	SDL_Rect* d = &dst, * s = &src;
	//if (dst.x == NULL)
	//{
	//	d = NULL;
	//}
	if (src.x == NULL)
	{
		s = NULL;
	}

	SDL_RenderCopy(renderer, texture[frame], s, d);
	
}
void AnimeObject::setPosition(int xx, int yy)
{
	x = xx;
	y = yy;
}

int AnimeObject::getWidth()
{
	return width;
}

int AnimeObject::getHeight() 
{
	return height;
}

int AnimeObject::getX() 
{
	return x;
}

int AnimeObject::getY() 
{
	return y;
}
/*
void AnimeObject::move() {
	//velY -= 1;
	x += velX;
	y += velY;
	if (x + width / 4 >= 2 * WIDTH - CAMERAW)
		x = WIDTH + width / 4;
	if (y + height / 4 >= 2 * HEIGHT + CAMERAH)
		y = HEIGHT + height / 4;
	if (x < 0)
		x = 0;
	if (y < 0)
		y = 0;
}
*/
void AnimeObject::setdetectP(SDL_Rect mc)
{
	detectP[0][0] = (mc.x + (width / 8+x - mc.x) * CAMERAW / WIDTH) * 30 / WIDTH;//up x
	detectP[0][1] = (mc.y + (y - mc.y) * CAMERAH / HEIGHT) * 20 / HEIGHT;//      y
	detectP[1][0] = (mc.x + (width / 4 + x - mc.x) * CAMERAW / WIDTH) * 30 / WIDTH;//right
	detectP[1][1] = (mc.y + (height / 8+y - mc.y) * CAMERAH / HEIGHT) * 20 / HEIGHT;
	detectP[2][0] = (mc.x + (x - mc.x) * CAMERAW / WIDTH) * 30 / WIDTH;//left
	detectP[2][1] = (mc.y + (height / 8 + y - mc.y) * CAMERAH / HEIGHT) * 20 / HEIGHT;
	detectP[3][0] = (mc.x + (width / 8 + x - mc.x) * CAMERAW / WIDTH) * 30 / WIDTH;//down 
	detectP[3][1] = (mc.y + (height / 4 + y - mc.y) * CAMERAH / HEIGHT) * 20 / HEIGHT;
	
	printf("up:    %d, %d\n", detectP[0][0], detectP[0][1]);
	printf("left:  %d, %d\n", detectP[1][0], detectP[1][1]);
	printf("right: %d, %d\n", detectP[2][0], detectP[2][1]);
	printf("down:  %d, %d\n", detectP[3][0], detectP[3][1]);
	printf("%d %d %d %d\n", tile[detectP[0][1]][detectP[0][0]], tile[detectP[1][1]][detectP[1][0]], tile[detectP[2][1]][detectP[2][0]], tile[detectP[3][1]][detectP[3][0]]);
	
}

void AnimeObject::setdetectCorner(SDL_Rect mc)
{
	detectCorner[0][0] = (mc.x + (x - mc.x) * CAMERAW / WIDTH) * 30 / WIDTH;//up leftx
	detectCorner[0][1] = (mc.y + (y - mc.y) * CAMERAH / HEIGHT) * 20 / HEIGHT;//      y
	detectCorner[1][0] = (mc.x + (width / 4 + x - mc.x) * CAMERAW / WIDTH) * 30 / WIDTH;//up right
	detectCorner[1][1] = (mc.y + ( y - mc.y) * CAMERAH / HEIGHT) * 20 / HEIGHT;
	detectCorner[2][0] = (mc.x + (x - mc.x) * CAMERAW / WIDTH) * 30 / WIDTH;//bottom left
	detectCorner[2][1] = (mc.y + (height / 4 + y - mc.y) * CAMERAH / HEIGHT) * 20 / HEIGHT;
	detectCorner[3][0] = (mc.x + (width / 4 + x - mc.x) * CAMERAW / WIDTH) * 30 / WIDTH;//bottom right 
	detectCorner[3][1] = (mc.y + (height / 4 + y - mc.y) * CAMERAH / HEIGHT) * 20 / HEIGHT;
}

void AnimeObject::move(SDL_Rect mc) {
	
//	if (tile[detectP[2][1]][detectP[2][0]] == 0 || tile[detectP[3][1]][detectP[3][0]] == 0)
//		velY += 1;
	//y += velY;
	setdetectP(mc);
	moveOrNot();
	//x += velX;
	//y += velY;
	printf("VX: %d\nVY: %d\n", velX, velY);
	if (x + width / 4 >= 2 * WIDTH - CAMERAW)
			x = WIDTH + width / 4;
	if (y + height / 4 >= 2 * HEIGHT + CAMERAH)
		y = HEIGHT + height / 4;
	if (x < 0)
		x = 0;
	if (y < 0)
		y = 0;
}

void AnimeObject::moveOrNot()
{

	int p[4][2];
	//  [ 0  1 ] 
	//  [ 2  3 ]  [0] for x , [1] for y
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 2; j++)
			p[i][j] = detectCorner[i][j];
	
	if ( tile[ p[1][1] ][ p[1][0] ] == 1 && tile[ p[3][1] ][ p[3][0] ] == 1 )
	{
		if (velX > 0)
		{
			x+=velX;
		}
	}
	if ( tile[ p[0][1] ][ p[0][0] ] == 1 && tile[ p[2][1] ][ p[2][0] ] == 1 )
	{
		if (velX < 0)
		{
			x += velX;
		}
	}
	if ( tile[ p[0][1] ][ p[0][0] ] == 1 && tile[ p[1][1] ][ p[1][0] ] == 1 )
	{
		if (velY < 0)
		{
			y+=velY;
		}
	}
	if ( tile [p[2][1] ][ p[2][0] ] == 1 && tile[ p[3][1] ][ p[3][0] ] == 1 )
	{
		if (velY > 0)
			y+=velY;
	}


	
	if (tile[detectP[1][1]][detectP[1][0]] == 0 )
	{
		if (velX > 0)
			x += velX;
	}
	
	
	
	if (tile[detectP[2][1]][detectP[2][0]] == 0 )
	{
		if (velX < 0)
			x += velX;
	}
	

	
	
	if (tile[detectP[0][1]][detectP[0][0]] == 0 )
	{
		if (velY < 0)
			y += velY;
	}
	
	
	
	if (tile[detectP[3][1]][detectP[3][0]] == 0)
	{
		if (velY > 0)
			y += velY;
	}
	
	
}

int AnimeObject::getVY() {
	return velY;
}
void AnimeObject::setVY(int yy) {
	velY = yy;
}
int AnimeObject::getVX() {
	return velX;
}
void AnimeObject::setVX(int xx) {
	velX = xx;
}

