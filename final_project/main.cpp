#include "main.h"

using namespace std;

SDL_Texture* texture = NULL;

void spacial_hash(const vector<Monster>& Mv, vector<vector<Monster>>& MvM)
{
	for (int i = 0; i < Mv.size(); i++)
	{
		//0 -> 1st quadrant, and so on
		if (Mv[i].getX() < WIDTH / 2 && Mv[i].getY() < HEIGHT / 2)
			MvM[0].push_back(Mv[i]);
		else if (Mv[i].getX() >= WIDTH / 2 && Mv[i].getY() < HEIGHT / 2)
			MvM[1].push_back(Mv[i]);
		else if (Mv[i].getX() < WIDTH / 2 && Mv[i].getY() >= HEIGHT / 2)
			MvM[2].push_back(Mv[i]);
		else
			MvM[3].push_back(Mv[i]);
	}
}

int main(int argc, char* args[])
{
	System sdl;
	if (!sdl.init())
	{
		printf("Failed to initialize SDL system!\n");
		return -1;
	}
	RenderWindow window("Elden's rOng", 300, 170, WINDOWW, WINDOWH);
	const int num=6;
	Coordinate coord, coo[num], enemycord[3];
	vector<Monster> monsv;
	vector<vector<Monster>> hash_monsv;
	SDL_Rect forpooh;//for pooh's move
	AnimeObject panda("../images/panda/", 4, window.getRenderer(), 0xFF, 0xFF, 0xFF);
	AnimeObject2 pan("../images/panda.png", 4, 1, 4, window.getRenderer(), 0xFF, 0xFF, 0xFF);
	AnimeObject2 p("../images/panda.png", window.getRenderer());
	Attack fire[num] = { Attack("../images/fire1.png", 1, 1, 1, window.getRenderer(), 0x00, 0x00, 0x00),
					   Attack("../images/fire1.png", 1, 1, 1, window.getRenderer(), 0x00, 0x00, 0x00),
					   Attack("../images/fire1.png", 1, 1, 1, window.getRenderer(), 0x00, 0x00, 0x00),
					   Attack("../images/fire1.png", 1, 1, 1, window.getRenderer(), 0x00, 0x00, 0x00),
					   Attack("../images/fire1.png", 1, 1, 1, window.getRenderer(), 0x00, 0x00, 0x00),
					   Attack("../images/fire1.png", 1, 1, 1, window.getRenderer(), 0x00, 0x00, 0x00)
	};

	for (int i = 0; i < 3; i++)
	{
		Monster enemy("../images/pooh/", 22, window.getRenderer(), 0xFF, 0xFF, 0xFF);
		enemy.setPosition(MonstP[i].x, MonstP[i].y);
		monsv.push_back(enemy);
	}

	
	for (int i = 0; i < 4; i++)
	{
		vector<Monster> v;
		hash_monsv.push_back(v);
	}

	Map demo1;
	demo1.set("../images/map/mapdemo", window.getRenderer());
	pan.setPosition(demo1.startL[demo1.getmapnum()].x, demo1.startL[demo1.getmapnum() ].y);
	SDL_Event e;

	bool quit = false;
	while (!quit)
	{
		
		while (SDL_PollEvent(&e) != 0)
		{
			if (e.type == SDL_QUIT)
				quit = true;
			poohKeyboard(e, pan);
			attackKeyboard(e, fire, pan);
		}
		
		pan.move();
		
		for (int i = 0; i < 3; i++)
		{
			monsv[i].AIstart(pan);
			
		}
		demo1.setcamera(pan);
		demo1.changemap(pan);


		window.clear();
		coord.calMapCamera(demo1, pan);
		for (int i = 0; i < 6; i++)
			coo[i].calMap(demo1, fire[i]);
		
		for (int i = 0; i < 4; i++)
			hash_monsv[i].clear();

		for (int i = 0; i < 3; i++)
		{
			spacial_hash(monsv, hash_monsv);
		}
			

		demo1.draw({ ALLREGION }, demo1.getcamera());
		pan.draw({ coord.getpCX(),coord.getpCY(),pan.getWidth() / SHRINK ,pan.getHeight() / SHRINK });
		
		for (int i = 0; i < 3; i++)
		{
			enemycord[i].calMapCamera(demo1, monsv[i]);
			monsv[i].draw({ enemycord[i].getpCX(),enemycord[i].getpCY(),monsv[i].getWidth() / SHRINK,monsv[i].getHeight() / SHRINK}, {NULL});
		}

		/*for (int i = 0; i < 3; i++)
		{
			monsv[i].collisionAABB(pan);
		}*/

		
		int tempmonv;
		switch (pan.getX() * 2 / WIDTH + pan.getY() * 2 / HEIGHT * 2)
		{
		case 0:
			tempmonv = 0;
			break;
		case 1:
			tempmonv = 1;
			break;
		case 2:
			tempmonv = 2;
			break;
		case 3:
			tempmonv = 3;
			break;
		}

		for (int i = 0; i < hash_monsv[tempmonv].size(); i++)
		{
			hash_monsv[tempmonv][i].collisionAABB(pan);
		}

		for (int i = 0; i < num; i++)
			fire[i].draw({ coo[i].getpCX(),coo[i].getpCY(),fire[i].getWidth(),fire[i].getHeight() });
		window.display();
	}
	SDL_DestroyTexture(texture);
	pan.close();
	demo1.close();

	for (int i = 0; i < 3; i++)
		monsv[i].close();

	for(int i=0; i<num; i++)
		fire[i].close();
	window.close();
	sdl.close();
	

	return 0;
}



