#include "Attack.h"

/* About Initialization */
Attack::Attack()
	: Object()
{
	initialize();
}
Attack::Attack(const char* path, SDL_Renderer* ren)
	: Object(path, ren) 
{
	initialize();
}
Attack::Attack(const char* path, SDL_Renderer* ren, Uint8 r, Uint8 g, Uint8 b)
	: Object(path, ren, r, g, b)
{
	initialize();
}
Attack::Attack(const char* path, int n, SDL_Renderer* ren)
	: Object(path, n, ren) 
{
	initialize();
}
Attack::Attack(const char* path, int n, SDL_Renderer* ren, Uint8 r, Uint8 g, Uint8 b)
	: Object(path, n, ren, r, g, b) 
{
	initialize();
}
void Attack::initialize()
{
	setShownFlag(false);
	velX = velY = 0;
	Mapnum = 0;
	pause = false;
	cd_count = ROTATECD / ROTATETIMER;
	rotateFlag = true;
}
/************************/

/* Draw Functions */
void Attack::draw() 
{
	if (ii) 
		Object::draw();
}
void Attack::draw(SDL_Rect src, SDL_Rect dst)
{
	if (ii)
		Object::draw(src, dst);
}
/******************/

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

void Attack::startTimerRotate(Uint32 t, int r, double d)
{
	if (rotateFlag) {
		ii = 0;
		phase_angle = d;
		radius = r;
		time = t;
		startRotateCoolDown(ROTATETIMER);
		timerID = SDL_AddTimer(time, changeDataRotate, this);
	}
}

void Attack::startRotateCoolDown(Uint32 t)
{
	cd = t;
	cd_count = 0;
	rotateFlag = false;
	cd_ID = SDL_AddTimer(cd, rotateCD, this);
}

Uint32 Attack::getTime() {
	return time;
}

Uint32 Attack::changeDataLine(Uint32 interval, void* param)
{
	Attack* p = (Attack*)param;
	if ( p->time != 0 && p->ii <= 30 )
	{
		if (p->pause == false)
		{
			p->ii++;
			p->move();
			return interval;
		}
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
		if (p->pause == false)
		{
			p->ii++;
			p->velY += 1;
			p->move();
			double angle = atan2(p->velY, p->dir * p->velX) * 180 / M_PI;
//			printf("%lf\n", angle);
			p->setCenterAngle({ p->getWidth() / 2, p->getHeight() / 2 }, angle);
		}
			return interval;
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
	if (p->time != 0 && p->ii <= 70)
	{
		if (p->pause ==false)
		{
			p->ii++;
			p->velY += 1;
			p->setdetectCorner();
			p->moveWithBounce();
		}
		return interval;
	}
	else
	{
		p->setShownFlag(false);
		return 0;
	}
}

Uint32 Attack::changeDataRotate(Uint32 interval, void* param)
{
	Attack* p = (Attack*)param;
	if (p->time != 0)
	{
		if (p->pause == false)
		{
			p->ii++;

			p->phase_angle = fmod(p->phase_angle + 5, 360);
			p->setCenterAngle({ p->getWidth() / 2, p->getHeight() / 2 }, p->phase_angle * M_PI / 180);
			p->setPosition(p->center.x + p->radius * cos(p->phase_angle * M_PI / 180), p->center.y + p->radius * sin(p->phase_angle * M_PI / 180));

		}
		return interval;
	}
	else
	{
		p->setShownFlag(false);
		return 0;
	}
}

Uint32 Attack::rotateCD(Uint32 interval, void* param)
{
	Attack* p = (Attack*)param;

	if (p->cd_count < ROTATECD / ROTATETIMER)
	{
		p->cd_count++;
		return interval;
	}
	else
	{
		p->rotateFlag = true;
		return 0;
	}
}

void Attack::stopTimer()
{
	time = 0;
}

void Attack::removeTimerID()
{
	SDL_RemoveTimer(timerID);
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
}

void Attack::setDir(int d)
{
	dir = d;
//	if (dir == 1)
//		setFlip(SDL_FLIP_NONE);
//	if(dir == -1)
//		setFlip(SDL_FLIP_HORIZONTAL);
}

void Attack::setPause(bool f)
{
	pause = f;
}

void Attack::setCharacterCenter(int x, int y)
{
	center.x = x;
	center.y = y;
}

int Attack::getRushCD()
{
	return cd_count;
	
}

bool Attack::getRotateFlag()
{
	return rotateFlag;
}



void Attack::collision_mons(std::vector<MonsterA>& mv)
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
					mv[i].startCD(200);
				}
				else
				{
					mv[i].setDeadFlag(true);
				}
				
				
			}
		}
	}
}

void Attack::collision_mons(std::vector<Monster*>& mv, AnimeObject2& mainch)
{
	for (int i = 0; i < mv.size(); i++)
	{
		if (!mv[i]->getcdFlag() && shownFlag && !mv[i]->getDeadFlag())
		{
			if (x < mv[i]->getX() + mv[i]->getWidth() / SHRINK &&
				mv[i]->getX() < x + getWidth() / SHRINK &&
				y < mv[i]->getY() + mv[i]->getHeight() / SHRINK &&
				mv[i]->getY() < y + getHeight() / SHRINK)
			{
				mv[i]->setHP(mv[i]->getHP() - 10);
				stopTimer();
				printf("%d HP remain: %d\n", i, mv[i]->getHP());
				if (mv[i]->getHP() > 0)
				{
					mv[i]->startCD(200);
				}
				else
				{
					mv[i]->setDeadFlag(true);
					mainch.setCoin(mainch.getCoin() + 1);
					printf("coins remain: %d\n", mainch.getCoin());
				}


			}
		}
	}
}