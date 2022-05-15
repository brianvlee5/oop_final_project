#include "Attack.h"

Attack::Attack()
	: Object()
{
}
Attack::Attack(const char* path, SDL_Renderer* ren)
	: Object(path, ren) 
{
	setShownFlag(false);
	velX = velY = 0;
	Mapnum = 0;
}

Attack::Attack(const char* path, int n, int hhn, int wwn, SDL_Renderer* ren)
	: Object(path, n, hhn, wwn, ren) 
{
	setShownFlag(false);
	velX = velY = 0;
	Mapnum = 0;
}

Attack::Attack(const char* path, int n, int hhn, int wwn, SDL_Renderer* ren, Uint8 r, Uint8 g, Uint8 b)
	: Object(path, n, hhn, wwn, ren, r, g, b) 
{
	setShownFlag(false);
	velX = velY = 0;
	Mapnum = 0;
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

void Attack::startTimerBounce(Uint32 t) {
	ii = 0;
	time = t;
	timerID = SDL_AddTimer(time, changeDataBounce, this);
}

Uint32 Attack::getTime() {
	return time;
}

Uint32 Attack::changeDataLine(Uint32 interval, void* param)
{
	Attack* p = (Attack*)param;
	if ( p->time != 0 && p->ii <= 30 )
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

Uint32 Attack::changeDataParabola(Uint32 interval, void* param)
{
	Attack* p = (Attack*)param;
	if (p->time != 0 && p->ii <= 50)
	{
		if (p->ii <= 50)
		{
			p->ii++;
			p->velY += 1;
			p->move();
			double angle = atan2(p->velY, p->dir * p->velX) * 180 / M_PI;
//			printf("%lf\n", angle);
			p->setCenterAngle({ p->getWidth()/2, p->getHeight()/2}, angle);

			return interval;
		}
	}
	else
	{
		p->setShownFlag(false);
		return 0;
	}
}

Uint32 Attack::changeDataBounce(Uint32 interval, void* param)
{
	Attack* p = (Attack*)param;
	if (p->time != 0 && p->ii <= 120)
	{
		if (p->ii <= 120)
		{
			p->ii++;
			p->velY += 1;
			p->setdetectCorner();
			p->moveWithBounce();
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

void Attack::move() 
{
	setdetectCorner();
	moveOrNot();
}

void Attack::setdetectCorner()
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

void Attack::moveOrNot()
{

	if (dir * velX > 0)
	{
		if (xRight())
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
		if (xLeft())
		{
			x += dir * velX;
		}
		else
		{
			stopTimer();
		}
	}

	if (velY < 0)
	{
		if (yUp())
		{
			y += velY;
		}
		else
		{
			stopTimer();
		}
	}
	else if (velY > 0)
	{
		if (yDown())
		{
			y += velY;
		}
		else
		{
			stopTimer();
		}
	}
}

void Attack::moveWithBounce()
{

	if (dir * velX > 0)
	{
		if (tile[Mapnum][detectCornerX[1][1]][detectCornerX[1][0]] == 1 && tile[Mapnum][detectCornerX[3][1]][detectCornerX[3][0]] == 1)
		{
			stopTimer();
		}
		else
		{
			x += dir * velX;
		}
	}
	else if (dir * velX < 0)
	{
		if (tile[Mapnum][detectCornerX[0][1]][detectCornerX[0][0]] == 1 && tile[Mapnum][detectCornerX[2][1]][detectCornerX[2][0]] == 1)
		{
			stopTimer();
		}
		else
		{
			x += dir * velX;
		}
	}

	if (velY < 0)
	{
		if (yUp())
		{
			y += velY;
		}
		else
		{
			velY = 2 * VELOCITY;
		}
	}
	else if (velY > 0)
	{
		if (yDown())
		{
			y += velY;
		}
		else
		{
			velY = -2 * VELOCITY;
		}
	}
}

bool Attack::xRight()
{
	if (tile[Mapnum][detectCornerX[1][1]][detectCornerX[1][0]] == 1 || tile[Mapnum][detectCornerX[3][1]][detectCornerX[3][0]] == 1)
		return false;
	return true;
}
bool Attack::xLeft()
{
	if (tile[Mapnum][detectCornerX[2][1]][detectCornerX[2][0]] == 1 || tile[Mapnum][detectCornerX[0][1]][detectCornerX[0][0]] == 1)
		return false;
	return true;
}
bool Attack::yUp()
{
	if (tile[Mapnum][detectCornerY[1][1]][detectCornerY[1][0]] == 1 || tile[Mapnum][detectCornerY[0][1]][detectCornerY[0][0]] == 1)
		return false;
	return true;
}
bool Attack::yDown()
{
	if (tile[Mapnum][detectCornerY[2][1]][detectCornerY[2][0]] == 1 || tile[Mapnum][detectCornerY[3][1]][detectCornerY[3][0]] == 1)
		return false;
	return true;
}

void Attack::setMapFlag(bool f)
{
	mapFlag = f;
}
bool Attack::getMapFlag()
{
	return mapFlag;
}
void Attack::setMapnum(int n)
{
	Mapnum = n;
	printf("%d\n", Mapnum);
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
	velY = vyy;
}

void Attack::setVx(int vxx)
{
	velX = vxx;
}


void Attack::collision_mons(std::vector<Monster>& mv)
{
	for (int i = 0; i < mv.size(); i++)
	{
		if (!mv[i].getcdFlag() && shownFlag && !mv[i].getDeadFlag())
		{
			if (x < mv[i].getX() + mv[i].getWidth() / SHRINK &&
				mv[i].getX() < x + getWidth() / SHRINK &&
				y < mv[i].getY() + mv[i].getHeight() / SHRINK &&
				mv[i].getY() < y + getHeight() / SHRINK)
			{
				mv[i].setHP(mv[i].getHP() - 10);
				stopTimer();
				printf("%d HP remain: %d\n", i, mv[i].getHP());
				if (mv[i].getHP() > 0)
				{
					mv[i].startCD(300);
				}
				else
				{
					mv[i].setDeadFlag(true);
				}
				
				
			}
		}
	}
}