#include "Attack.h"

Attack::Attack()
	: Object()
{
}
Attack::Attack(const char* path, SDL_Renderer* ren)
	: Object(path, ren) 
{
	setShownFlag(false);
}

Attack::Attack(const char* path, int n, int hhn, int wwn, SDL_Renderer* ren)
	: Object(path, n, hhn, wwn, ren) 
{
	setShownFlag(false);
}

Attack::Attack(const char* path, int n, int hhn, int wwn, SDL_Renderer* ren, Uint8 r, Uint8 g, Uint8 b)
	: Object(path, n, hhn, wwn, ren, r, g, b) 
{
	setShownFlag(false);
}

Attack Attack::set(const char* path, int n, int hhn, int wwn, SDL_Renderer* ren, Uint8 r, Uint8 g, Uint8 b)
{
	return Attack(path, n, hhn, wwn, ren, r, g, b);
}

void Attack::draw() {
	if (shownFlag)
		Object::draw();
}

void Attack::draw(SDL_Rect d)
{

	int wc = frame % wn;
	int hc = frame / wn;

	SDL_Rect s;
	s.x = getWidth() * wc;
	s.y = getHeight() * hc;
	s.w = getWidth();
	s.h = getHeight();

	image.setSrcRegion(s);
	image.setDstRegion(d);
	
	if (shownFlag)
		image.draw();
}
/*
void Attack::draw(SDL_Rect s, SDL_Rect d) {
	if(shownFlag)
		Object::draw(s, d);
}
*/
void Attack::startTimerLine(Uint32 t) {
	time = t;
	timerID = SDL_AddTimer(time, changeDataLine, this);
}

Uint32 Attack::getTime() {
	return time;
}

Uint32 Attack::changeDataLine(Uint32 interval, void* param)
{
	Attack* p = (Attack*)param;
	if ( p->time != 0 && p->shownFlag  && p->ii <= 30 )
	{
		p->ii++;
		p->setPosition(p->getX() + 2*p->dir*VELOCITY, p->getY());
		return interval;
	}
	else
	{
		p->setShownFlag(false);
		return 0;
	}
}

void Attack::stopTimer()
{
	time = 0;
}

void Attack::setShownFlag(bool b) 
{
	shownFlag = b;
	if(b)
		ii = 0;
}

bool Attack::getShownFlag() 
{
	return shownFlag;
}

void Attack::setDir(int d)
{
	dir = d;
	if (dir == 1)
		setFlip(SDL_FLIP_NONE);
	if(dir == -1)
		setFlip(SDL_FLIP_HORIZONTAL);

}