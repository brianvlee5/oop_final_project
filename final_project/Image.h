#pragma once
#include <SDL.h>
#include "SDL_image.h" 
#include <stdio.h>
#include <string.h>
#include "constants.h"
class Image
{
public:
	Image();
	Image(const char* path, SDL_Renderer* renderer);
	Image(const char* path, SDL_Renderer* renderer, Uint8 r, Uint8 g, Uint8 b);
	void generateTexture();
	void close();
	void draw();
	void draw_src(SDL_Rect src);
	void draw_dst(SDL_Rect dst);
	void draw(SDL_Rect src, SDL_Rect dst);
	void draw(SDL_Renderer* renderer, SDL_Rect src, SDL_Rect dst, SDL_Point center, double angle, SDL_RendererFlip flip, int alpha);

	int getWidth();
	int getHeight();
	double getAngle();
	int getAlpha();

	void setPath(const char* p);
	void setColorKey(SDL_Color c);  // NO_TRANSPARENT_BG | {r,g,b,255}
	void setRenderer(SDL_Renderer* ren);
	void setSrcRegion(SDL_Rect src);
	void setDstRegion(SDL_Rect dst);
	void setCenterAngle(SDL_Point c, double a);
	void setFlip(SDL_RendererFlip f);
	void setAlpha(int a);

	void initialize();


private:
	char* path;
	SDL_Texture* texture;
	int width;
	int height;
	SDL_Color colorKey;
	SDL_Renderer* renderer;

	SDL_Rect srcRegion;
	SDL_Rect dstRegion;

	SDL_Point center;
	double angle;
	SDL_RendererFlip flip;
	int alpha;
};

