#include "MonsterI.h"

MonsterI::MonsterI(const char* path, int n, SDL_Renderer* ren) :Monster(path, n, ren)
{

}

MonsterI::MonsterI(const char* path, int n, SDL_Renderer* ren, Uint8 r, Uint8 g, Uint8 b) : Monster(path, n, ren, r, g, b)
{

}

void MonsterI::gotKey(AnimeObject2& mainch)
{
	if (getX() < mainch.getX() + mainch.getWidth() / SHRINK &&
		mainch.getX() < getX() + getWidth() / SHRINK &&
		getY() < mainch.getY() + mainch.getHeight() / SHRINK &&
		mainch.getY() < getY() + getHeight() / SHRINK &&
		mainch.getMapnum()==3)
	{

		setDeadFlag(true);
		mainch.setKey(true);
	}
}

void MonsterI::setMchptr(AnimeObject2& mainch)
{

}

void MonsterI::startAI(Uint32 t)
{

}

void MonsterI::stopAI()
{

}

