#include "Image.h"
#include "SDL_image.h" 
#include <stdio.h>
#include <SDL.h> // Using SDL
#include <string.h>
#include "constants.h"


Image::Image()
{
	initialize();
}

Image::Image(const char* path, SDL_Renderer* renderer)
{
	initialize();
	setPath(path);
	setColorKey(NO_TRANSPARENT_BG);
	setRenderer(renderer);

	generateTexture();
}

Image::Image(const char* path, SDL_Renderer* renderer, Uint8 r, Uint8 g, Uint8 b)
{
	initialize();
	setPath(path);
	setColorKey({ r, g, b, 255 });
	setRenderer(renderer);

	generateTexture();
}

void Image::generateTexture()
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
		if (colorKey.a == 255)
		{
			// Set the color key (transparent pixel) in a surface.		
			SDL_SetColorKey(imgSurface, true, SDL_MapRGB(imgSurface->format, colorKey.r, colorKey.g, colorKey.b));
		}

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

void Image::close()
{
	// Free loaded image	
	SDL_DestroyTexture(texture);
}

void Image::draw()
{
	SDL_Rect* d = &dstRegion, * s = &srcRegion;

	if (dstRegion.x == ALLREGION)
	{
		d = NULL;
	}
	if (srcRegion.x == ALLREGION)
	{
		s = NULL;
	}


	// Set and enable standard alpha blending mode for a texture	
	if (SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND) == -1)
	{
		printf("SDL_SetTextureBlendMode failed: %s\n", SDL_GetError());
		return;
	}

	// Modulate texture alpha	
	if (SDL_SetTextureAlphaMod(texture, alpha) == -1)
	{
		printf("SDL_SetTextureAlphaMod failed: %s\n", SDL_GetError());
		return;
	}

	// Copy a portion of the texture to the current rendering target, 
	// optionally rotating it by angle around the given center and also flipping it top-bottom and/or left-right.
	// if center is NULL, rotation will be done around dstrect.w / 2, dstrect.h / 2	
	SDL_RenderCopyEx(renderer, texture, s, d, angle, &center, flip);
	//SDL_RenderCopy(renderer, texture, s, d);
}

void Image::draw_src(SDL_Rect src)
{
	setSrcRegion(src);

	draw();
}

void Image::draw_dst(SDL_Rect dst)
{
	setDstRegion(dst);

	draw();
}

void Image::draw(SDL_Rect src, SDL_Rect dst)
{
	setSrcRegion(src);
	setDstRegion(dst);

	draw();
}
// 用處不大 constructor時就已經set過
void Image::draw(SDL_Renderer* renderer, SDL_Rect src, SDL_Rect dst, SDL_Point center, double angle, SDL_RendererFlip flip, int alpha)
{
	setSrcRegion(src);
	setDstRegion(dst);
	setCenterAngle(center, angle);
	setFlip(flip);
	setAlpha(alpha);

	draw();
}

int Image::getWidth()
{
	return width;
}

int Image::getHeight()
{
	return height;
}

void Image::setPath(const char* p)
{
	path = new char[strlen(p)];
	strcpy_s(path, strlen(p) + 1, p);
}

void Image::setColorKey(SDL_Color c)
{
	colorKey = c;
}

void Image::setRenderer(SDL_Renderer* r)
{
	renderer = r;
}

void Image::setSrcRegion(SDL_Rect s)
{
	srcRegion = s;
}

void Image::setDstRegion(SDL_Rect d)
{
	dstRegion = d;
}

void Image::setCenterAngle(SDL_Point c, double a)
{
	center = c;
	angle = a;
}

void Image::setFlip(SDL_RendererFlip f)
{
	flip = f;
}

void Image::setAlpha(int a)
{
	alpha = a;
}

double Image::getAngle() {
	return angle;
}
int Image::getAlpha() {
	return alpha;
}

void Image::initialize()
{
	width = height = 0;
	setColorKey({0, 0, 0});
	srcRegion = dstRegion = { 0, 0, 0, 0 };
	center = { 0, 0 };
	angle = 0;
	flip = SDL_FLIP_NONE;
	alpha = 0;
}