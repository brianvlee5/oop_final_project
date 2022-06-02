#include "Test.h"

/* About Initialization */
Test::Test()
	: Object()
{
	initialize();
}
Test::Test(const char* path, SDL_Renderer* ren)
	: Object(path, ren)
{
	initialize();
}
Test::Test(const char* path, SDL_Renderer* ren, Uint8 r, Uint8 g, Uint8 b)
	: Object(path, ren, r, g, b)
{
	initialize();
}
Test::Test(const char* path, int n, SDL_Renderer* ren)
	: Object(path, n, ren)
{
	initialize();
}
Test::Test(const char* path, int n, SDL_Renderer* ren, Uint8 r, Uint8 g, Uint8 b)
	: Object(path, n, ren, r, g, b)
{
	initialize();
}
void Test::initialize()
{
	setShownFlag(false);
	velX = velY = 0;
	dir = 1;
}
/************************/

/* Draw Functions */
/*
void Test::draw()
{
	if (shownFlag && ii)
		Role::draw();
}

void Test::draw_src(SDL_Rect src)
{
	if (shownFlag && ii)
		Object::draw_src(src);
}
void Test::draw_dst(SDL_Rect dst)
{
	if (shownFlag && ii)
		Object::draw_dst(dst);
}

void Test::draw(SDL_Rect src, SDL_Rect dst)
{
	if (shownFlag && ii)
		Object::draw(src, dst);
}
*/
/******************/

void Test::startTimerLine(Uint32 t) {
	ii = 0;
	time = t;
	timerID = SDL_AddTimer(time, changeDataLine, this);
}

void Test::startTimerParabola(Uint32 t) {
	ii = 0;
	time = t;
	timerID = SDL_AddTimer(time, changeDataParabola, this);
}


Uint32 Test::getTime() {
	return time;
}

Uint32 Test::changeDataLine(Uint32 interval, void* param)
{
	Test* p = (Test*)param;
	if (p->time != 0 && p->ii <= 30)
	{
		p->ii++;
		p->move();
		return interval;
	}
	else
	{
		p->setShownFlag(false);
		return 0;
	}
}

Uint32 Test::changeDataParabola(Uint32 interval, void* param)
{
	Test* p = (Test*)param;
	if (p->time != 0 && p->ii <= 50)
	{
		if (p->ii <= 50)
		{
			p->ii++;
			p->velY += 1;
			p->move();
			double angle = atan2(p->velY, p->dir * p->velX) * 180 / M_PI;
			//			printf("%lf\n", angle);
			p->setCenterAngle({ p->getWidth() / 2, p->getHeight() / 2 }, angle);

			return interval;
		}
	}
	else
	{
		p->setShownFlag(false);
		return 0;
	}
}


void Test::stopTimer()
{
	time = 0;
}

void Test::move()
{
	moveOrNot();
}
/*
void Test::setdetectCorner()
{
	if (dir * velX >= 0)
	{
		detectCornerX[0][0] = x * MAPTILEX / WIDTH;//up leftx
		detectCornerX[0][1] = y * MAPTILEY / HEIGHT;//      y
		detectCornerX[1][0] = (getWidth() / SHRINK + x + 0 * dir * velX) * MAPTILEX / WIDTH;//up right
		detectCornerX[1][1] = y * MAPTILEY / HEIGHT;
		detectCornerX[2][0] = x * MAPTILEX / WIDTH;//bottom left
		detectCornerX[2][1] = (getHeight() / SHRINK + y) * MAPTILEY / HEIGHT;
		detectCornerX[3][0] = (getWidth() / SHRINK + x + 0 * dir * velX) * MAPTILEX / WIDTH;//bottom right
		detectCornerX[3][1] = (getHeight() / SHRINK + y) * MAPTILEY / HEIGHT;
	}
	else if (dir * velX < 0)
	{
		detectCornerX[0][0] = (x + 0 * dir * velX) * MAPTILEX / WIDTH;//up leftx
		detectCornerX[0][1] = y * MAPTILEY / HEIGHT;//      y
		detectCornerX[1][0] = (getWidth() / SHRINK + x) * MAPTILEX / WIDTH;//up right
		detectCornerX[1][1] = y * MAPTILEY / HEIGHT;
		detectCornerX[2][0] = (x + 0 * dir * velX) * MAPTILEX / WIDTH;//bottom left
		detectCornerX[2][1] = (getHeight() / SHRINK + y) * MAPTILEY / HEIGHT;
		detectCornerX[3][0] = (getWidth() / SHRINK + x) * MAPTILEX / WIDTH;//bottom right
		detectCornerX[3][1] = (getHeight() / SHRINK + y) * MAPTILEY / HEIGHT;
	}

	if (velY <= 0)
	{
		detectCornerY[0][0] = (x)*MAPTILEX / WIDTH;//up leftx
		detectCornerY[0][1] = (y + 0 * velY) * MAPTILEY / HEIGHT;//      y
		detectCornerY[1][0] = (getWidth() / SHRINK + x) * MAPTILEX / WIDTH;//up right
		detectCornerY[1][1] = (y + 0 * velY) * MAPTILEY / HEIGHT;
		detectCornerY[2][0] = (x)*MAPTILEX / WIDTH;//bottom left
		detectCornerY[2][1] = (getHeight() / SHRINK + y) * MAPTILEY / HEIGHT;
		detectCornerY[3][0] = (getWidth() / SHRINK + x) * MAPTILEX / WIDTH;//bottom right
		detectCornerY[3][1] = (getHeight() / SHRINK + y) * MAPTILEY / HEIGHT;
	}
	else if (velY > 0)
	{
		detectCornerY[0][0] = (x)*MAPTILEX / WIDTH;//up leftx
		detectCornerY[0][1] = y * MAPTILEY / HEIGHT;//      y
		detectCornerY[1][0] = (getWidth() / SHRINK + x) * MAPTILEX / WIDTH;//up right
		detectCornerY[1][1] = y * MAPTILEY / HEIGHT;
		detectCornerY[2][0] = (x)*MAPTILEX / WIDTH;//bottom left
		detectCornerY[2][1] = (getHeight() / SHRINK + (y + 0 * velY)) * MAPTILEY / HEIGHT;
		detectCornerY[3][0] = (getWidth() / SHRINK + x) * MAPTILEX / WIDTH;//bottom right
		detectCornerY[3][1] = (getHeight() / SHRINK + (y + 0 * velY)) * MAPTILEY / HEIGHT;
	}
}
*/
void Test::moveOrNot()
{

	if (dir * velX > 0)
	{
		if (x + getWidth() < WIDTH)
		{
			x += dir * velX;
		}
		else
		{
			stopTimer();
		}
	}
	else if (dir * velX < 0)
	{
		if (x > 0)
		{
			x += dir * velX;
		}
		else
		{
			stopTimer();
		}
	}
	if (y + getHeight() < HEIGHT)
	{
		y += velY;
	}
	else
	{
		stopTimer();
	}
	/*
	if (velY > 0)
	{
		if (y + getHeight() < HEIGHT)
		{
			y += velY;
		}
		else
		{
			stopTimer();
		}
	}
	else if (y<0)
	{

		if (yDown())
		{
			y += velY;
		}
		else
		{
			stopTimer();
		}
	}*/
}



bool Test::xRight()
{
	return true;
}
bool Test::xLeft()
{
	return true;
}
bool Test::yUp()
{
	return true;
}
bool Test::yDown()
{
	return true;
}

void Test::setDir(int d)
{
	dir = d;
}

