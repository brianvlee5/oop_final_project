#include "GSManager.h"

//global functions
static void pauseEvents(SDL_Event e, GSManager* gsm, int& state, AnimeObject2& mch, vector<Attack>& atk)
{
	MainchSave mchsave;
	MapSave mapsave;
	int x, y;
	if (e.type == SDL_KEYDOWN && e.key.repeat == 0)
	{
		switch (e.key.keysym.sym)
		{
		case SDLK_ESCAPE:
			if (state == PLAY)
			{
				for (int i = 0; i < atk.size(); i++)
					atk[i].setPause(true);
				state = PAUSE;
			}
			else if (state == PAUSE)
			{
				for (int i = 0; i < atk.size(); i++)
					atk[i].setPause(false);
				state = PLAY;
			}
			break;
			/*
		case SDLK_p:
			if (state == PLAY)
			{
				state = BACKPACK;
			}
			else if (state == BACKPACK)
			{
				state = PLAY;
			}
			*/
		}

	}
	else if (e.type == SDL_KEYUP && e.key.repeat == 0)
	{
		switch (e.key.keysym.sym)
		{

		}
	}

	if (e.type == SDL_MOUSEBUTTONUP)
	{
		SDL_GetMouseState(&x, &y);
		if (e.button.button == SDL_BUTTON_LEFT && x >= (WINDOWW / 2 - 150) && x <= (WINDOWW / 2 + 100) && y >= (WINDOWH / 2) && y <= (WINDOWH / 2 + 50))//resume
		{
			state = PLAY;
		}
		if (e.button.button == SDL_BUTTON_LEFT && x >= (WINDOWW / 2 - 150) && x <= (WINDOWW / 2 + 100) && y >= (WINDOWH / 2 + 45) && y <= (WINDOWH / 2 + 95))//menu
		{
			gsm->setGameState(MAINMENU);
		}
		if (e.button.button == SDL_BUTTON_LEFT && x >= (WINDOWW / 2 - 150) && x <= (WINDOWW / 2 + 100) && y >= (WINDOWH / 2 - 80) && y <= (WINDOWH / 2 - 30))//save
		{
			FILE* fsave;
			fopen_s(&fsave, "../saves/slot1.dat", "wb");
			if (!fsave)
				printf("open file fail\n");

			mchsave.health = mch.getHP();
			mchsave.mapnum = mch.getMapnum();
			mchsave.x = mch.getX();
			mchsave.y = mch.getY();
			mapsave.mapnum = mch.getMapnum();

			fwrite(&mchsave, sizeof(MainchSave), 1, fsave);
			fwrite(&mapsave, sizeof(mapsave), 1, fsave);
			fclose(fsave);
			state = PLAY;

		}
	}
}

static void MenuEvents(SDL_Event e, GSManager* gsm, int& state)
{
	int x, y;


	if (e.type == SDL_MOUSEBUTTONUP)
	{
		SDL_GetMouseState(&x, &y);
		switch (state)
		{
		case MENU:
		{
			if (e.button.button == SDL_BUTTON_LEFT && x >= (WINDOWW / 2 - 150) && x <= (WINDOWW / 2 + 100) && y >= (WINDOWH / 2) && y <= (WINDOWH / 2 + 50))
			{
				gsm->setGameState(GAMEPLAY);
			}
			else if (e.button.button == SDL_BUTTON_LEFT && x >= (WINDOWW / 2 - 150) && x <= (WINDOWW / 2 + 100) && y >= (WINDOWH / 2 + 45) && y <= (WINDOWH / 2 + 95))
			{
				state = LOAD;
			}
			break;
		}
		case LOAD:
		{
			if (e.button.button == SDL_BUTTON_LEFT && x >= (WINDOWW / 2 - 150) && x <= (WINDOWW / 2 + 100) && y >= (WINDOWH / 2 + 110) && y <= (WINDOWH / 2 + 150))//back
			{
				state = MENU;
			}
			if (e.button.button == SDL_BUTTON_LEFT && x >= (WINDOWW / 2 - 150) && x <= (WINDOWW / 2 + 100) && y >= (WINDOWH / 2) && y <= (WINDOWH / 2 + 40))//slot1
			{
				gsm->setGameState(LOADGAMEPLAY);
			}
			break;
		}
		}
	}
}

//class GSManager

GSManager::GSManager()
{
	quit = false;
	GameState = GAMEPLAY;
}

void GSManager::InitMonsters(std::vector<Monster*>& mv, RenderWindow& window)
{


}

void GSManager::startGame(RenderWindow& window)
{
	while (!quit)
	{
		switch (GameState)
		{
		case MAINMENU:
		{
			MainMenu(window);
			break;
		}
		case GAMEPLAY:
		{
			GamePlay(window);
			break;
		}
		case LOADGAMEPLAY:
		{
			LoadGamePlay(window);
			break;
		}

		}
	}
}

void GSManager::MainMenu(RenderWindow& window)
{
	Object mainmenu("../images/mapdemo1.png", window.getRenderer());
	Text NewGame("New Game", "../fonts/akabara-cinderella.ttf", 60, TTF_STYLE_BOLD, { 0, 255, 255 }, BLENDED, { 100, 100, 100 }, window.getRenderer(), { WINDOWW / 2 - 150, WINDOWH / 2 }, { NULL, NULL }, NULL, SDL_FLIP_NONE, 100);
	Text Load("load", "../fonts/akabara-cinderella.ttf", 60, TTF_STYLE_BOLD, { 0, 255, 255 }, BLENDED, { 100, 100, 100 }, window.getRenderer(), { WINDOWW / 2 - 150, WINDOWH / 2 + 45 }, { NULL, NULL }, NULL, SDL_FLIP_NONE, 100);
	Text Back("back", "../fonts/akabara-cinderella.ttf", 60, TTF_STYLE_BOLD, { 0, 255, 255 }, BLENDED, { 100, 100, 100 }, window.getRenderer(), { WINDOWW / 2 - 150, WINDOWH / 2 + 110 }, { NULL, NULL }, NULL, SDL_FLIP_NONE, 100);
	Text Slot1("Slot1", "../fonts/akabara-cinderella.ttf", 60, TTF_STYLE_BOLD, { 0, 255, 255 }, BLENDED, { 100, 100, 100 }, window.getRenderer(), { WINDOWW / 2 - 150, WINDOWH / 2 }, { NULL, NULL }, NULL, SDL_FLIP_NONE, 100);


	int state = MENU;


	while (!quit && GameState == MAINMENU)
	{
		while (SDL_PollEvent(&ev) != 0)
		{
			if (ev.type == SDL_QUIT)
				quit = true;
			MenuEvents(ev, this, state);
		}
		window.clear();
		mainmenu.draw({ ALLREGION }, { ALLREGION });

		switch (state)
		{
		case MENU:
		{
			NewGame.draw();
			Load.draw();
			break;
		}
		case LOAD:
		{
			Slot1.draw();
			Back.draw();
			break;
		}
		}



		window.display();
	}
	Slot1.close();
	Back.close();
	Load.close();
	NewGame.close();
	mainmenu.close();
}

void GSManager::GamePlay(RenderWindow& window)
{
	int state = 0;
	Coordinate coord, coo[6], enemycord[3], enemyhp[3], keycord, tempcord;



	Text fail("Game Over", "../fonts/akabara-cinderella.ttf", 60, TTF_STYLE_BOLD, { 0, 255, 255 }, BLENDED, { 100, 100, 100 }, window.getRenderer(), { WINDOWW / 2 - 150, WINDOWH / 2 }, { NULL, NULL }, NULL, SDL_FLIP_NONE, 100);
	Text resume("resume", "../fonts/akabara-cinderella.ttf", 60, TTF_STYLE_BOLD, { 0, 255, 255 }, BLENDED, { 100, 100, 100 }, window.getRenderer(), { WINDOWW / 2 - 100, WINDOWH / 2 - 30 }, { NULL, NULL }, NULL, SDL_FLIP_NONE, 100);
	Text menu("menu", "../fonts/akabara-cinderella.ttf", 60, TTF_STYLE_BOLD, { 0, 255, 255 }, BLENDED, { 100, 100, 100 }, window.getRenderer(), { WINDOWW / 2 - 70, WINDOWH / 2 + 15 }, { NULL, NULL }, NULL, SDL_FLIP_NONE, 100);
	Text save("save", "../fonts/akabara-cinderella.ttf", 60, TTF_STYLE_BOLD, { 0, 255, 255 }, BLENDED, { 100, 100, 100 }, window.getRenderer(), { WINDOWW / 2 - 70, WINDOWH / 2 - 80 }, { NULL, NULL }, NULL, SDL_FLIP_NONE, 100);
	Text slot1("Slot1", "../fonts/akabara-cinderella.ttf", 60, TTF_STYLE_BOLD, { 0, 255, 255 }, BLENDED, { 100, 100, 100 }, window.getRenderer(), { WINDOWW / 2 - 70, WINDOWH / 2 + 15 }, { NULL, NULL }, NULL, SDL_FLIP_NONE, 100);
	Text back("back", "../fonts/akabara-cinderella.ttf", 60, TTF_STYLE_BOLD, { 0, 255, 255 }, BLENDED, { 100, 100, 100 }, window.getRenderer(), { WINDOWW / 2 - 70, WINDOWH / 2 + 75 }, { NULL, NULL }, NULL, SDL_FLIP_NONE, 100);


	AnimeObject2 pan("../images/panda/", 4, window.getRenderer(), 0xFF, 0xFF, 0xFF);
	//MonsterI thekey("../images/Key", 1, window.getRenderer(), 0xFF, 0xFF, 0xFF);
	vector<Attack> fire; // (6, Attack("../images/attack/fire2.png", 1, 1, 1, window.getRenderer(), 0xFF, 0xFF, 0xFF));
	Object h("../images/heart.png", window.getRenderer(), 0xFF, 0xFF, 0xFF);
	Object prop("../images/frame.png", window.getRenderer(), 0xFF, 0xFF, 0xFF);
	Object key("../images/key.png", window.getRenderer(), 0xFF, 0xFF, 0xFF);
	vector<Object> prop_v;

	vector<MonsterA> tempa;
	vector<MonsterB> tempb;
	vector<MonsterC> tempc;
	vector<MonsterD> tempd;

	for (int i = 0; i < 3; i++)
	{
		MonsterA a("../images/MonsterA/", 4, window.getRenderer(), 0xFF, 0xFF, 0xFF);
		tempa.push_back(a);
	}
	for (int i = 0; i < 3; i++)
	{
		MonsterB b("../images/MonsterB/", 5, window.getRenderer(), 0xFF, 0xFF, 0xFF);
		tempb.push_back(b);
	}
	for (int i = 0; i < 2; i++)
	{
		MonsterC c("../images/MonsterC/", 6, window.getRenderer(), 0xFF, 0xFF, 0xFF);
		tempc.push_back(c);
	}
	for (int i = 0; i < 2; i++)
	{
		MonsterD d("../images/MonsterD/", 4, window.getRenderer(), 0xFF, 0xFF, 0xFF);
		tempd.push_back(d);
	}		
	vector<Monster*> Monsv;
	for (int i = 0; i < tempa.size(); i++)
		Monsv.push_back(&tempa[i]);
	for (int i = 0; i < tempb.size(); i++)
		Monsv.push_back(&tempb[i]);
	for (int i = 0; i < tempc.size(); i++)
		Monsv.push_back(&tempc[i]);
	for (int i = 0; i < tempd.size(); i++)
		Monsv.push_back(&tempd[i]);

	for (int i = 0; i < Monsv.size(); i++)
		Monsv[i]->setPosition((i + 5) * WIDTH / MAPTILEX, 36 * HEIGHT / MAPTILEY);

	h.setShownFlag(true);
	h.setPosition(0, 0);
	for (int i = 0; i < MAXHP; i++)
	{
		window.addVPregion({ {h.getWidth() / 2 * i, 0, h.getWidth() / 2, h.getHeight()} });
	}
	prop.setShownFlag(true);
	prop.setPosition(0, 0);
	for (int i = 0; i < PROPNUM; i++)
	{
		window.addVPregion({ {prop.getWidth() * i, h.getHeight() * 4 / 3, prop.getWidth() , prop.getHeight()} });
	}
	key.setShownFlag(true);
	key.setPosition(0, 0);

	prop_v.push_back(key);


	Map demo1;
	demo1.set("../images/map/map", window.getRenderer());
	window.addVPregion({ {WINDOWW / 6 * 5, 0, WINDOWW / 4, WINDOWH / 4} }); // VP: 
	pan.setPosition(demo1.startL[demo1.getmapnum()].x, demo1.startL[demo1.getmapnum()].y);

	//thekey.setPosition(21 * WIDTH / MAPTILEX, 31 * HEIGHT / MAPTILEY);


	for (int i = 0; i < Monsv.size(); i++)
	{
		Monsv[i]->setMchptr(pan);
		Monsv[i]->startAI(15);
	}

	for (int i = 0; i < 6; i++)
	{
		if (i == 2 || i == 3)
			fire.push_back(Attack("../images/fire2.png", window.getRenderer(), 0x00, 0x00, 0x00));
		else
			fire.push_back(Attack("../images/fire1.png", window.getRenderer(), 0x00, 0x00, 0x00));
	}
	while (!quit && GameState == GAMEPLAY)
	{

		while (SDL_PollEvent(&ev) != 0)
		{
			if (ev.type == SDL_QUIT)
				quit = true;
			pauseEvents(ev, this, state, pan, fire);
			if (state == PLAY)
			{
				poohKeyboard(ev, pan);
				attackKeyboard(ev, fire, pan);
			}
		}

		switch (state)
		{
		case PLAY:
		{
			window.clear();
			window.setVP(-1);
			pan.move();

			//			for (int i = 0; i < 3; i++)
			//			{
			//				if (!monsv[i].getDeadFlag())
			//					monsv[i].AIstate(pan);
			//				//monsv[i].StartWait(30);
			//			}
			demo1.setcamera(pan);



			coord.calMapCamera(demo1, pan);
			for (int i = 0; i < fire.size(); i++)
				coo[i].calMapCamera(demo1, fire[i]);



			demo1.draw({ ALLREGION }, demo1.getcamera());
			pan.draw({ ALLREGION }, { coord.getpCX(), coord.getpCY(), pan.getWidth() / SHRINK, pan.getHeight() / SHRINK });



			for (int i = 0; i < Monsv.size(); i++)
			{
				if (!Monsv[i]->getDeadFlag())
				{
					enemycord[0].calMapCamera(demo1, *Monsv[i]);
					Monsv[i]->draw({ enemycord[0].getpCX(),enemycord[0].getpCY(),Monsv[i]->getWidth() / SHRINK,Monsv[i]->getHeight() / SHRINK }, { ALLREGION });
				}
			}

			//thekey.gotKey(pan);
		//if (demo1.getmapnum() == 3)
		//{
		//	keycord.calMapCamera(demo1, thekey);
		//	thekey.draw({ keycord.getpCX(),keycord.getpCY(),thekey.getWidth() / SHRINK,thekey.getHeight() / SHRINK }, { ALLREGION });
		//}




			for (int i = 0; i < Monsv.size(); i++)
			{
				if (!Monsv[i]->getDeadFlag())
					Monsv[i]->collisionAABB(pan);
			}



			for (int i = 0; i < fire.size(); i++)
			{
				fire[i].collision_mons(Monsv);
			}

			for (int i = 0; i < fire.size(); i++)
				fire[i].draw({ ALLREGION }, { coo[i].getpCX(), coo[i].getpCY(), fire[i].getWidth(), fire[i].getHeight() });


			window.setVP(-1);
			if (pan.getDeadFlag())
			{
				fail.draw();
				window.display();
				system("pause");

				break;
			}


			for (int i = 0; i < MAXHP; i++) {
				window.setVP(i);
				h.draw({ h.getWidth() / 2, 0, h.getWidth() , h.getHeight() }, { 0, 0,h.getWidth() / 2, h.getHeight() });
			}
			for (int i = 0; i < pan.getHP(); i++) {
				window.setVP(i);
				h.draw();
			}
			for (int i = 0; i < PROPNUM; i++)
			{
				window.setVP(MAXHP + i);
				if (i == 0)
					prop_v[i].draw();
				prop.draw();

			}

			window.setVP(MAXHP + PROPNUM);
			demo1.draw({ 0, 0, WINDOWW / 6 , WINDOWW / 6 }, { ALLREGION });
			filledCircleColor(window.getRenderer(), (pan.getX() + pan.getWidth() / 2) / 12, (pan.getY() + pan.getHeight() / 2) / 8, 2, 0xFF0000FF);
			window.display();
			break;
		}
		case PAUSE:
		{
			demo1.draw({ ALLREGION }, demo1.getcamera());
			pan.draw({ ALLREGION }, { coord.getpCX(), coord.getpCY(), pan.getWidth() / SHRINK, pan.getHeight() / SHRINK });
			for (int i = 0; i < Monsv.size(); i++)
			{
				if (!Monsv[i]->getDeadFlag())
				{
					enemycord[i].calMapCamera(demo1, *Monsv[i]);
					Monsv[i]->draw({ enemycord[i].getpCX(),enemycord[i].getpCY(),Monsv[i]->getWidth() / SHRINK,Monsv[i]->getHeight() / SHRINK }, { ALLREGION });
				}
			}
			for (int i = 0; i < fire.size(); i++)
				fire[i].draw({ ALLREGION }, { coo[i].getpCX(), coo[i].getpCY(), fire[i].getWidth(), fire[i].getHeight() });
			for (int i = 0; i < MAXHP; i++) {
				window.setVP(i);
				h.draw({ h.getWidth() / 2, 0, h.getWidth() , h.getHeight() }, { 0, 0,h.getWidth() / 2, h.getHeight() });
			}
			for (int i = 0; i < pan.getHP(); i++) {
				window.setVP(i);
				h.draw();
			}
			for (int i = 0; i < PROPNUM; i++)
			{
				window.setVP(MAXHP + i);
				prop.draw();
			}
			window.setVP(MAXHP + PROPNUM);
			demo1.draw({ 0, 0, WINDOWW / 6 , WINDOWW / 6 }, { ALLREGION });
			filledCircleColor(window.getRenderer(), (pan.getX() + pan.getWidth() / 2) / 12, (pan.getY() + pan.getHeight() / 2) / 8, 2, 0xFF0000FF);

			window.setVP(-1);
			resume.draw();
			menu.draw();
			save.draw();
			window.display();

			break;
		}
		case SAVE:
		{
			demo1.draw({ ALLREGION }, demo1.getcamera());
			pan.draw({ ALLREGION }, { coord.getpCX(), coord.getpCY(), pan.getWidth() / SHRINK, pan.getHeight() / SHRINK });
			for (int i = 0; i < Monsv.size(); i++)
			{
				if (!Monsv[i]->getDeadFlag())
				{
					enemycord[i].calMapCamera(demo1, *Monsv[i]);
					Monsv[i]->draw({ enemycord[i].getpCX(),enemycord[i].getpCY(),Monsv[i]->getWidth() / SHRINK,Monsv[i]->getHeight() / SHRINK }, { ALLREGION });
				}
			}
			for (int i = 0; i < fire.size(); i++)
				fire[i].draw({ ALLREGION }, { coo[i].getpCX(), coo[i].getpCY(), fire[i].getWidth(), fire[i].getHeight() });
			for (int i = 0; i < MAXHP; i++) {
				window.setVP(i);
				h.draw({ h.getWidth() / 2, 0, h.getWidth() , h.getHeight() }, { 0, 0,h.getWidth() / 2, h.getHeight() });
			}
			for (int i = 0; i < pan.getHP(); i++) {
				window.setVP(i);
				h.draw();
			}
			window.setVP(MAXHP + 0);
			demo1.draw({ 0, 0, WINDOWW / 6 , WINDOWW / 6 }, { ALLREGION });
			filledCircleColor(window.getRenderer(), (pan.getX() + pan.getWidth() / 2) / 12, (pan.getY() + pan.getHeight() / 2) / 8, 2, 0xFF0000FF);

			window.setVP(-1);
			slot1.draw();
			back.draw();
			window.display();
			break;
		}
		/*
		case BACKPACK:
		{
			break;
		}
		*/
		}
	}
	pan.close();
	demo1.close();
	fail.close();
	resume.close();
	menu.close();

	for (int i = 0; i < Monsv.size(); i++)
		Monsv[i]->close();

	for (int i = 0; i < 6; i++)
		fire[i].close();
}

void GSManager::LoadGamePlay(RenderWindow& window)
{
	int state = 0;
	Coordinate coord, coo[6], enemycord[3], enemyhp[3], keycord, tempcord;



	Text fail("Game Over", "../fonts/akabara-cinderella.ttf", 60, TTF_STYLE_BOLD, { 0, 255, 255 }, BLENDED, { 100, 100, 100 }, window.getRenderer(), { WINDOWW / 2 - 150, WINDOWH / 2 }, { NULL, NULL }, NULL, SDL_FLIP_NONE, 100);
	Text resume("resume", "../fonts/akabara-cinderella.ttf", 60, TTF_STYLE_BOLD, { 0, 255, 255 }, BLENDED, { 100, 100, 100 }, window.getRenderer(), { WINDOWW / 2 - 100, WINDOWH / 2 - 30 }, { NULL, NULL }, NULL, SDL_FLIP_NONE, 100);
	Text menu("menu", "../fonts/akabara-cinderella.ttf", 60, TTF_STYLE_BOLD, { 0, 255, 255 }, BLENDED, { 100, 100, 100 }, window.getRenderer(), { WINDOWW / 2 - 70, WINDOWH / 2 + 15 }, { NULL, NULL }, NULL, SDL_FLIP_NONE, 100);
	Text save("save", "../fonts/akabara-cinderella.ttf", 60, TTF_STYLE_BOLD, { 0, 255, 255 }, BLENDED, { 100, 100, 100 }, window.getRenderer(), { WINDOWW / 2 - 70, WINDOWH / 2 - 80 }, { NULL, NULL }, NULL, SDL_FLIP_NONE, 100);
	Text slot1("Slot1", "../fonts/akabara-cinderella.ttf", 60, TTF_STYLE_BOLD, { 0, 255, 255 }, BLENDED, { 100, 100, 100 }, window.getRenderer(), { WINDOWW / 2 - 70, WINDOWH / 2 + 15 }, { NULL, NULL }, NULL, SDL_FLIP_NONE, 100);
	Text back("back", "../fonts/akabara-cinderella.ttf", 60, TTF_STYLE_BOLD, { 0, 255, 255 }, BLENDED, { 100, 100, 100 }, window.getRenderer(), { WINDOWW / 2 - 70, WINDOWH / 2 + 75 }, { NULL, NULL }, NULL, SDL_FLIP_NONE, 100);


	AnimeObject2 pan("../images/panda/", 4, window.getRenderer(), 0xFF, 0xFF, 0xFF);
	//MonsterI thekey("../images/Key", 1, window.getRenderer(), 0xFF, 0xFF, 0xFF);
	vector<Attack> fire; // (6, Attack("../images/attack/fire2.png", 1, 1, 1, window.getRenderer(), 0xFF, 0xFF, 0xFF));
	Object h("../images/heart.png", window.getRenderer(), 0xFF, 0xFF, 0xFF);
	Object prop("../images/frame.png", window.getRenderer(), 0xFF, 0xFF, 0xFF);
	Object key("../images/key.png", window.getRenderer(), 0xFF, 0xFF, 0xFF);
	vector<Object> prop_v;

	vector<MonsterA> tempa;
	vector<MonsterB> tempb;
	vector<MonsterC> tempc;
	vector<MonsterD> tempd;

	for (int i = 0; i < 3; i++)
	{
		MonsterA a("../images/MonsterA/", 4, window.getRenderer(), 0xFF, 0xFF, 0xFF);
		tempa.push_back(a);
	}
	for (int i = 0; i < 3; i++)
	{
		MonsterB b("../images/MonsterB/", 5, window.getRenderer(), 0xFF, 0xFF, 0xFF);
		tempb.push_back(b);
	}
	for (int i = 0; i < 2; i++)
	{
		MonsterC c("../images/MonsterC/", 6, window.getRenderer(), 0xFF, 0xFF, 0xFF);
		tempc.push_back(c);
	}
	for (int i = 0; i < 2; i++)
	{
		MonsterD d("../images/MonsterD/", 4, window.getRenderer(), 0xFF, 0xFF, 0xFF);
		tempd.push_back(d);
	}
	vector<Monster*> Monsv;
	for (int i = 0; i < tempa.size(); i++)
		Monsv.push_back(&tempa[i]);
	for (int i = 0; i < tempb.size(); i++)
		Monsv.push_back(&tempb[i]);
	for (int i = 0; i < tempc.size(); i++)
		Monsv.push_back(&tempc[i]);
	for (int i = 0; i < tempd.size(); i++)
		Monsv.push_back(&tempd[i]);

	for (int i = 0; i < Monsv.size(); i++)
		Monsv[i]->setPosition((i + 5) * WIDTH / MAPTILEX, 36 * HEIGHT / MAPTILEY);

	h.setShownFlag(true);
	h.setPosition(0, 0);
	for (int i = 0; i < MAXHP; i++)
	{
		window.addVPregion({ {h.getWidth() / 2 * i, 0, h.getWidth() / 2, h.getHeight()} });
	}
	prop.setShownFlag(true);
	prop.setPosition(0, 0);
	for (int i = 0; i < PROPNUM; i++)
	{
		window.addVPregion({ {prop.getWidth() * i, h.getHeight() * 4 / 3, prop.getWidth() , prop.getHeight()} });
	}
	key.setShownFlag(true);
	key.setPosition(0, 0);

	prop_v.push_back(key);


	Map demo1;
	demo1.set("../images/map/map", window.getRenderer());
	window.addVPregion({ {WINDOWW / 6 * 5, 0, WINDOWW / 4, WINDOWH / 4} }); // VP: 
	pan.setPosition(demo1.startL[demo1.getmapnum()].x, demo1.startL[demo1.getmapnum()].y);

	//thekey.setPosition(21 * WIDTH / MAPTILEX, 31 * HEIGHT / MAPTILEY);


	for (int i = 0; i < Monsv.size(); i++)
	{
		Monsv[i]->setMchptr(pan);
		Monsv[i]->startAI(15);
	}

	for (int i = 0; i < 6; i++)
	{
		if (i == 2 || i == 3)
			fire.push_back(Attack("../images/fire2.png", window.getRenderer(), 0x00, 0x00, 0x00));
		else
			fire.push_back(Attack("../images/fire1.png", window.getRenderer(), 0x00, 0x00, 0x00));
	}
	MainchSave mchsave;
	MapSave mapsave;
	FILE* fload;
	fopen_s(&fload, "../saves/slot1.dat", "rb");
	fread(&mchsave, sizeof(mchsave), 1, fload);
	fread(&mapsave, sizeof(mapsave), 1, fload);
	printf("mapnum: %d\n", mapsave.mapnum);
	demo1.setmapnum(mapsave.mapnum);
	pan.setMapnum(mchsave.mapnum);
	pan.setHP(mchsave.health);
	pan.setPosition(mchsave.x, mchsave.y);
	fclose(fload);
	demo1.setmap(Monsv);

	while (!quit && GameState == GAMEPLAY)
	{

		while (SDL_PollEvent(&ev) != 0)
		{
			if (ev.type == SDL_QUIT)
				quit = true;
			pauseEvents(ev, this, state, pan, fire);
			if (state == PLAY)
			{
				poohKeyboard(ev, pan);
				attackKeyboard(ev, fire, pan);
			}
		}

		switch (state)
		{
		case PLAY:
		{
			window.clear();
			window.setVP(-1);
			pan.move();

			//			for (int i = 0; i < 3; i++)
			//			{
			//				if (!monsv[i].getDeadFlag())
			//					monsv[i].AIstate(pan);
			//				//monsv[i].StartWait(30);
			//			}
			demo1.setcamera(pan);



			coord.calMapCamera(demo1, pan);
			for (int i = 0; i < fire.size(); i++)
				coo[i].calMapCamera(demo1, fire[i]);



			demo1.draw({ ALLREGION }, demo1.getcamera());
			pan.draw({ ALLREGION }, { coord.getpCX(), coord.getpCY(), pan.getWidth() / SHRINK, pan.getHeight() / SHRINK });



			for (int i = 0; i < Monsv.size(); i++)
			{
				if (!Monsv[i]->getDeadFlag())
				{
					enemycord[0].calMapCamera(demo1, *Monsv[i]);
					Monsv[i]->draw({ enemycord[0].getpCX(),enemycord[0].getpCY(),Monsv[i]->getWidth() / SHRINK,Monsv[i]->getHeight() / SHRINK }, { ALLREGION });
				}
			}

			//thekey.gotKey(pan);
		//if (demo1.getmapnum() == 3)
		//{
		//	keycord.calMapCamera(demo1, thekey);
		//	thekey.draw({ keycord.getpCX(),keycord.getpCY(),thekey.getWidth() / SHRINK,thekey.getHeight() / SHRINK }, { ALLREGION });
		//}




			for (int i = 0; i < Monsv.size(); i++)
			{
				if (!Monsv[i]->getDeadFlag())
					Monsv[i]->collisionAABB(pan);
			}



			for (int i = 0; i < fire.size(); i++)
			{
				fire[i].collision_mons(Monsv);
			}

			for (int i = 0; i < fire.size(); i++)
				fire[i].draw({ ALLREGION }, { coo[i].getpCX(), coo[i].getpCY(), fire[i].getWidth(), fire[i].getHeight() });


			window.setVP(-1);
			if (pan.getDeadFlag())
			{
				fail.draw();
				window.display();
				system("pause");

				break;
			}


			for (int i = 0; i < MAXHP; i++) {
				window.setVP(i);
				h.draw({ h.getWidth() / 2, 0, h.getWidth() , h.getHeight() }, { 0, 0,h.getWidth() / 2, h.getHeight() });
			}
			for (int i = 0; i < pan.getHP(); i++) {
				window.setVP(i);
				h.draw();
			}
			for (int i = 0; i < PROPNUM; i++)
			{
				window.setVP(MAXHP + i);
				if (i == 0)
					prop_v[i].draw();
				prop.draw();

			}

			window.setVP(MAXHP + PROPNUM);
			demo1.draw({ 0, 0, WINDOWW / 6 , WINDOWW / 6 }, { ALLREGION });
			filledCircleColor(window.getRenderer(), (pan.getX() + pan.getWidth() / 2) / 12, (pan.getY() + pan.getHeight() / 2) / 8, 2, 0xFF0000FF);
			window.display();
			break;
		}
		case PAUSE:
		{
			demo1.draw({ ALLREGION }, demo1.getcamera());
			pan.draw({ ALLREGION }, { coord.getpCX(), coord.getpCY(), pan.getWidth() / SHRINK, pan.getHeight() / SHRINK });
			for (int i = 0; i < Monsv.size(); i++)
			{
				if (!Monsv[i]->getDeadFlag())
				{
					enemycord[i].calMapCamera(demo1, *Monsv[i]);
					Monsv[i]->draw({ enemycord[i].getpCX(),enemycord[i].getpCY(),Monsv[i]->getWidth() / SHRINK,Monsv[i]->getHeight() / SHRINK }, { ALLREGION });
				}
			}
			for (int i = 0; i < fire.size(); i++)
				fire[i].draw({ ALLREGION }, { coo[i].getpCX(), coo[i].getpCY(), fire[i].getWidth(), fire[i].getHeight() });
			for (int i = 0; i < MAXHP; i++) {
				window.setVP(i);
				h.draw({ h.getWidth() / 2, 0, h.getWidth() , h.getHeight() }, { 0, 0,h.getWidth() / 2, h.getHeight() });
			}
			for (int i = 0; i < pan.getHP(); i++) {
				window.setVP(i);
				h.draw();
			}
			for (int i = 0; i < PROPNUM; i++)
			{
				window.setVP(MAXHP + i);
				prop.draw();
			}
			window.setVP(MAXHP + PROPNUM);
			demo1.draw({ 0, 0, WINDOWW / 6 , WINDOWW / 6 }, { ALLREGION });
			filledCircleColor(window.getRenderer(), (pan.getX() + pan.getWidth() / 2) / 12, (pan.getY() + pan.getHeight() / 2) / 8, 2, 0xFF0000FF);

			window.setVP(-1);
			resume.draw();
			menu.draw();
			save.draw();
			window.display();

			break;
		}
		case SAVE:
		{
			demo1.draw({ ALLREGION }, demo1.getcamera());
			pan.draw({ ALLREGION }, { coord.getpCX(), coord.getpCY(), pan.getWidth() / SHRINK, pan.getHeight() / SHRINK });
			for (int i = 0; i < Monsv.size(); i++)
			{
				if (!Monsv[i]->getDeadFlag())
				{
					enemycord[i].calMapCamera(demo1, *Monsv[i]);
					Monsv[i]->draw({ enemycord[i].getpCX(),enemycord[i].getpCY(),Monsv[i]->getWidth() / SHRINK,Monsv[i]->getHeight() / SHRINK }, { ALLREGION });
				}
			}
			for (int i = 0; i < fire.size(); i++)
				fire[i].draw({ ALLREGION }, { coo[i].getpCX(), coo[i].getpCY(), fire[i].getWidth(), fire[i].getHeight() });
			for (int i = 0; i < MAXHP; i++) {
				window.setVP(i);
				h.draw({ h.getWidth() / 2, 0, h.getWidth() , h.getHeight() }, { 0, 0,h.getWidth() / 2, h.getHeight() });
			}
			for (int i = 0; i < pan.getHP(); i++) {
				window.setVP(i);
				h.draw();
			}
			window.setVP(MAXHP + 0);
			demo1.draw({ 0, 0, WINDOWW / 6 , WINDOWW / 6 }, { ALLREGION });
			filledCircleColor(window.getRenderer(), (pan.getX() + pan.getWidth() / 2) / 12, (pan.getY() + pan.getHeight() / 2) / 8, 2, 0xFF0000FF);

			window.setVP(-1);
			slot1.draw();
			back.draw();
			window.display();
			break;
		}
		/*
		case BACKPACK:
		{
			break;
		}
		*/
		}
	}
	pan.close();
	demo1.close();
	fail.close();
	resume.close();
	menu.close();

	for (int i = 0; i < Monsv.size(); i++)
		Monsv[i]->close();

	for (int i = 0; i < 6; i++)
		fire[i].close();
}

void GSManager::setGameState(int gs)
{
	GameState = gs;
}

int GSManager::getGameState()
{
	return GameState;
}

