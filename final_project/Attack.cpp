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
	
	if (shownFlag && ii )
		image.draw();
}
/*
void Attack::draw(SDL_Rect s, SDL_Rect d) {
	if(shownFlag)
		Object::draw(s, d);
}
*/
void Attack::startTimerLine(Uint32 t) {
	ii = 0;
	time = t;
	timerID = SDL_AddTimer(time, changeDataLine, this);
}

void Attack::startTimerParabola(Uint32 t) {
	ii = 0;
	time = t;
	timerID = SDL_AddTimer(time, changeDataParabola, this);
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

Uint32 Attack::changeDataParabola(Uint32 interval, void* param)
{
	Attack* p = (Attack*)param;
	if (p->time != 0 && p->shownFlag && p->ii <= 100)
	{
		if (p->ii <= 50)
		{
			p->ii++;
			p->vy += 1;
			p->x += p->dir * p->vx;
			p->y += p->vy;
			double angle = atan2(p->vy, p->dir * p->vx) * 180 / M_PI;
			printf("%lf\n", angle);
			p->setCenterAngle({0, 0}, atan2(p->vy, p->dir * p->vx) * 180 / M_PI);

			return interval;
		}
		else if(p->ii <= 100)
		{
			p->ii++;
			p->vy += 1;
			p->x += p->dir * p->vx;
			p->y += p->vy;
			double angle = atan2(p->vy, p->dir * p->vx) * 180 / M_PI;
			printf("%lf\n", angle);
			p->setCenterAngle({0, 0}, atan2(p->vy, p->dir * p->vx) * 180 / M_PI );
			return interval;
		}
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
}

bool Attack::getShownFlag() 
{
	return shownFlag;
}

void Attack::setDir(int d)
{
	dir = d;
//	if (dir == 1)
//		setFlip(SDL_FLIP_NONE);
//	if(dir == -1)
//		setFlip(SDL_FLIP_HORIZONTAL);

}

void Attack::setVy(int vyy)
{
	vy = vyy;
}

void Attack::setVx(int vxx)
{
	vx = vxx;
}

SDL_Point Attack::getSelfCenter()
{
	return { getX() + getWidth() * 3/4, getY() + getHeight() / 2};
}