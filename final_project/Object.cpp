#include "Object.h"
Object::Object(const char* path, SDL_Renderer* ren)
{
	image.setPath(path);
	image.setRenderer(ren);
	image.setColorKey(NO_TRANSPARENT_BG);
	image.setCenterAngle({ 0,0 }, 0);
	image.setFlip(SDL_FLIP_NONE);
	image.setAlpha(255);

	image.generateTexture();

	renderer = ren;
	num = 1;
	frame = 0;
	hn = 1;
	wn = 1;
}

Object::Object(const char* path, int n, int hhn, int wwn, SDL_Renderer* ren)
{
	image.setPath(path);
	image.setRenderer(ren);
	image.setColorKey(NO_TRANSPARENT_BG);
	image.setCenterAngle({ 0,0 }, 0);
	image.setFlip(SDL_FLIP_NONE);
	image.setAlpha(255);

	image.generateTexture();

	renderer = ren;
	num = n;
	frame = 0;
	hn = hhn;
	wn = wwn;
}

Object::Object(const char* path, int n, int hhn, int wwn, SDL_Renderer* ren, Uint8 r, Uint8 g, Uint8 b)
{
	image.setPath(path);
	image.setRenderer(ren);
	image.setColorKey({ r, g, b, 255 });
	image.setCenterAngle({ 0,0 }, 0);
	image.setFlip(SDL_FLIP_NONE);
	image.setAlpha(255);

	image.generateTexture();

	renderer = ren;
	num = n;
	frame = 0;
	hn = hhn;
	wn = wwn;
}

void Object::close()
{
	// Free loaded image	
	image.close();

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
	return image.getWidth() / wn;
}

int Object::getHeight()
{
	return image.getHeight() / hn;
}

void Object::draw()
{
	int wc = frame % wn;
	int hc = frame / wn;

	SDL_Rect s, d;
	s.x = getWidth() * wc;
	s.y = getHeight() * hc;
	s.w = getWidth();
	s.h = getHeight();
	d.x = x;
	d.y = y;
	d.w = s.w;
	d.h = s.h;

	image.setSrcRegion(s);
	image.setDstRegion(d);

	image.draw();
}

void Object::draw(SDL_Rect s, SDL_Rect d)
{

	image.setSrcRegion(s);
	image.setDstRegion(d);

	image.draw();
}

Uint32 Object::changeData(Uint32 interval, void* param)
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

void Object::startTimer(Uint32 t)
{
	time = t;
	timerID = SDL_AddTimer(time, changeData, this); // Set Timer callback
}

void Object::stopTimer()
{
	time = 0;
}

void Object::setCenterAngle(SDL_Point c, double a)
{
	image.setCenterAngle(c, a);
}

void Object::setFlip(SDL_RendererFlip f)
{
	image.setFlip(f);
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
	image.setAlpha(a);
}

double Object::getAngle()
{
	return image.getAngle();
}

int Object::getAlpha()
{
	return image.getAlpha();
}

// New in this example
Object::~Object()
{
	close();
}
