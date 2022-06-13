#include "GSManager.h"

//global functions
static void pauseEvents(SDL_Event e, GSManager* gsm, int& state, AnimeObject2& mch, vector<Attack>& atk, vector<Monster*>&mv)
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
					for (int i = 0; i < mv.size(); i++)
						mv[i]->setAImode(STOP);
					state = PAUSE;
				}
				else if (state == PAUSE)
				{
					for (int i = 0; i < atk.size(); i++)
						atk[i].setPause(false);
					for (int i = 0; i < mv.size(); i++)
						mv[i]->setAImode(WAIT);
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
			for (int i = 0; i < mv.size(); i++)
				mv[i]->setAImode(WAIT);
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
			mchsave.c = mch.getCoin();
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
				if (e.button.button == SDL_BUTTON_LEFT && x >= (WINDOWW / 2 - 150) && x <= (WINDOWW / 2 + 100) && y >= (WINDOWH / 2) && y <= (WINDOWH / 2 + 50))//new game
				{
					gsm->setGameState(GAMEPLAY);
				}
				else if (e.button.button == SDL_BUTTON_LEFT && x >= (WINDOWW / 2 - 70) && x <= (WINDOWW / 2 + 130) && y >= (WINDOWH / 2 + 55) && y <= (WINDOWH / 2 + 105))//load
				{
					state = LOAD;
				}
				break;
			}
			case LOAD:
			{
				if (e.button.button == SDL_BUTTON_LEFT && x >= (WINDOWW / 2 - 70) && x <= (WINDOWW / 2 + 130) && y >= (WINDOWH / 2 + 110) && y <= (WINDOWH / 2 + 150))//back
				{
					state = MENU;
				}
				if (e.button.button == SDL_BUTTON_LEFT && x >= (WINDOWW / 2 - 70) && x <= (WINDOWW / 2 + 130) && y >= (WINDOWH / 2) && y <= (WINDOWH / 2 + 40))//slot1
				{
					gsm->setGameState(LOADGAMEPLAY);
				}
				break;
			}
		}
	}
}

static void ClearEvents(SDL_Event e, GSManager* gsm)
{
	int x, y;
	if (e.type == SDL_MOUSEBUTTONUP)
	{
		SDL_GetMouseState(&x, &y);
		if (e.button.button == SDL_BUTTON_LEFT && x >= (WINDOWW / 2 - 50) && x <= (WINDOWW / 2 + 50) && y >= (WINDOWH / 2+30) && y <= (WINDOWH / 2 + 70))//back
		{
			gsm->setGameState(MAINMENU);
		}
	}
}

static void OverEvents(SDL_Event e, GSManager* gsm)
{
	int x, y;
	if (e.type == SDL_MOUSEBUTTONUP)
	{
		SDL_GetMouseState(&x, &y);
		if (e.button.button == SDL_BUTTON_LEFT && x >= (WINDOWW / 2 - 150) && x <= (WINDOWW / 2 + 150) && y >= (WINDOWH / 2 -40) && y <= (WINDOWH / 2 + 70))//back
		{
			printf("in\n");
			gsm->setGameState(MAINMENU);
		}
	}
}

//class GSManager

GSManager::GSManager()
{
	quit = false;
	GameState = MAINMENU;
}

void GSManager::InitMonsters(std::vector<Monster*>& mv)
{
	FILE* fspawn;
	char file[100];
	int xx, yy, Dflag;

	sprintf_s(file, 100, "%s%02d.txt", "../Mspawn/", mv[0]->getMapnum() + 1);
	fopen_s(&fspawn, file, "r");
	for (int i = 0; i < mv.size(); i++)
	{
		fscanf_s(fspawn, "%d %d %d", &Dflag, &xx, &yy);
		mv[i]->setDeadFlag(Dflag);
		mv[i]->setPosition(xx * WIDTH / MAPTILEX, yy * HEIGHT / MAPTILEY);
		mv[i]->setBase(xx, yy);

	}
	fclose(fspawn);

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
			case GAMECLEAR:
			{
				GameClear(window);
				break;
			}

		}
	}
}

void GSManager::MainMenu(RenderWindow& window)
{
	Map mainmenu("../images/mapdemo1.png", window.getRenderer());
	//Object mainmenu("../images/mapdemo1.png", window.getRenderer());
	Text NewGame("New Game", "../fonts/akabara-cinderella.ttf", 60, TTF_STYLE_BOLD, { 0, 255, 255 }, BLENDED, { 100, 100, 100 }, window.getRenderer(), { WINDOWW / 2 - 150, WINDOWH / 2-10 }, { NULL, NULL }, NULL, SDL_FLIP_NONE, 100);
	Text Load("Load", "../fonts/akabara-cinderella.ttf", 60, TTF_STYLE_BOLD, { 0, 255, 255 }, BLENDED, { 100, 100, 100 }, window.getRenderer(), { WINDOWW / 2 - 70, WINDOWH / 2 + 55 }, { NULL, NULL }, NULL, SDL_FLIP_NONE, 100);
	Text Back("Back", "../fonts/akabara-cinderella.ttf", 60, TTF_STYLE_BOLD, { 0, 255, 255 }, BLENDED, { 100, 100, 100 }, window.getRenderer(), { WINDOWW / 2 - 70, WINDOWH / 2 + 110 }, { NULL, NULL }, NULL, SDL_FLIP_NONE, 100);
	Text Slot1("Slot1", "../fonts/akabara-cinderella.ttf", 60, TTF_STYLE_BOLD, { 0, 255, 255 }, BLENDED, { 100, 100, 100 }, window.getRenderer(), { WINDOWW / 2 - 70, WINDOWH / 2 }, { NULL, NULL }, NULL, SDL_FLIP_NONE, 100);

	

	int state = MENU;


	while (!quit && GameState == MAINMENU)
	{
		while (SDL_PollEvent(&ev) != 0)
		{
			if (ev.type == SDL_QUIT)
				quit = true;
			MenuEvents(ev, this, state);
		}
		window.setVP(-1);
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
	int state = PLAY;
	Coordinate cord;



	Text fail("Game Over", "../fonts/akabara-cinderella.ttf", 60, TTF_STYLE_BOLD, { 0, 255, 255 }, BLENDED, { 100, 100, 100 }, window.getRenderer(), { WINDOWW / 2 - 150, WINDOWH / 2 }, { NULL, NULL }, NULL, SDL_FLIP_NONE, 100);
	Text resume("resume", "../fonts/akabara-cinderella.ttf", 60, TTF_STYLE_BOLD, { 0, 255, 255 }, BLENDED, { 100, 100, 100 }, window.getRenderer(), { WINDOWW / 2 - 100, WINDOWH / 2 - 30 }, { NULL, NULL }, NULL, SDL_FLIP_NONE, 100);
	Text menu("menu", "../fonts/akabara-cinderella.ttf", 60, TTF_STYLE_BOLD, { 0, 255, 255 }, BLENDED, { 100, 100, 100 }, window.getRenderer(), { WINDOWW / 2 - 70, WINDOWH / 2 + 15 }, { NULL, NULL }, NULL, SDL_FLIP_NONE, 100);
	Text save("save", "../fonts/akabara-cinderella.ttf", 60, TTF_STYLE_BOLD, { 0, 255, 255 }, BLENDED, { 100, 100, 100 }, window.getRenderer(), { WINDOWW / 2 - 70, WINDOWH / 2 - 80 }, { NULL, NULL }, NULL, SDL_FLIP_NONE, 100);
	Text slot1("Slot1", "../fonts/akabara-cinderella.ttf", 60, TTF_STYLE_BOLD, { 0, 255, 255 }, BLENDED, { 100, 100, 100 }, window.getRenderer(), { WINDOWW / 2 - 70, WINDOWH / 2 + 15 }, { NULL, NULL }, NULL, SDL_FLIP_NONE, 100);
	Text back("back", "../fonts/akabara-cinderella.ttf", 60, TTF_STYLE_BOLD, { 0, 255, 255 }, BLENDED, { 100, 100, 100 }, window.getRenderer(), { WINDOWW / 2 - 70, WINDOWH / 2 + 75 }, { NULL, NULL }, NULL, SDL_FLIP_NONE, 100);


	AnimeObject2 pan("../images/panda/", 4, window.getRenderer(), 0xFF, 0xFF, 0xFF);
	
	MonsterI thekey("../images/Key", 1, window.getRenderer(), 0xFF, 0xFF, 0xFF);
	MonsterI gate("../images/gate", 1, window.getRenderer(), 0xFF, 0xFF, 0xFF);
	MonsterI princess("../images/princess", 1, window.getRenderer(), 0xFF, 0xFF, 0xFF);
	
	NPC npcPotion("../images/npcP", 1, window.getRenderer(), 0xFF, 0xFF, 0xFF);
	
	
	
	vector<Attack> fire; // (6, Attack("../images/attack/fire2.png", 1, 1, 1, window.getRenderer(), 0xFF, 0xFF, 0xFF));
	vector<MAttack> mfire(3, MAttack("../images/fire", 1, window.getRenderer(), 0x00, 0x00, 0x00));


	Object h("../images/heart.png", window.getRenderer(), 0xFF, 0xFF, 0xFF);
	Object frame("../images/frame.png", window.getRenderer(), 0xFF, 0xFF, 0xFF);
	Object key("../images/key.png", window.getRenderer(), 0xFF, 0xFF, 0xFF);
	
	Object potion("../images/potion.png", window.getRenderer(), 32, 29, 32);
	Object coin("../images/coin.png", window.getRenderer(), 32, 29, 32);
	Object flash("../images/flash.png", window.getRenderer());
	vector<Object> prop_v;
	vector<Object> number;
	vector<Object> numberc;

	vector<MonsterA> tempa;
	vector<MonsterB> tempb;
	vector<MonsterC> tempc;
	vector<MonsterD> tempd;
	vector<Monster*> Monsv;
	for (int i = 0; i < 3; i++)
	{
		MonsterA a("../images/MonsterA/", 5, window.getRenderer(), 0xFF, 0xFF, 0xFF);
		tempa.push_back(a);
	}
	for (int i = 0; i < 3; i++)
	{
		MonsterB b("../images/MonsterB/", 4, window.getRenderer(), 0xFF, 0xFF, 0xFF);
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
	
	printf("1\n");
	for (int i = 0; i < tempa.size(); i++)
		Monsv.push_back(&tempa[i]);
	for (int i = 0; i < tempb.size(); i++)
		Monsv.push_back(&tempb[i]);
	for (int i = 0; i < tempc.size(); i++)
		Monsv.push_back(&tempc[i]);
	for (int i = 0; i < tempd.size(); i++)
		Monsv.push_back(&tempd[i]);

	InitMonsters(Monsv);
	printf("2\n");

	npcPotion.setPosition(5 * WIDTH / MAPTILEX, 36 * HEIGHT / MAPTILEY);
	gate.setPosition(45 * WIDTH / MAPTILEX, 6 * HEIGHT / MAPTILEY);
	princess.setPosition(51 * WIDTH / MAPTILEX, 24 * HEIGHT / MAPTILEY + 5);

	h.setShownFlag(true);
	h.setPosition(0, 0);
	for (int i = 0; i < MAXHP; i++)
	{
		window.addVPregion({ {h.getWidth() / 2 * i, 0, h.getWidth() / 2, h.getHeight()} });//0~7
	}
	frame.setShownFlag(true);
	frame.setPosition(0, 0);
	for (int i = 0; i < PROPNUM; i++)
	{
		window.addVPregion({ {(frame.getWidth()+1) * i, h.getHeight() * 4 / 3, frame.getWidth(), frame.getHeight()} });//8~13
	}
	key.setShownFlag(true);
	key.setPosition(0, 0);
	potion.setShownFlag(true);
	potion.setPosition(0, 0);

	

	prop_v.push_back(key);
	prop_v.push_back(potion);
	
	for (int i = 0; i < 10; i++)
	{
		char file[100];
		sprintf_s(file, "../images/number/%d.png", i);
		number.push_back(Object(file, window.getRenderer(), 32, 29, 32));
		number[i].setShownFlag(true);
		number[i].setPosition(0, 0);
	}

	for (int i = 0; i < 10; i++)
	{
		char file[100];
		sprintf_s(file, "../images/number/0%d.png", i);
		numberc.push_back(Object(file, window.getRenderer(), 32, 29, 32));
		numberc[i].setShownFlag(true);
		numberc[i].setPosition(0, 0);
	}
	

	Map demo1;
	demo1.set("../images/map/map", window.getRenderer());
	window.addVPregion({ {WINDOWW / 6 * 5, 0, WINDOWW / 4, WINDOWH / 4} }); // 14
	pan.setPosition(demo1.startL[demo1.getmapnum()].x, demo1.startL[demo1.getmapnum()].y);

	thekey.setPosition(21 * WIDTH / MAPTILEX, 31 * HEIGHT / MAPTILEY);

	window.addVPregion({ {0, h.getHeight() * 12 / 3, coin.getWidth()/8, coin.getHeight()/8} });//15
	coin.setShownFlag(true);
	coin.setPosition(0, 0);

	window.addVPregion({ {WINDOWW - flash.getWidth(), 0, flash.getWidth(), flash.getHeight()} });
	flash.setShownFlag(true);
	flash.setPosition(0, 0);

	for(int i=1; i<=3; i++)
		window.addVPregion({ {i*coin.getWidth() / 8, h.getHeight() * 12 / 3, coin.getWidth() / 8, coin.getHeight() / 8} });//16~18

	for (int i = 0; i < Monsv.size(); i++)
	{
		Monsv[i]->setMchptr(pan);
		Monsv[i]->setMatkptr(mfire[i % 3]);
		Monsv[i]->startAI(15);
	}
	printf("3\n");
	for (int i = 0; i < ATTACKNUM; i++)
	{
		if (i > 3)
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

			if(state==PLAY || state==PAUSE)
				pauseEvents(ev, this, state, pan, fire, Monsv);

			if (state == OVER)
				OverEvents(ev, this);
			if (state == PLAY)
			{
				poohKeyboard(ev, pan);
				attackKeyboard(ev, fire, pan);
				npcKeyBoard(ev, pan, npcPotion);
			}
		}

		switch (state)
		{
		case PLAY:
		{
			window.clear();
			window.setVP(-1);
			pan.move();

			demo1.setcamera(pan);
			demo1.changemap(pan, Monsv);


			cord.calMapCamera(demo1, pan);
				



			demo1.draw({ ALLREGION }, demo1.getcamera());
			pan.draw({ ALLREGION }, { cord.getpCX(), cord.getpCY(), pan.getWidth() / SHRINK, pan.getHeight() / SHRINK });



			for (int i = 0; i < Monsv.size(); i++)
			{
				if (!Monsv[i]->getDeadFlag())
				{
					cord.calMapCamera(demo1, *Monsv[i]);
					Monsv[i]->draw({ cord.getpCX(),cord.getpCY(),Monsv[i]->getWidth() / SHRINK,Monsv[i]->getHeight() / SHRINK }, { ALLREGION });
				}
			}

			thekey.gotKey(pan);
			if (demo1.getmapnum() == 3)
			{
				cord.calMapCamera(demo1, thekey);
				thekey.draw({ cord.getpCX(),cord.getpCY(),thekey.getWidth() / SHRINK,thekey.getHeight() / SHRINK }, { ALLREGION });
			}
			if (demo1.getmapnum() == 4)
			{
				cord.calMapCamera(demo1, gate);
				gate.draw({ cord.getpCX(), cord.getpCY(), gate.getWidth() / SHRINK, gate.getHeight() / SHRINK }, { ALLREGION });
				gate.gateAABB(pan);
			}
			

			for (int i = 0; i < Monsv.size(); i++)
			{
				if (!Monsv[i]->getDeadFlag())
					Monsv[i]->collisionAABB(pan);
			}


			if (demo1.getmapnum() == 6)
			{
				cord.calMapCamera(demo1, princess);
				princess.draw({ cord.getpCX(),cord.getpCY(),princess.getWidth() / SHRINK,princess.getHeight() / SHRINK }, { ALLREGION });
				princess.princessAABB(pan);
			}

			if (demo1.getmapnum() == 0)
			{
				cord.calMapCamera(demo1, npcPotion);
				npcPotion.draw({ cord.getpCX(),cord.getpCY(),npcPotion.getWidth() / SHRINK,npcPotion.getHeight() / SHRINK }, { ALLREGION });
				npcPotion.npcAABB(pan);
			}

			if (princess.getWinFlag())
				GameState = GAMECLEAR;

		
			for (int i = 0; i < fire.size(); i++)
			{
				fire[i].setCharacterCenter(pan.getX() + pan.getWidth() / 3, pan.getY() + pan.getHeight() / 4);
				fire[i].setMapnum(pan.getMapnum());
				fire[i].collision_mons(Monsv, pan);
			}

			for (int i = 0; i < fire.size(); i++)
			{
				cord.calMapCamera(demo1, fire[i]);
				fire[i].draw({ ALLREGION }, { cord.getpCX(), cord.getpCY(), fire[i].getWidth(), fire[i].getHeight() });
			}

			for (int i = 0; i < mfire.size(); i++)
			{
				cord.calMapCamera(demo1, mfire[i]);
				mfire[i].collisionAABB(pan);
				mfire[i].draw({ cord.getpCX(), cord.getpCY(), mfire[i].getWidth(), mfire[i].getHeight()}, {ALLREGION});
			}

			window.setVP(-1);
			if (pan.getDeadFlag())
			{
				for (int i = 0; i < Monsv.size(); i++)
					Monsv[i]->setAImode(STOP);
				state = OVER;
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
				if (pan.getKey() == true && i == 0) //key
				{
					prop_v[0].draw();
				}
				if (i == 1) //potion
				{
					prop_v[1].draw();
					number[pan.getPotionNum()].draw();
				}
				frame.draw();

			}

			
			drawCoinNum(numberc, window, pan.getCoin(), coin);

			window.setVP(MAXHP + PROPNUM);
			demo1.draw({ 0, 0, WINDOWW / 6 , WINDOWW / 6 }, { ALLREGION });
			filledCircleColor(window.getRenderer(), (pan.getX() + pan.getWidth() / 2) / 12, (pan.getY() + pan.getHeight() / 2) / 8, 2, 0xFF0000FF);
			window.setVP(MAXHP + PROPNUM + 1);
			coin.draw({ ALLREGION } , { 0, 0, coin.getWidth() / 8 , coin.getHeight() / 8});
			window.setVP(MAXHP + PROPNUM + 2);
			flash.draw();
			boxRGBA(window.getRenderer(), 0, 0, flash.getWidth(), 0 + (flash.getHeight() - flash.getHeight() * pan.getRushCD() / (RUSHCD / RUSHTIMER)), 0x9E, 0x9E, 0x9E, 0x99);

			window.display();
			break;
		}
		case PAUSE:
		{

			demo1.draw({ ALLREGION }, demo1.getcamera());
			cord.calMapCamera(demo1, pan);
			pan.draw({ ALLREGION }, { cord.getpCX(), cord.getpCY(), pan.getWidth() / SHRINK, pan.getHeight() / SHRINK });
			for (int i = 0; i < Monsv.size(); i++)
			{
				if (!Monsv[i]->getDeadFlag())
				{
					cord.calMapCamera(demo1, *Monsv[i]);
					Monsv[i]->draw({ cord.getpCX(),cord.getpCY(),Monsv[i]->getWidth() / SHRINK,Monsv[i]->getHeight() / SHRINK }, { ALLREGION });
				}
			}

			thekey.gotKey(pan);
			if (demo1.getmapnum() == 3)
			{
				cord.calMapCamera(demo1, thekey);
				thekey.draw({ cord.getpCX(),cord.getpCY(),thekey.getWidth() / SHRINK,thekey.getHeight() / SHRINK }, { ALLREGION });
			}
			if (demo1.getmapnum() == 4)
			{
				cord.calMapCamera(demo1, gate);
				gate.draw({ cord.getpCX(), cord.getpCY(), gate.getWidth() / SHRINK, gate.getHeight() / SHRINK }, { ALLREGION });
				gate.collisionAABB(pan);
			}
			if (demo1.getmapnum() == 0)
			{
				cord.calMapCamera(demo1, npcPotion);
				npcPotion.draw({ cord.getpCX(),cord.getpCY(),npcPotion.getWidth() / SHRINK,npcPotion.getHeight() / SHRINK }, { ALLREGION });
				npcPotion.npcAABB(pan);
			}
			for (int i = 0; i < PROPNUM; i++)
			{
				window.setVP(MAXHP + i);
				if (pan.getKey() == true && i == 0) //key
				{
					prop_v[0].draw();
				}
				if (i == 1) //potion
				{
					prop_v[1].draw();
					number[pan.getPotionNum()].draw();
				}
				frame.draw();

			}
			window.setVP(-1);
			for (int i = 0; i < fire.size(); i++)
			{
				cord.calMapCamera(demo1, fire[i]);
				fire[i].draw({ ALLREGION }, { cord.getpCX(), cord.getpCY(), fire[i].getWidth(), fire[i].getHeight() });
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
				if (pan.getKey() == true && i == 0) //key
				{
					prop_v[0].draw();
				}
				if (i == 1) //potion
				{
					prop_v[1].draw();
					number[pan.getPotionNum()].draw();
				}
				frame.draw();

			}
			drawCoinNum(numberc, window, pan.getCoin(), coin);
			window.setVP(MAXHP + PROPNUM);
			demo1.draw({ 0, 0, WINDOWW / 6 , WINDOWW / 6 }, { ALLREGION });
			filledCircleColor(window.getRenderer(), (pan.getX() + pan.getWidth() / 2) / 12, (pan.getY() + pan.getHeight() / 2) / 8, 2, 0xFF0000FF);
			window.setVP(MAXHP + PROPNUM + 1);
			coin.draw({ ALLREGION }, { 0, 0, coin.getWidth() / 8 , coin.getHeight() / 8 });
			window.setVP(MAXHP + PROPNUM + 2);
			flash.draw();
			boxRGBA(window.getRenderer(), 0, 0, flash.getWidth(), 0 + (flash.getHeight() - flash.getHeight() * pan.getRushCD() / (RUSHCD / RUSHTIMER)), 0x9E, 0x9E, 0x9E, 0x99);

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
			cord.calMapCamera(demo1, pan);
			pan.draw({ ALLREGION }, { cord.getpCX(), cord.getpCY(), pan.getWidth() / SHRINK, pan.getHeight() / SHRINK });
			for (int i = 0; i < Monsv.size(); i++)
			{
				if (!Monsv[i]->getDeadFlag())
				{
					cord.calMapCamera(demo1, *Monsv[i]);
					Monsv[i]->draw({ cord.getpCX(),cord.getpCY(),Monsv[i]->getWidth() / SHRINK,Monsv[i]->getHeight() / SHRINK }, { ALLREGION });
				}
			}
			for (int i = 0; i < fire.size(); i++)
			{
				cord.calMapCamera(demo1, fire[i]);
				fire[i].draw({ ALLREGION }, { cord.getpCX(), cord.getpCY(), fire[i].getWidth(), fire[i].getHeight() });
			}	
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
			window.setVP(MAXHP + PROPNUM + 1);
			coin.draw({ ALLREGION }, { 0, 0, coin.getWidth() / 8 , coin.getHeight() / 8 });
			window.setVP(MAXHP + PROPNUM + 2);
			flash.draw();
			boxRGBA(window.getRenderer(), 0, 0, flash.getWidth(), 0 + (flash.getHeight() - flash.getHeight() * pan.getRushCD() / (RUSHCD / RUSHTIMER)), 0x9E, 0x9E, 0x9E, 0x99);

			window.setVP(-1);
			slot1.draw();
			back.draw();
			window.display();
			break;
		}
		case OVER:
		{

			demo1.draw({ ALLREGION }, demo1.getcamera());
			cord.calMapCamera(demo1, pan);
			pan.draw({ ALLREGION }, { cord.getpCX(), cord.getpCY(), pan.getWidth() / SHRINK, pan.getHeight() / SHRINK });
			
			for (int i = 0; i < Monsv.size(); i++)
			{
				if (!Monsv[i]->getDeadFlag())
				{
					cord.calMapCamera(demo1, *Monsv[i]);
					Monsv[i]->draw({ cord.getpCX(),cord.getpCY(),Monsv[i]->getWidth() / SHRINK,Monsv[i]->getHeight() / SHRINK }, { ALLREGION });
				}
			}

			thekey.gotKey(pan);
			if (demo1.getmapnum() == 3)
			{
				cord.calMapCamera(demo1, thekey);
				thekey.draw({ cord.getpCX(),cord.getpCY(),thekey.getWidth() / SHRINK,thekey.getHeight() / SHRINK }, { ALLREGION });
			}
			if (demo1.getmapnum() == 4)
			{
				cord.calMapCamera(demo1, gate);
				gate.draw({ cord.getpCX(), cord.getpCY(), gate.getWidth() / SHRINK, gate.getHeight() / SHRINK }, { ALLREGION });
				gate.collisionAABB(pan);
			}
			for (int i = 0; i < PROPNUM; i++)
			{
				window.setVP(MAXHP + i);
				if (pan.getKey() == true && i == 0) //key
				{
					prop_v[0].draw();
				}
				if (i == 1) //potion
				{
					prop_v[1].draw();
					number[pan.getPotionNum()].draw();
				}
				frame.draw();

			}
			window.setVP(-1);
			for (int i = 0; i < fire.size(); i++)
			{
				cord.calMapCamera(demo1, fire[i]);
				fire[i].draw({ ALLREGION }, { cord.getpCX(), cord.getpCY(), fire[i].getWidth(), fire[i].getHeight() });
			}

			for (int i = 0; i < MAXHP; i++) 
			{
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
				if (pan.getKey() == true && i == 0) //key
				{
					prop_v[0].draw();
				}
				if (i == 1) //potion
				{
					prop_v[1].draw();
					number[pan.getPotionNum()].draw();
				}
				frame.draw();

			}
			drawCoinNum(numberc, window, pan.getCoin(), coin);
			window.setVP(MAXHP + PROPNUM);
			demo1.draw({ 0, 0, WINDOWW / 6 , WINDOWW / 6 }, { ALLREGION });
			filledCircleColor(window.getRenderer(), (pan.getX() + pan.getWidth() / 2) / 12, (pan.getY() + pan.getHeight() / 2) / 8, 2, 0xFF0000FF);
			window.setVP(MAXHP + PROPNUM + 1);
			coin.draw({ ALLREGION }, { 0, 0, coin.getWidth() / 8 , coin.getHeight() / 8 });
			window.setVP(MAXHP + PROPNUM + 2);
			flash.draw();
			boxRGBA(window.getRenderer(), 0, 0, flash.getWidth(), 0 + (flash.getHeight() - flash.getHeight() * pan.getRushCD() / (RUSHCD / RUSHTIMER)), 0x9E, 0x9E, 0x9E, 0x99);

			window.setVP(-1);
			fail.draw();
			window.display();
			break;
		}
		}
	}
	pan.close();
	demo1.close();
	fail.close();
	resume.close();
	menu.close();

	save.close();
	slot1.close();
	back.close();

	for (int i = 0; i < Monsv.size(); i++)
	{
		Monsv[i]->close();
		SDL_RemoveTimer(Monsv[i]->AIID);
	}
		
	Monsv.clear();

	for (int i = 0; i < tempa.size(); i++)
		tempa[i].close();
	tempa.clear();
	for (int i = 0; i < tempb.size(); i++)
		tempb[i].close();
	tempb.clear();
	for (int i = 0; i < tempc.size(); i++)
		tempc[i].close();
	tempc.clear();
	for (int i = 0; i < tempd.size(); i++)
		tempd[i].close();
	tempd.clear();

	for (int i = 0; i < mfire.size(); i++)
		mfire[i].close();

	for (int i = 0; i < ATTACKNUM; i++)
		fire[i].close();

	gate.close();
	thekey.close();
	for (int i = 0; i < prop_v.size(); i++)
		prop_v[i].close();

	princess.close();
	npcPotion.close();
	h.close();
	potion.close();
	frame.close();
	flash.close();

	for (int i = 0; i < number.size(); i++)
		number[i].close();
	for (int i = 0; i < numberc.size(); i++)
		numberc[i].close();
}

void GSManager::LoadGamePlay(RenderWindow& window)
{
	int state = PLAY;
	Coordinate cord;



	Text fail("Game Over", "../fonts/akabara-cinderella.ttf", 60, TTF_STYLE_BOLD, { 0, 255, 255 }, BLENDED, { 100, 100, 100 }, window.getRenderer(), { WINDOWW / 2 - 150, WINDOWH / 2 }, { NULL, NULL }, NULL, SDL_FLIP_NONE, 100);
	Text resume("resume", "../fonts/akabara-cinderella.ttf", 60, TTF_STYLE_BOLD, { 0, 255, 255 }, BLENDED, { 100, 100, 100 }, window.getRenderer(), { WINDOWW / 2 - 100, WINDOWH / 2 - 30 }, { NULL, NULL }, NULL, SDL_FLIP_NONE, 100);
	Text menu("menu", "../fonts/akabara-cinderella.ttf", 60, TTF_STYLE_BOLD, { 0, 255, 255 }, BLENDED, { 100, 100, 100 }, window.getRenderer(), { WINDOWW / 2 - 70, WINDOWH / 2 + 15 }, { NULL, NULL }, NULL, SDL_FLIP_NONE, 100);
	Text save("save", "../fonts/akabara-cinderella.ttf", 60, TTF_STYLE_BOLD, { 0, 255, 255 }, BLENDED, { 100, 100, 100 }, window.getRenderer(), { WINDOWW / 2 - 70, WINDOWH / 2 - 80 }, { NULL, NULL }, NULL, SDL_FLIP_NONE, 100);
	Text slot1("Slot1", "../fonts/akabara-cinderella.ttf", 60, TTF_STYLE_BOLD, { 0, 255, 255 }, BLENDED, { 100, 100, 100 }, window.getRenderer(), { WINDOWW / 2 - 70, WINDOWH / 2 + 15 }, { NULL, NULL }, NULL, SDL_FLIP_NONE, 100);
	Text back("back", "../fonts/akabara-cinderella.ttf", 60, TTF_STYLE_BOLD, { 0, 255, 255 }, BLENDED, { 100, 100, 100 }, window.getRenderer(), { WINDOWW / 2 - 70, WINDOWH / 2 + 75 }, { NULL, NULL }, NULL, SDL_FLIP_NONE, 100);


	AnimeObject2 pan("../images/panda/", 4, window.getRenderer(), 0xFF, 0xFF, 0xFF);

	MonsterI thekey("../images/Key", 1, window.getRenderer(), 0xFF, 0xFF, 0xFF);
	MonsterI gate("../images/gate", 1, window.getRenderer(), 0xFF, 0xFF, 0xFF);
	MonsterI princess("../images/princess", 1, window.getRenderer(), 0xFF, 0xFF, 0xFF);

	NPC npcPotion("../images/npcP", 1, window.getRenderer(), 0xFF, 0xFF, 0xFF);



	vector<Attack> fire; // (6, Attack("../images/attack/fire2.png", 1, 1, 1, window.getRenderer(), 0xFF, 0xFF, 0xFF));
	vector<MAttack> mfire(3, MAttack("../images/fire", 1, window.getRenderer(), 0x00, 0x00, 0x00));


	Object h("../images/heart.png", window.getRenderer(), 0xFF, 0xFF, 0xFF);
	Object frame("../images/frame.png", window.getRenderer(), 0xFF, 0xFF, 0xFF);
	Object key("../images/key.png", window.getRenderer(), 0xFF, 0xFF, 0xFF);

	Object potion("../images/potion.png", window.getRenderer(), 32, 29, 32);
	Object coin("../images/coin.png", window.getRenderer(), 32, 29, 32);
	Object flash("../images/flash.png", window.getRenderer());
	vector<Object> prop_v;
	vector<Object> number;
	vector<Object> numberc;

	vector<MonsterA> tempa;
	vector<MonsterB> tempb;
	vector<MonsterC> tempc;
	vector<MonsterD> tempd;
	vector<Monster*> Monsv;
	for (int i = 0; i < 3; i++)
	{
		MonsterA a("../images/MonsterA/", 5, window.getRenderer(), 0xFF, 0xFF, 0xFF);
		tempa.push_back(a);
	}
	for (int i = 0; i < 3; i++)
	{
		MonsterB b("../images/MonsterB/", 4, window.getRenderer(), 0xFF, 0xFF, 0xFF);
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

	printf("1\n");
	for (int i = 0; i < tempa.size(); i++)
		Monsv.push_back(&tempa[i]);
	for (int i = 0; i < tempb.size(); i++)
		Monsv.push_back(&tempb[i]);
	for (int i = 0; i < tempc.size(); i++)
		Monsv.push_back(&tempc[i]);
	for (int i = 0; i < tempd.size(); i++)
		Monsv.push_back(&tempd[i]);

	InitMonsters(Monsv);
	printf("2\n");

	npcPotion.setPosition(5 * WIDTH / MAPTILEX, 36 * HEIGHT / MAPTILEY);
	gate.setPosition(45 * WIDTH / MAPTILEX, 6 * HEIGHT / MAPTILEY);
	princess.setPosition(51 * WIDTH / MAPTILEX, 24 * HEIGHT / MAPTILEY + 5);

	h.setShownFlag(true);
	h.setPosition(0, 0);
	for (int i = 0; i < MAXHP; i++)
	{
		window.addVPregion({ {h.getWidth() / 2 * i, 0, h.getWidth() / 2, h.getHeight()} });//0~7
	}
	frame.setShownFlag(true);
	frame.setPosition(0, 0);
	for (int i = 0; i < PROPNUM; i++)
	{
		window.addVPregion({ {(frame.getWidth() + 1) * i, h.getHeight() * 4 / 3, frame.getWidth(), frame.getHeight()} });//8~13
	}
	key.setShownFlag(true);
	key.setPosition(0, 0);
	potion.setShownFlag(true);
	potion.setPosition(0, 0);



	prop_v.push_back(key);
	prop_v.push_back(potion);

	for (int i = 0; i < 10; i++)
	{
		char file[100];
		sprintf_s(file, "../images/number/%d.png", i);
		number.push_back(Object(file, window.getRenderer(), 32, 29, 32));
		number[i].setShownFlag(true);
		number[i].setPosition(0, 0);
	}

	for (int i = 0; i < 10; i++)
	{
		char file[100];
		sprintf_s(file, "../images/number/0%d.png", i);
		numberc.push_back(Object(file, window.getRenderer(), 32, 29, 32));
		numberc[i].setShownFlag(true);
		numberc[i].setPosition(0, 0);
	}


	Map demo1;
	demo1.set("../images/map/map", window.getRenderer());
	window.addVPregion({ {WINDOWW / 6 * 5, 0, WINDOWW / 4, WINDOWH / 4} }); // 14
	pan.setPosition(demo1.startL[demo1.getmapnum()].x, demo1.startL[demo1.getmapnum()].y);

	thekey.setPosition(21 * WIDTH / MAPTILEX, 31 * HEIGHT / MAPTILEY);

	window.addVPregion({ {0, h.getHeight() * 12 / 3, coin.getWidth() / 8, coin.getHeight() / 8} });//15
	coin.setShownFlag(true);
	coin.setPosition(0, 0);

	window.addVPregion({ {WINDOWW - flash.getWidth(), 0, flash.getWidth(), flash.getHeight()} });
	flash.setShownFlag(true);
	flash.setPosition(0, 0);

	for (int i = 1; i <= 3; i++)
		window.addVPregion({ {i * coin.getWidth() / 8, h.getHeight() * 12 / 3, coin.getWidth() / 8, coin.getHeight() / 8} });//16~18

	for (int i = 0; i < Monsv.size(); i++)
	{
		Monsv[i]->setMchptr(pan);
		Monsv[i]->setMatkptr(mfire[i % 3]);
		Monsv[i]->startAI(15);
	}
	printf("3\n");
	for (int i = 0; i < ATTACKNUM; i++)
	{
		if (i > 3)
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
	demo1.setmapnum(mapsave.mapnum);
	pan.setMapnum(mchsave.mapnum);
	pan.setHP(mchsave.health);
	pan.setPosition(mchsave.x, mchsave.y);
	pan.setCoin(mchsave.c);
	fclose(fload);
	demo1.setmap(Monsv);


	while (!quit && GameState == LOADGAMEPLAY)
	{

		while (SDL_PollEvent(&ev) != 0)
		{
			if (ev.type == SDL_QUIT)
				quit = true;

			if (state == PLAY || state == PAUSE)
				pauseEvents(ev, this, state, pan, fire, Monsv);

			if (state == OVER)
				OverEvents(ev, this);
			if (state == PLAY)
			{
				poohKeyboard(ev, pan);
				attackKeyboard(ev, fire, pan);
				npcKeyBoard(ev, pan, npcPotion);
			}
		}

		switch (state)
		{
		case PLAY:
		{
			window.clear();
			window.setVP(-1);
			pan.move();

			demo1.setcamera(pan);
			demo1.changemap(pan, Monsv);


			cord.calMapCamera(demo1, pan);




			demo1.draw({ ALLREGION }, demo1.getcamera());
			pan.draw({ ALLREGION }, { cord.getpCX(), cord.getpCY(), pan.getWidth() / SHRINK, pan.getHeight() / SHRINK });



			for (int i = 0; i < Monsv.size(); i++)
			{
				if (!Monsv[i]->getDeadFlag())
				{
					cord.calMapCamera(demo1, *Monsv[i]);
					Monsv[i]->draw({ cord.getpCX(),cord.getpCY(),Monsv[i]->getWidth() / SHRINK,Monsv[i]->getHeight() / SHRINK }, { ALLREGION });
				}
			}

			thekey.gotKey(pan);
			if (demo1.getmapnum() == 3)
			{
				cord.calMapCamera(demo1, thekey);
				thekey.draw({ cord.getpCX(),cord.getpCY(),thekey.getWidth() / SHRINK,thekey.getHeight() / SHRINK }, { ALLREGION });
			}
			if (demo1.getmapnum() == 4)
			{
				cord.calMapCamera(demo1, gate);
				gate.draw({ cord.getpCX(), cord.getpCY(), gate.getWidth() / SHRINK, gate.getHeight() / SHRINK }, { ALLREGION });
				gate.gateAABB(pan);
			}


			for (int i = 0; i < Monsv.size(); i++)
			{
				if (!Monsv[i]->getDeadFlag())
					Monsv[i]->collisionAABB(pan);
			}


			if (demo1.getmapnum() == 6)
			{
				cord.calMapCamera(demo1, princess);
				princess.draw({ cord.getpCX(),cord.getpCY(),princess.getWidth() / SHRINK,princess.getHeight() / SHRINK }, { ALLREGION });
				princess.princessAABB(pan);
			}

			if (demo1.getmapnum() == 0)
			{
				cord.calMapCamera(demo1, npcPotion);
				npcPotion.draw({ cord.getpCX(),cord.getpCY(),npcPotion.getWidth() / SHRINK,npcPotion.getHeight() / SHRINK }, { ALLREGION });
				npcPotion.npcAABB(pan);
			}

			if (princess.getWinFlag())
				GameState = GAMECLEAR;


			for (int i = 0; i < fire.size(); i++)
			{
				fire[i].setCharacterCenter(pan.getX() + pan.getWidth() / 3, pan.getY() + pan.getHeight() / 4);
				fire[i].setMapnum(pan.getMapnum());
				fire[i].collision_mons(Monsv, pan);
			}

			for (int i = 0; i < fire.size(); i++)
			{
				cord.calMapCamera(demo1, fire[i]);
				fire[i].draw({ ALLREGION }, { cord.getpCX(), cord.getpCY(), fire[i].getWidth(), fire[i].getHeight() });
			}

			for (int i = 0; i < mfire.size(); i++)
			{
				cord.calMapCamera(demo1, mfire[i]);
				mfire[i].collisionAABB(pan);
				mfire[i].draw({ cord.getpCX(), cord.getpCY(), mfire[i].getWidth(), mfire[i].getHeight() }, { ALLREGION });
			}

			window.setVP(-1);
			if (pan.getDeadFlag())
			{
				for (int i = 0; i < Monsv.size(); i++)
					Monsv[i]->setAImode(STOP);
				state = OVER;
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
				if (pan.getKey() == true && i == 0) //key
				{
					prop_v[0].draw();
				}
				if (i == 1) //potion
				{
					prop_v[1].draw();
					number[pan.getPotionNum()].draw();
				}
				frame.draw();

			}


			drawCoinNum(numberc, window, pan.getCoin(), coin);

			window.setVP(MAXHP + PROPNUM);
			demo1.draw({ 0, 0, WINDOWW / 6 , WINDOWW / 6 }, { ALLREGION });
			filledCircleColor(window.getRenderer(), (pan.getX() + pan.getWidth() / 2) / 12, (pan.getY() + pan.getHeight() / 2) / 8, 2, 0xFF0000FF);
			window.setVP(MAXHP + PROPNUM + 1);
			coin.draw({ ALLREGION }, { 0, 0, coin.getWidth() / 8 , coin.getHeight() / 8 });
			window.setVP(MAXHP + PROPNUM + 2);
			flash.draw();
			boxRGBA(window.getRenderer(), 0, 0, flash.getWidth(), 0 + (flash.getHeight() - flash.getHeight() * pan.getRushCD() / (RUSHCD / RUSHTIMER)), 0x9E, 0x9E, 0x9E, 0x99);

			window.display();
			break;
		}
		case PAUSE:
		{

			demo1.draw({ ALLREGION }, demo1.getcamera());
			cord.calMapCamera(demo1, pan);
			pan.draw({ ALLREGION }, { cord.getpCX(), cord.getpCY(), pan.getWidth() / SHRINK, pan.getHeight() / SHRINK });
			for (int i = 0; i < Monsv.size(); i++)
			{
				if (!Monsv[i]->getDeadFlag())
				{
					cord.calMapCamera(demo1, *Monsv[i]);
					Monsv[i]->draw({ cord.getpCX(),cord.getpCY(),Monsv[i]->getWidth() / SHRINK,Monsv[i]->getHeight() / SHRINK }, { ALLREGION });
				}
			}

			thekey.gotKey(pan);
			if (demo1.getmapnum() == 3)
			{
				cord.calMapCamera(demo1, thekey);
				thekey.draw({ cord.getpCX(),cord.getpCY(),thekey.getWidth() / SHRINK,thekey.getHeight() / SHRINK }, { ALLREGION });
			}
			if (demo1.getmapnum() == 4)
			{
				cord.calMapCamera(demo1, gate);
				gate.draw({ cord.getpCX(), cord.getpCY(), gate.getWidth() / SHRINK, gate.getHeight() / SHRINK }, { ALLREGION });
				gate.collisionAABB(pan);
			}
			if (demo1.getmapnum() == 0)
			{
				cord.calMapCamera(demo1, npcPotion);
				npcPotion.draw({ cord.getpCX(),cord.getpCY(),npcPotion.getWidth() / SHRINK,npcPotion.getHeight() / SHRINK }, { ALLREGION });
				npcPotion.npcAABB(pan);
			}
			for (int i = 0; i < PROPNUM; i++)
			{
				window.setVP(MAXHP + i);
				if (pan.getKey() == true && i == 0) //key
				{
					prop_v[0].draw();
				}
				if (i == 1) //potion
				{
					prop_v[1].draw();
					number[pan.getPotionNum()].draw();
				}
				frame.draw();

			}
			window.setVP(-1);
			for (int i = 0; i < fire.size(); i++)
			{
				cord.calMapCamera(demo1, fire[i]);
				fire[i].draw({ ALLREGION }, { cord.getpCX(), cord.getpCY(), fire[i].getWidth(), fire[i].getHeight() });
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
				if (pan.getKey() == true && i == 0) //key
				{
					prop_v[0].draw();
				}
				if (i == 1) //potion
				{
					prop_v[1].draw();
					number[pan.getPotionNum()].draw();
				}
				frame.draw();

			}
			drawCoinNum(numberc, window, pan.getCoin(), coin);
			window.setVP(MAXHP + PROPNUM);
			demo1.draw({ 0, 0, WINDOWW / 6 , WINDOWW / 6 }, { ALLREGION });
			filledCircleColor(window.getRenderer(), (pan.getX() + pan.getWidth() / 2) / 12, (pan.getY() + pan.getHeight() / 2) / 8, 2, 0xFF0000FF);
			window.setVP(MAXHP + PROPNUM + 1);
			coin.draw({ ALLREGION }, { 0, 0, coin.getWidth() / 8 , coin.getHeight() / 8 });
			window.setVP(MAXHP + PROPNUM + 2);
			flash.draw();
			boxRGBA(window.getRenderer(), 0, 0, flash.getWidth(), 0 + (flash.getHeight() - flash.getHeight() * pan.getRushCD() / (RUSHCD / RUSHTIMER)), 0x9E, 0x9E, 0x9E, 0x99);

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
			cord.calMapCamera(demo1, pan);
			pan.draw({ ALLREGION }, { cord.getpCX(), cord.getpCY(), pan.getWidth() / SHRINK, pan.getHeight() / SHRINK });
			for (int i = 0; i < Monsv.size(); i++)
			{
				if (!Monsv[i]->getDeadFlag())
				{
					cord.calMapCamera(demo1, *Monsv[i]);
					Monsv[i]->draw({ cord.getpCX(),cord.getpCY(),Monsv[i]->getWidth() / SHRINK,Monsv[i]->getHeight() / SHRINK }, { ALLREGION });
				}
			}
			for (int i = 0; i < fire.size(); i++)
			{
				cord.calMapCamera(demo1, fire[i]);
				fire[i].draw({ ALLREGION }, { cord.getpCX(), cord.getpCY(), fire[i].getWidth(), fire[i].getHeight() });
			}
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
			window.setVP(MAXHP + PROPNUM + 1);
			coin.draw({ ALLREGION }, { 0, 0, coin.getWidth() / 8 , coin.getHeight() / 8 });
			window.setVP(MAXHP + PROPNUM + 2);
			flash.draw();
			boxRGBA(window.getRenderer(), 0, 0, flash.getWidth(), 0 + (flash.getHeight() - flash.getHeight() * pan.getRushCD() / (RUSHCD / RUSHTIMER)), 0x9E, 0x9E, 0x9E, 0x99);

			window.setVP(-1);
			slot1.draw();
			back.draw();
			window.display();
			break;
		}
		case OVER:
		{

			demo1.draw({ ALLREGION }, demo1.getcamera());
			cord.calMapCamera(demo1, pan);
			pan.draw({ ALLREGION }, { cord.getpCX(), cord.getpCY(), pan.getWidth() / SHRINK, pan.getHeight() / SHRINK });

			for (int i = 0; i < Monsv.size(); i++)
			{
				if (!Monsv[i]->getDeadFlag())
				{
					cord.calMapCamera(demo1, *Monsv[i]);
					Monsv[i]->draw({ cord.getpCX(),cord.getpCY(),Monsv[i]->getWidth() / SHRINK,Monsv[i]->getHeight() / SHRINK }, { ALLREGION });
				}
			}

			thekey.gotKey(pan);
			if (demo1.getmapnum() == 3)
			{
				cord.calMapCamera(demo1, thekey);
				thekey.draw({ cord.getpCX(),cord.getpCY(),thekey.getWidth() / SHRINK,thekey.getHeight() / SHRINK }, { ALLREGION });
			}
			if (demo1.getmapnum() == 4)
			{
				cord.calMapCamera(demo1, gate);
				gate.draw({ cord.getpCX(), cord.getpCY(), gate.getWidth() / SHRINK, gate.getHeight() / SHRINK }, { ALLREGION });
				gate.collisionAABB(pan);
			}
			for (int i = 0; i < PROPNUM; i++)
			{
				window.setVP(MAXHP + i);
				if (pan.getKey() == true && i == 0) //key
				{
					prop_v[0].draw();
				}
				if (i == 1) //potion
				{
					prop_v[1].draw();
					number[pan.getPotionNum()].draw();
				}
				frame.draw();

			}
			window.setVP(-1);
			for (int i = 0; i < fire.size(); i++)
			{
				cord.calMapCamera(demo1, fire[i]);
				fire[i].draw({ ALLREGION }, { cord.getpCX(), cord.getpCY(), fire[i].getWidth(), fire[i].getHeight() });
			}

			for (int i = 0; i < MAXHP; i++)
			{
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
				if (pan.getKey() == true && i == 0) //key
				{
					prop_v[0].draw();
				}
				if (i == 1) //potion
				{
					prop_v[1].draw();
					number[pan.getPotionNum()].draw();
				}
				frame.draw();

			}
			drawCoinNum(numberc, window, pan.getCoin(), coin);
			window.setVP(MAXHP + PROPNUM);
			demo1.draw({ 0, 0, WINDOWW / 6 , WINDOWW / 6 }, { ALLREGION });
			filledCircleColor(window.getRenderer(), (pan.getX() + pan.getWidth() / 2) / 12, (pan.getY() + pan.getHeight() / 2) / 8, 2, 0xFF0000FF);
			window.setVP(MAXHP + PROPNUM + 1);
			coin.draw({ ALLREGION }, { 0, 0, coin.getWidth() / 8 , coin.getHeight() / 8 });
			window.setVP(MAXHP + PROPNUM + 2);
			flash.draw();
			boxRGBA(window.getRenderer(), 0, 0, flash.getWidth(), 0 + (flash.getHeight() - flash.getHeight() * pan.getRushCD() / (RUSHCD / RUSHTIMER)), 0x9E, 0x9E, 0x9E, 0x99);

			window.setVP(-1);
			fail.draw();
			window.display();
			break;
		}
		}
	}
	pan.close();
	demo1.close();
	fail.close();
	resume.close();
	menu.close();

	save.close();
	slot1.close();
	back.close();

	for (int i = 0; i < Monsv.size(); i++)
	{
		Monsv[i]->close();
		SDL_RemoveTimer(Monsv[i]->AIID);
	}

	Monsv.clear();

	for (int i = 0; i < tempa.size(); i++)
		tempa[i].close();
	tempa.clear();
	for (int i = 0; i < tempb.size(); i++)
		tempb[i].close();
	tempb.clear();
	for (int i = 0; i < tempc.size(); i++)
		tempc[i].close();
	tempc.clear();
	for (int i = 0; i < tempd.size(); i++)
		tempd[i].close();
	tempd.clear();

	for (int i = 0; i < mfire.size(); i++)
		mfire[i].close();

	for (int i = 0; i < ATTACKNUM; i++)
		fire[i].close();

	gate.close();
	thekey.close();
	for (int i = 0; i < prop_v.size(); i++)
		prop_v[i].close();

	princess.close();
	npcPotion.close();
	h.close();
	potion.close();
	frame.close();
	flash.close();

	for (int i = 0; i < number.size(); i++)
		number[i].close();
	for (int i = 0; i < numberc.size(); i++)
		numberc[i].close();
}


void GSManager::GameClear(RenderWindow& window)
{
	Text congratulation("congratulation", "../fonts/akabara-cinderella.ttf", 60, TTF_STYLE_BOLD, { 0, 255, 255 }, BLENDED, { 100, 100, 100 }, window.getRenderer(), { WINDOWW / 2 - 190, WINDOWH / 2 - 30 }, { NULL, NULL }, NULL, SDL_FLIP_NONE, 100);
	Text back("back", "../fonts/akabara-cinderella.ttf", 60, TTF_STYLE_BOLD, { 0, 255, 255 }, BLENDED, { 100, 100, 100 }, window.getRenderer(), { WINDOWW / 2 -50, WINDOWH / 2 +30 }, { NULL, NULL }, NULL, SDL_FLIP_NONE, 100);
	
	
	Map congrats("../images/mapdemo1.png", window.getRenderer());

	while (!quit && GameState == GAMECLEAR)
	{

		while (SDL_PollEvent(&ev) != 0)
		{
			if (ev.type == SDL_QUIT)
				quit = true;
			ClearEvents(ev, this);
		}
		window.setVP(-1);
		window.clear();
		congrats.draw({ ALLREGION }, { ALLREGION });
		back.draw();
		congratulation.draw();
		window.display();
	}

	congrats.close();
	congratulation.close();
}

void GSManager::drawCoinNum(std::vector<Object>& cv, RenderWindow& window, int coinn, Object& Coin)
{
	int hun, ten, one, cointemp;
	cointemp = coinn;
	one = cointemp % 10;
	cointemp /= 10;
	ten = cointemp % 10;
	cointemp /= 10;
	hun = cointemp % 10;

	window.setVP(MAXHP + PROPNUM + 2);
	cv[hun].draw({ ALLREGION }, { 0, 0, Coin.getWidth() / 8 , Coin.getHeight() / 8 });
	window.setVP(MAXHP + PROPNUM + 3);
	cv[ten].draw({ ALLREGION }, { 0, 0, Coin.getWidth() / 8 , Coin.getHeight() / 8 });
	window.setVP(MAXHP + PROPNUM + 4);
	cv[one].draw({ ALLREGION }, { 0, 0, Coin.getWidth() / 8 , Coin.getHeight() / 8 });
}

void GSManager::setGameState(int gs)
{
	GameState = gs;
}

int GSManager::getGameState()
{
	return GameState;
}

