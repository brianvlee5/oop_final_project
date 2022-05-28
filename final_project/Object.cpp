#include "Object.h"
Object::Object()
{
}
Object::Object(const char* path, SDL_Renderer* ren)
{
	image = new Image;
	image->setPath(path);
	image->setRenderer(ren);
	image->setColorKey(NO_TRANSPARENT_BG);
	image->setCenterAngle({ 0,0 }, 0);
	image->setFlip(SDL_FLIP_VERTICAL);
	image->setAlpha(255);

	image->generateTexture();

	renderer = ren;
	num = 1;
	frame = 0;
}

Object::Object(const char* path, SDL_Renderer* ren, Uint8 r, Uint8 g, Uint8 b)
{
	image = new Image;
	image->setPath(path);
	image->setRenderer(ren);
	image->setColorKey({ r, g, b, 255 });
	image->setCenterAngle({ 0,0 }, 0);
	image->setFlip(SDL_FLIP_NONE);
	image->setAlpha(255);

	image->generateTexture();

	renderer = ren;
	num = 1;
	frame = 0;
}

Object::Object(const char* path, int n, SDL_Renderer* ren)
{
	num = n;
	image = new Image[num];

	for (int i = 0; i < num; i++)
	{
		char file[100];
		sprintf_s(file, 100, "%s%02d.png", path, i + 1);

		image[i].setPath(file);
		image[i].setRenderer(ren);
		image[i].setColorKey(NO_TRANSPARENT_BG);
		image[i].setCenterAngle({ 0,0 }, 0);
		image[i].setFlip(SDL_FLIP_NONE);
		image[i].setAlpha(255);

		image[i].generateTexture();
	}

	frame = 0;
	renderer = ren;
}

Object::Object(const char* path, int n, SDL_Renderer* ren, Uint8 r, Uint8 g, Uint8 b)
{
	num = n;
	image = new Image[num];

	for (int i = 0; i < num; i++)
	{
		char file[100];
		sprintf_s(file, 100, "%s%02d.png", path, i + 1);

		image[i].setPath(file);
		image[i].setRenderer(ren);
		image[i].setColorKey({ r, g, b, 255 });
		image[i].setCenterAngle({ 0,0 }, 0);
		image[i].setFlip(SDL_FLIP_NONE);
		image[i].setAlpha(255);

		image[i].generateTexture();
	}

	frame = 0;
	renderer = ren;
}
Object::~Object()
{
	close();
}

void Object::close()
{
	// Free loaded image	
	for (int i = 0; i < num; i++)
	{
		image[i].close();
	}

	// Remove timer in case the call back was not called	
	SDL_RemoveTimer(timerID);
}

void Object::setPosition(int xx, int yy)
{
	x = xx;
	y = yy;
}

int Object::getWidth()
{
	return image[frame].getWidth();
}

int Object::getHeight()
{
	return image[frame].getHeight();
}
/* Draw Functions */
void Object::draw()
{
	SDL_Rect d, s;
	d.x = x;
	d.y = y;
	d.w = image[frame].getWidth();
	d.h = image[frame].getHeight();

	image[frame].draw({ ALLREGION }, d);
}

void Object::draw_src(SDL_Rect src) // shownFlag is supposed to be applied here 
								// instead of the derived class
{
	SDL_Rect s;
	if (src.x == ALLREGION) {
		s.x = ALLREGION;
	}
	else {
		s.x = src.x;
		s.y = src.y;
		s.w = src.w;
		s.h = src.h;
	}

	image[frame].draw_src(s);
}
void Object::draw_dst(SDL_Rect dst)
{
	SDL_Rect d;
	if (dst.x == ALLREGION) {
		d.x = x;
		d.y = y;
		d.w = image[frame].getWidth();
		d.h = image[frame].getHeight();
	}
	else {
		d.x = dst.x;
		d.y = dst.y;
		d.w = dst.w;
		d.h = dst.h;
	}
	image[frame].draw_dst(d);
}

void Object::draw(SDL_Rect src, SDL_Rect dst)
{
	SDL_Rect s, d;
	if (src.x == ALLREGION) {
		s.x = ALLREGION;
	}
	else {
		s.x = src.x;
		s.y = src.y;
		s.w = src.w;
		s.h = src.h;
	}
	if (dst.x == ALLREGION) {
		d.x = x;
		d.y = y;
		d.w = image[frame].getWidth();
		d.h = image[frame].getHeight();
	}
	else {
		d.x = dst.x;
		d.y = dst.y;
		d.w = dst.w;
		d.h = dst.h;
	}
	image[frame].draw(s, d);
}
/******************/

Uint32 Object::changeFrame(Uint32 interval, void* param)
{
	Object* p = (Object*)param;

	if (p->time != 0)
	{
		p->frame = (p->frame + 1) % p->num;  // image frame	
		return interval;
	}
	else
	{
		return 0;
	}

}

void Object::startFrameTimer(Uint32 t)
{
	time = t;
	timerID = SDL_AddTimer(time, changeFrame, this); // Set Timer callback
}

void Object::stopFrameTimer()
{
	time = 0;
}

void Object::setCenterAngle(SDL_Point c, double a)
{
	for (int i = 0; i < num; i++) {
		image[i].setCenterAngle(c, a);
	}
}

void Object::setFlip(SDL_RendererFlip f)
{
	for (int i = 0; i < num; i++) {
		image[i].setFlip(f);
	}
}
int Object::getX()
{
	return x;
}
int Object::getY()
{
	return y;
}
void Object::setAlpha(int a)
{
	for (int i = 0; i < num; i++) {
		image[i].setAlpha(a);
	}
}

double Object::getAngle()
{
	return image[0].getAngle();
}
int Object::getAlpha()
{
	return image[0].getAlpha();
}
void Object::setShownFlag(bool b)
{
	shownFlag = b;
}
bool Object::getShownFlag()
{
	return shownFlag;
}
