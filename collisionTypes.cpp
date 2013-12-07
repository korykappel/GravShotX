// Programming 2D Games
// Copyright (c) 2011, 2012 by: 
// Charles Kelly
// Collision types demo
// Press '1', '2' or '3' to select collision type for ship.

#include "collisionTypes.h"

//=============================================================================
// Constructor
//=============================================================================
CollisionTypes::CollisionTypes()
{
	scoreIndicator = new TextDX();
}

//=============================================================================
// Destructor
//=============================================================================
CollisionTypes::~CollisionTypes()
{
    releaseAll();           // call onLostDevice() for every graphics item
}

//=============================================================================
// Initializes the game
// Throws GameError on error
//=============================================================================
void CollisionTypes::initialize(HWND hwnd)
{
    Game::initialize(hwnd); // throws GameError

	///////////////////////
	// Menu Initialization
	///////////////////////

	mainMenu = new Menu();
	mainMenu->initialize(graphics, input);

	mainMenu->setMenuHeader("Main Menu");
	mainMenu->setMenuItem("Start Game");
	mainMenu->setMenuItem("Exit Game");
	mainMenu->setVisible(true);
	mainMenu->setActive(true);

	// Avatar texture manager
    if (!avatarTM.initialize(graphics,AVATAR_IMAGE))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing avatar texture"));

	if (!enemyShipTM.initialize(graphics,ENEMYSHIP_IMAGE))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing enemy textures"));

	if (!shieldTM.initialize(graphics,SHIELD_IMAGE))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing shield textures"));

	if (!bungeeTM.initialize(graphics,BUNGEE_IMAGE))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing bungee textures"));

	if (!avatarBulletTM.initialize(graphics,AVATARBULLET_IMAGE))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing avatarBullet textures"));

	if (!enemyTankTM.initialize(graphics,TANK_IMAGE))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing tank textures"));

	if (!enemyBulletTM.initialize(graphics,ENEMYBULLET_IMAGE))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing avatarBullet textures"));

	if (!markerTM.initialize(graphics,MARKER_IMAGE))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing marker textures"));

	if (!menuScreenTM.initialize(graphics,MENU_IMAGE))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing menu textures"));

	if (!timeTM.initialize(graphics,HEALTH_IMAGE))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing health textures"));

	if (!barTM.initialize(graphics,BAR_IMAGE))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing bar textures"));

	if (!explosionTM.initialize(graphics,EXPLOSION_IMAGE))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing explosion textures"));

	//BACKGROUNDS:
	if (!background1TM.initialize(graphics,BACKGROUND1_IMAGE))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing background textures"));

	if (!midground1TM.initialize(graphics,MIDGROUND1_IMAGE))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing midground textures"));

	if (!background2TM.initialize(graphics,BACKGROUND2_IMAGE))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing background textures"));

	if (!midground2TM.initialize(graphics,MIDGROUND2_IMAGE))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing midground textures"));

	if (!background3TM.initialize(graphics,BACKGROUND3_IMAGE))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing background textures"));

	if (!midground3TM.initialize(graphics,MIDGROUND3_IMAGE))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing midground textures"));

	//if (!baseDestroyedTM.initialize(graphics,BASEDESTROYED_IMAGE))
 //       throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing midground textures"));
	if (!creditsTM.initialize(graphics,CREDITS_IMAGE))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing midground textures"));
	if (!endScreenTM.initialize(graphics,ENDSCREEN_IMAGE))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing midground textures"));
	if (!levelCompleteTM.initialize(graphics,LEVELCOMPLETE_IMAGE))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing midground textures"));
	if (!youDiedTM.initialize(graphics,YOUDIED_IMAGE))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing midground textures"));

	//INITIALIZE OBJECTS:

	//if (!baseDestroyed.initialize(graphics, 0, 0, 0, &baseDestroyedTM))
	//	throw(GameError(gameErrorNS::WARNING, "menu not initialized"));
	if (!credits.initialize(graphics, 0, 0, 0, &creditsTM))
		throw(GameError(gameErrorNS::WARNING, "menu not initialized"));
	if (!endScreen.initialize(graphics, 0, 0, 0, &endScreenTM))
		throw(GameError(gameErrorNS::WARNING, "menu not initialized"));
	if (!levelComplete.initialize(graphics, 0, 0, 0, &levelCompleteTM))
		throw(GameError(gameErrorNS::WARNING, "menu not initialized"));
	if (!youDied.initialize(graphics, 0, 0, 0, &youDiedTM))
		throw(GameError(gameErrorNS::WARNING, "menu not initialized"));

	//AVATAR:
	if (!avatar.initialize(this, avatarNS::WIDTH, avatarNS::HEIGHT, avatarNS::COLS, &avatarTM))
		throw(GameError(gameErrorNS::WARNING, "Paddle not initialized"));
	// Avatar object initialization
    avatar.setEdge(COLLISION_BOX_AVATAR);
	avatar.setVisible(true);
	avatar.setFrames(avatarNS::FLY_START, avatarNS::FLY_END);
	avatar.setCurrentFrame(avatarNS::FLY_START);
	avatar.setFrameDelay(.1);
	//avatar.setForwardAndBack(true);
	//avatar.setLoop(false);

	if (!menuScreen.initialize(graphics, 0, 0, 0, &menuScreenTM))
		throw(GameError(gameErrorNS::WARNING, "menu not initialized"));

	if (!marker.initialize(graphics, 0, 0, 0, &markerTM))
			throw(GameError(gameErrorNS::WARNING, "marker not initialized"));
	marker.setVisible(false);
	marker.setY(GAME_HEIGHT - marker.getHeight() - 10);
	
	//BACKGROUNDS:
	if (!Level_1_Background1.initialize(graphics, 0, 0, 0, &background1TM))
			throw(GameError(gameErrorNS::WARNING, "background not initialized"));
	if (!Level_1_Background2.initialize(graphics, 0, 0, 0, &background1TM))
			throw(GameError(gameErrorNS::WARNING, "background not initialized"));
	Level_1_Background1.setY(0);
	Level_1_Background2.setY(0);

	if (!Level_1_Midground1.initialize(graphics, 0, 0, 0, &midground1TM))
			throw(GameError(gameErrorNS::WARNING, "midground not initialized"));
	if (!Level_1_Midground2.initialize(graphics, 0, 0, 0, &midground1TM))
			throw(GameError(gameErrorNS::WARNING, "midground not initialized"));
	Level_1_Midground1.setY(0);
	Level_1_Midground2.setY(0);

	if (!Level_2_Background1.initialize(graphics, 0, 0, 0, &background2TM))
			throw(GameError(gameErrorNS::WARNING, "background not initialized"));
	if (!Level_2_Background2.initialize(graphics, 0, 0, 0, &background2TM))
			throw(GameError(gameErrorNS::WARNING, "background not initialized"));
	
	Level_2_Background1.setY(0);
	Level_2_Background2.setY(0);
	
	if (!Level_2_Midground1.initialize(graphics, 0, 0, 0, &midground2TM))
			throw(GameError(gameErrorNS::WARNING, "midground not initialized"));
	if (!Level_2_Midground2.initialize(graphics, 0, 0, 0, &midground2TM))
			throw(GameError(gameErrorNS::WARNING, "midground not initialized"));
	Level_2_Midground1.setY(350);
	Level_2_Midground2.setY(350);
	//Level_2_Midground2.setVisible(true);

	if (!Level_3_Background1.initialize(graphics, 0, 0, 0, &background3TM))
			throw(GameError(gameErrorNS::WARNING, "background not initialized"));
	if (!Level_3_Background2.initialize(graphics, 0, 0, 0, &background3TM))
			throw(GameError(gameErrorNS::WARNING, "background not initialized"));
	Level_3_Background1.setY(0);
	Level_3_Background2.setY(0);

	if (!Level_3_Midground1.initialize(graphics, 0, 0, 0, &midground3TM))
			throw(GameError(gameErrorNS::WARNING, "midground not initialized"));
	if (!Level_3_Midground2.initialize(graphics, 0, 0, 0, &midground3TM))
			throw(GameError(gameErrorNS::WARNING, "midground not initialized"));
	Level_3_Midground1.setY(350);
	Level_3_Midground2.setY(350);


	//BUNGEES:
	//for(int i = 0; i < 3; i++)
	//{
		if (!bungees[0].initialize(this, bungeeNS::WIDTH, bungeeNS::HEIGHT, 0, &bungeeTM))
			throw(GameError(gameErrorNS::WARNING, "Puck not initialized"));
		bungees[0].setCollisionType(entityNS::BOX);
	//}

	//TIME
	if (!timeBar.initialize(graphics, 0, 0, 0, &timeTM))
			throw(GameError(gameErrorNS::WARNING, "health not initialized"));
	timeBar.setX(23);
	timeBar.setY(77);

	//BAR
	if (!bar.initialize(graphics, 0, 0, 0, &barTM))
			throw(GameError(gameErrorNS::WARNING, "bar not initialized"));
	bar.setX(timeBar.getX()-2);
	bar.setY(timeBar.getY()-1);

	//SHIELD:
	if (!shield.initialize(this, 0, 0, 0, &shieldTM))
			throw(GameError(gameErrorNS::WARNING, "shield not initialized"));
	shield.setCollisionType(entityNS::BOX);
	shield.setEdge(COLLISION_BOX_SHIELD); 
	

	//ENEMY BULLETS
	for (int i = 0; i<10; i++)
	{
		if (!shipBullets[i].initialize(this, bulletNS::WIDTH, bulletNS::HEIGHT, 0,&enemyBulletTM))
			throw(GameError(gameErrorNS::WARNING, "bullet not initialized"));
			shipBullets[i].setCollisionType(entityNS::BOX);
			shipBullets[i].setEdge(COLLISION_BOX_BULLET);
	}
	for (int i = 0; i<10; i++)
	{
		if (!tankBullets[i].initialize(this, bulletNS::WIDTH, bulletNS::HEIGHT, 0,&enemyBulletTM))
			throw(GameError(gameErrorNS::WARNING, "bullet not initialized"));
			tankBullets[i].setCollisionType(entityNS::BOX);
			tankBullets[i].setEdge(COLLISION_BOX_BULLET);
	}

	//AVATAR BULLETS
	for (int i = 0; i<3; i++)
	{
		if (!avatarBullets[i].initialize(this, bulletNS::WIDTH, bulletNS::HEIGHT, 0,&avatarBulletTM))
			throw(GameError(gameErrorNS::WARNING, "bullet not initialized"));
			avatarBullets[i].setCollisionType(entityNS::BOX);
			avatarBullets[i].setEdge(COLLISION_BOX_BULLET);
	}

	//ENEMIES:
	//SHIPS:
	for (int i = 0; i<7; i++)
	{
		if (!enemyShips[i].initialize(this, shipNS::WIDTH, shipNS::HEIGHT, shipNS::COLS, &enemyShipTM, scoreIndicator))
			throw(GameError(gameErrorNS::WARNING, "Ship not initialized"));
		enemyShips[i].setCollisionType(entityNS::BOX);
		enemyShips[i].setEdge(COLLISION_BOX_SHIP);
		enemyShips[i].setFrames(shipNS::FLY_START, shipNS::FLY_END);
		enemyShips[i].setCurrentFrame(shipNS::FLY_START);
		enemyShips[i].setFrameDelay(0.1);
		enemyShips[i].setType(SHIP);

		//enemies[i] = &enemyShips[i];
	}

	//TANKS:
	for (int i=0; i<7; i++)
	{
		if (!enemyTanks[i].initialize(this, tankNS::WIDTH, tankNS::HEIGHT, 0, &enemyTankTM, scoreIndicator))
			throw(GameError(gameErrorNS::WARNING, "Tank not initialized"));
		enemyTanks[i].setCollisionType(entityNS::BOX);
		enemyTanks[i].setEdge(COLLISION_BOX_TANK);
		enemyTanks[i].setType(TANK);

		//enemies[i+5] = &enemyTanks[i];
	}

	//EXPLOSIONS
	for (int i=0; i<10; i++)
	{
		if (!explosion[i].initialize(graphics, 64, 64, 4, &explosionTM))
			throw(GameError(gameErrorNS::WARNING, "explosion not initialized"));
		explosion[i].setFrames(0, 7);
		explosion[i].setFrameDelay(0.1f);
	}

	if(font.initialize(graphics, 25, true, false, "Small Fonts") == false)
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing DirectX font"));
	font.setFontColor(graphicsNS::BLACK);

	if(invincible.initialize(graphics, 40, true, false, "Small Fonts") == false)
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing DirectX font"));
	invincible.setFontColor(graphicsNS::ORANGE);

	if(scoreText.initialize(graphics, 40, true, false, "Small Fonts") == false)
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing DirectX font"));
	scoreText.setFontColor(graphicsNS::YELLOW);


	//for(int i = 0; i < 4; i++)
	//{
		//if(scoreIndicators[0]->initialize(graphics, 20, true, false, "Small Fonts") == false)
		//	throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing DirectX font"));
		
		scoreIndicator->initialize(graphics, 30, true, false, "Small Fonts");
		scoreIndicator->setFontColor(graphicsNS::YELLOW);
	//}


	//MISC.
	srand(time(0));
	score = 0;
	invincibility = false;
	totalScore = 0;
	
	
	//currentlyHit1 = NULL;
	//currentlyHit2 = NULL;
	//numMarked = 0;
	//groundLocX = 0;
	//depressedLastFrame = false;
	//shipSpawnTime = 0;
	//tankSpawnTime = 0;
	//baseHealth = 100;

	
	startLevelTime = GetTickCount();

	//STATE
	timeInState = 0;
	gameStates = menu;
	gameStart = false;


	//AUDIO
	audio->playCue(MENU_SONG);

    return;
}

//=============================================================================
// Keeps track of what state we are in
//=============================================================================
void CollisionTypes::gameStateUpdate()
{
	timeInState += frameTime;
	timeLeftOnLevel -= frameTime;

	if(input->isKeyDown(ENTER_KEY))
		enterDepressedLastFrame = true;
	if (!input->isKeyDown(VK_RETURN) && enterDepressedLastFrame)
	{
		enterDepressedLastFrame = false;
		if(gameStates == levelEnd)
		{
			level++;
			initializeLevel();
			gameStates = gamePlay;
			timeInState = 0;
		}
		else if(gameStates == restart)
		{
			initializeLevel();
			gameStates = gamePlay;
			timeInState = 0;
		}
		else if(gameStates == win)
		{
			gameStates = menu;
			gameStart = false;
			timeInState = 0;
		}
		else if (gameStates==menu && gameStart)
		{
			
			level = 1;
			initializeLevel();
			gameStates = gamePlay;
			timeInState = 0;
		}
	}
	
	/*if (gameStates==menu && gameStart)
	{
		level = 1;
		initializeLevel();
		gameStates = gamePlay;
		timeInState = 0;
	}*/
	else if (gameStates==gamePlay && input->isKeyDown(VK_ESCAPE))
	{
		gameStates = quit;
		timeInState = 0;
	}
	else if(gameStates == gamePlay && level == 3 && timeInState >= endLevelTime)  //GetTickCount()-startLevelTime >= endLevelTime
	{
		totalScore += score;
		gameStates = win;
		timeInState = 0;
	}
	else if (gameStates==gamePlay && (timeInState > endLevelTime) && (level != 3))  //GetTickCount()-startLevelTime >= endLevelTime
	{
		
		gameStates = levelEnd;
		timeInState = 0;
	}
	else if(gameStates == gamePlay && avatar.getDead())
	{
		if(GetTickCount() - crashedTime >= 1000)
		{
			gameStates = restart;
			timeInState = 0;
		}
	}
	/*else if(gameStates == levelEnd && input->isKeyDown(ENTER_KEY))
	{
		level++;
		initializeLevel();
		gameStates = gamePlay;
		timeInState = 0;
	}*/
	/*else if(gameStates == restart && input->isKeyDown(ENTER_KEY))
	{
		initializeLevel();
		gameStates = gamePlay;
		timeInState = 0;
	}*/
	else if(gameStates == restart && input->isKeyDown(0x4D))  //go back to menu
	{
		gameStates = menu;
		gameStart = false;
		timeInState = 0;
	}
	else if(gameStates == win && input->isKeyDown(0x4D))
	{
		gameStates = menu;
		gameStart = false;
		timeInState = 0;
	}
	else if (gameStates==quit && timeInState > 1)
	{
		PostQuitMessage(0);
	}
	//else if(gameStates == gamePlay && baseHealth <= 0)
	//{
	//	gameStates = restart;
	//	timeInState = 0;
	//}
}

void CollisionTypes::resetEverything()
{
	avatar.setPosition(VECTOR2(100, GAME_HEIGHT/2));
	avatar.setX(avatar.getPositionX());
	avatar.setY(avatar.getPositionY());
	avatar.setDead(false);
	avatar.setVisible(true);
	avatar.setActive(true);
	avatar.setVelocity(VECTOR2(0,0));
	currentlyHit1 = NULL;
	currentlyHit2 = NULL;
	numMarked = 0;
	groundLocX = 0;
	depressedLastFrame = false;
	shipSpawnTime = 0;
	tankSpawnTime = 0;
	//baseHealth = 100;
	crashedTime = 0;

	marker.setVisible(false);
	bungees[0].clear();
	shield.setVisible(false);

	for(int i = 0; i < 10; i++)
	{
		shipBullets[i].setVisible(false);
		shipBullets[i].setActive(false);
		tankBullets[i].setVisible(false);
		tankBullets[i].setActive(false);
	}
	for(int i = 0; i < 3; i++)
	{
		avatarBullets[i].setVisible(false);
		avatarBullets[i].setActive(false);		
	}
	for(int i = 0; i < 7; i++)
	{		
		enemyShips[i].setVisible(false);
		enemyShips[i].setActive(false);
		enemyShips[i].setMarked(false);
		enemyShips[i].setBungeed(false);
		enemyTanks[i].setVisible(false);
		enemyTanks[i].setActive(false);
		enemyTanks[i].setMarked(false);
		enemyTanks[i].setBungeed(false);
	}
	for(int i = 0; i < 10; i++)
	{
		explosion[i].setVisible(false);
		explosion[i].setLoop(false);
	}


	if(level == 1)
	{
		Level_1_Background1.setX(0);
		Level_1_Background2.setX(Level_1_Background1.getWidth());
		Level_1_Midground1.setX(0);
		Level_1_Midground2.setX(Level_1_Midground1.getWidth());
	}
	if(level == 2)
	{
		Level_2_Background1.setX(0);
		Level_2_Background2.setX(Level_2_Background1.getWidth());
		Level_2_Midground1.setX(0);
		Level_2_Midground2.setX(Level_1_Midground1.getWidth());
	}
	if(level == 3)
	{
		Level_3_Background1.setX(0);
		Level_3_Background2.setX(Level_3_Background1.getWidth());
		Level_3_Midground1.setX(0);
		Level_3_Midground2.setX(Level_3_Midground1.getWidth());
	}
}
//=============================================================================
// Initializes current level
//=============================================================================
void CollisionTypes::initializeLevel()
{
	resetEverything();

	if(level == 1)
	{
		audio->stopCue(MENU_SONG);
		audio->playCue(LEVEL_1_SONG);

		enemyBulletSpeed = 300;
		avatarBulletSpeed = 600;
		//numTanks = 2;
		numTanks = 0;
		numShips = 4;
		//numTankBullets = 2;
		numTankBullets = 2;
		numShipBullets = 3;
		numAvatarBullets = 3;
		//tankSpeed = 80;
		//shipSpeed = rand()%100 + 150;
		//tankSpawnRate = 10;
		//shipSpawnRate = 10;
		endLevelTime = 45.0;
		timeLeftOnLevel = endLevelTime;
		startLevelTime = GetTickCount();

		for(int i = 0; i < numShips; i++)
			enemies[i] = &enemyShips[i];
		for(int i = 0; i < numTanks; i++)
			enemies[i+numShips] = &enemyTanks[i];

	}
	else if(level == 2)
	{
		audio->stopCue(LEVEL_1_SONG);
		audio->playCue(LEVEL_2_SONG);

		enemyBulletSpeed = 300;
		avatarBulletSpeed = 600;
		numTanks = 2;
		numShips = 5;
		numTankBullets = 2;
		numShipBullets = 3;	
		numAvatarBullets = 3;
		tankSpeed = 100;
		//shipSpeed = 150;		
		//tankSpawnRate = 10;
		//shipSpawnRate = 10;
		endLevelTime = 45.0; 
		timeLeftOnLevel = endLevelTime;
		startLevelTime = GetTickCount();

		for(int i = 0; i < numShips; i++)
			enemies[i] = &enemyShips[i];
		for(int i = 0; i < numTanks; i++)
			enemies[i+numShips] = &enemyTanks[i];
	}
	else if(level == 3)
	{
		audio->stopCue(LEVEL_2_SONG);
		audio->playCue(LEVEL_3_SONG);

		enemyBulletSpeed = 300;
		avatarBulletSpeed = 600;
		numTanks = 3;
		numShips = 7;
		numTankBullets = 2;
		numShipBullets = 3;
		numAvatarBullets = 3;
		tankSpeed = 100;
		//shipSpeed = 180;		
		//tankSpawnRate = 10;
		//shipSpawnRate = 10;
		endLevelTime = 45.0; 
		timeLeftOnLevel = endLevelTime;
		startLevelTime = GetTickCount();
		
		for(int i = 0; i < numShips; i++)
			enemies[i] = &enemyShips[i];
		for(int i = 0; i < numTanks; i++)
			enemies[i+numShips] = &enemyTanks[i];
	}
}

//=============================================================================
// Update all game items
//=============================================================================
void CollisionTypes::update()
{
	gameStateUpdate();

	if(input->wasKeyPressed(VK_SPACE) && !invincibility)
		invincibility = true;
	else if(input->wasKeyPressed(VK_SPACE) && invincibility)
		invincibility = false;

	switch (gameStates)
	{
		case menu:

			score = 0;
			totalScore = 0;

			audio->stopCue(CREDITS_SONG);

			// Exit Game chosen 
			if (mainMenu->getSelectedItem() == "Exit Game")
			PostQuitMessage(0);

			// Start Game chosen
			if (mainMenu->getSelectedItem() == "Start Game")
				gameStart = true;

			mainMenu->update();

			break;

		case quit:
			break;

		case restart:
			score = 0;
			break;

		case win: 
			
			audio->stopCue(LEVEL_3_SONG);
			audio->playCue(CREDITS_SONG);
			break;

		case levelEnd:
			totalScore += score;
			score = 0;
			break;
			
		case gamePlay:
		{

			//////////////////
			// Keyboard Input
			//////////////////

			//if (input->isKeyDown(D_KEY))	// Right 
			//	avatar.right();
			//if (input->isKeyDown(A_KEY))	// Left 
			//	avatar.left();
			//if (input->isKeyDown(W_KEY))	// Up 
			//	avatar.up();	
			//if (input->isKeyDown(S_KEY))	// Down
			//	avatar.down();

			if (input->isKeyDown(D_KEY))   {// Right 
                avatar.right();
                avatar.lastXDir = "right";
            } else if (!input->isKeyDown(A_KEY) && avatar.lastXDir == "right") {
                 avatar.stopRight();
            }
            if (input->isKeyDown(A_KEY))   {// Left 
                avatar.left();
                avatar.lastXDir = "left";
            } else if (!input->isKeyDown(D_KEY) && avatar.lastXDir == "left") {
                  avatar.stopLeft();
            }
            if (input->isKeyDown(W_KEY))  {// Up 
                avatar.up();        
                avatar.lastYDir = "up";
            } else if (!input->isKeyDown(S_KEY) && avatar.lastYDir == "up") {
                 avatar.stopUp();
            }
            if (input->isKeyDown(S_KEY))    {// Down
                avatar.down();
                avatar.lastYDir = "down";
            } else if (!input->isKeyDown(W_KEY) && avatar.lastYDir == "down") {
                 avatar.stopDown();
            }


			if (!input->getMouseLButton()) {
				depressedLastFrame = true;
			}


			//WAVES CODE HERE
			if((timeLeftOnLevel < 45 && timeLeftOnLevel > 37) || (timeLeftOnLevel < 28 && timeLeftOnLevel > 17) || timeLeftOnLevel < 8)
			{
				shipSpawnRate = 100;
				tankSpawnRate = 200;
			}
			if((timeLeftOnLevel < 37 && timeLeftOnLevel > 28) || (timeLeftOnLevel < 17 && timeLeftOnLevel > 8))
			{
				shipSpawnRate = 1;   //onslaught
				tankSpawnRate = 60;
			}

		
			//AT RANDOM TIME INTERVALS, call spawning enemy ships
			if(GetTickCount() - 1000 > shipSpawnTime)
			{
				tempRand = rand()%shipSpawnRate;  //MAKE VALUES DEPENDING ON LEVEL
				if(tempRand == 0)
					spawnEnemyShip();
			}

			//AT RANDOM TIME INTERVALS, call spawning enemy ships
			if(GetTickCount() - 1000 > tankSpawnTime)
			{
				tempRand = rand()%tankSpawnRate;  //MAKE VALUES DEPENDING ON LEVEL
				if(tempRand == 0)
					spawnEnemyTank();
			}

			//SPAWN SHIELD AT CERTAIN TIMES
			spawnShield();

	
			shipsShoot();
			tanksShoot();
			avatarShoot();
			shipToGround();
			createBungee();

			//reset enemies
			for(int i = 0; i < numShips+numTanks; i++)
			{
				if(enemies[i]->getNeedsReset())   
					resetEnemy(enemies[i]);
			}


			for(int i = 0; i < numAvatarBullets; i++)
			{
				int tempGroundLoc = avatarBullets[i].getGroundLoc();
				if(tempGroundLoc != 0)
				{
					groundLocX = tempGroundLoc;
					marker.setX(tempGroundLoc);
					marker.setVisible(true);
				}
				avatarBullets[i].setGroundLoc(0);
			}


			//SHIELD STATE STUFF:
			if(shield.getAttached())
			{
				shield.setX(avatar.getCenterX()-shield.getScaleX()*shield.getWidth()/2);
				shield.setY(avatar.getCenterY()-shield.getScaleY()*shield.getHeight()/2);
			}
			if(!shield.getAttached())
			{
				shield.setScaleX(.2);
				shield.setScaleY(.2);
			}
			else
			{
				shield.setScaleX(shieldNS::SCALE);
				shield.setScaleY(shieldNS::SCALE);
			}
			if(shield.getHealth()<=0)
			{
				shield.setAttached(false);
				shield.setVisible(false);
				shield.setActive(false);
			}
						
	
			//////////////////
			// Update Objects
			//////////////////

			//for(int i = 0; i < 3; i++)
			//{
				bungees[0].update(frameTime);
			//}
			avatar.update(frameTime);
			shield.update(frameTime);

			for (int i = 0; i<numShips+numTanks; i++)
				enemies[i]->update(frameTime);

			for (int i = 0; i<numAvatarBullets; i++)
				avatarBullets[i].update(frameTime);

			for (int i = 0; i<numShipBullets; i++)
				shipBullets[i].update(frameTime);

			for (int i = 0; i<numTankBullets; i++)
				tankBullets[i].update(frameTime);

			for (int i = 0; i<10; i++)
			{
				if (explosion[i].getAnimationComplete())
					explosion[i].setVisible(false);

				explosion[i].update(frameTime);
			}

			moveBackground();

			break;
		}
	}
	
}
void CollisionTypes::spawnShield()
{
	if(!shield.getVisible())
		{
			//shipSpawnTime = GetTickCount();
			shield.setHealth(2);
			shield.setPosition(VECTOR2(GAME_WIDTH+100, rand()%500));
			shield.setX(shield.getPositionX());
			shield.setY(shield.getPositionY());
			shield.setVelocity(VECTOR2(-shieldNS::SPEED,0));
			shield.setVisible(true);
			shield.setActive(true);

		}
}


void CollisionTypes::moveBackground()
{
	static int startBackground = GetTickCount();
	static int startMidground = GetTickCount();
	if(level == 1)
	{
		// Move Background
		if(GetTickCount()-startBackground >= 50)
		{
			Level_1_Background1.setX(Level_1_Background1.getX()-1);
			Level_1_Background2.setX(Level_1_Background2.getX()-1);
			startBackground = GetTickCount();
		}
		// Move Midground
		if(GetTickCount()-startMidground >= 10)
		{
			Level_1_Midground1.setX(Level_1_Midground1.getX()-1);
			Level_1_Midground2.setX(Level_1_Midground2.getX()-1);
			startMidground = GetTickCount();
		}

		if(Level_1_Background1.getX()+Level_1_Background1.getWidth() <= 0)
			Level_1_Background1.setX(Level_1_Background2.getX()+Level_1_Background2.getWidth());
		if(Level_1_Background2.getX()+Level_1_Background2.getWidth() <= 0)
			Level_1_Background2.setX(Level_1_Background1.getX()+Level_1_Background1.getWidth());

		if(Level_1_Midground1.getX()+Level_1_Midground1.getWidth() <= 0)
			Level_1_Midground1.setX(Level_1_Midground2.getX()+Level_1_Midground2.getWidth());
		if(Level_1_Midground2.getX()+Level_1_Midground2.getWidth() <= 0)
			Level_1_Midground2.setX(Level_1_Midground1.getX()+Level_1_Midground1.getWidth());
	}
	else if(level == 2)
	{
		// Move Background
		if(GetTickCount()-startBackground >= 50)
		{
			Level_2_Background1.setX(Level_2_Background1.getX()-1);
			Level_2_Background2.setX(Level_2_Background2.getX()-1);
			startBackground = GetTickCount();
		}
		// Move Midground
		if(GetTickCount()-startMidground >= 10)
		{
			Level_2_Midground1.setX(Level_2_Midground1.getX()-1);
			Level_2_Midground2.setX(Level_2_Midground2.getX()-1);
			startMidground = GetTickCount();
		}

		if(Level_2_Background1.getX()+Level_2_Background1.getWidth() <= 0)
			Level_2_Background1.setX(Level_2_Background2.getX()+Level_2_Background2.getWidth());
		if(Level_2_Background2.getX()+Level_2_Background2.getWidth() <= 0)
			Level_2_Background2.setX(Level_2_Background1.getX()+Level_2_Background1.getWidth());

		if(Level_2_Midground1.getX()+Level_2_Midground1.getWidth() <= 0)
			Level_2_Midground1.setX(Level_2_Midground2.getX()+Level_2_Midground2.getWidth());
		if(Level_2_Midground2.getX()+Level_2_Midground2.getWidth() <= 0)
			Level_2_Midground2.setX(Level_2_Midground1.getX()+Level_2_Midground1.getWidth());
	}
	else if(level == 3) 
	{
		// Move Background
		if(GetTickCount()-startBackground >= 50)
		{
			Level_3_Background1.setX(Level_3_Background1.getX()-1);
			Level_3_Background2.setX(Level_3_Background2.getX()-1);
			startBackground = GetTickCount();
		}
		// Move Midground
		if(GetTickCount()-startMidground >= 10)
		{
			Level_3_Midground1.setX(Level_3_Midground1.getX()-1);
			Level_3_Midground2.setX(Level_3_Midground2.getX()-1);
			startMidground = GetTickCount();
		}

		if(Level_3_Background1.getX()+Level_3_Background1.getWidth() <= 0)
			Level_3_Background1.setX(Level_3_Background2.getX()+Level_3_Background2.getWidth());
		if(Level_3_Background2.getX()+Level_3_Background2.getWidth() <= 0)
			Level_3_Background2.setX(Level_3_Background1.getX()+Level_3_Background1.getWidth());

		if(Level_3_Midground1.getX()+Level_3_Midground1.getWidth() <= 0)
			Level_3_Midground1.setX(Level_3_Midground2.getX()+Level_3_Midground2.getWidth());
		if(Level_3_Midground2.getX()+Level_3_Midground2.getWidth() <= 0)
			Level_3_Midground2.setX(Level_3_Midground1.getX()+Level_3_Midground1.getWidth());
	}
}

void CollisionTypes::createBungee()  //might be able to make this smaller if i make the bungee visible test first
{

	if(numMarked == 1 && groundLocX != 0)
	{
		if(currentlyHit1->getType() == SHIP)
		{
			//NEED TO MAKE THIS A FOR LOOP FOR ALL BUNGEES:
			if(bungees[0].getBungeeState() == none)   //STUPID TO RUN BOTH A VISIBLE AND BUNGEE STATE TEST, SINCE THEY GO TOGETHER
			{
				currentlyHit1->setBungeed(true);
				bungees[0].setBungeeState(enemyToGround);
				bungees[0].setPointer1(currentlyHit1);
				bungees[0].setGroundLoc(groundLocX);
				
				//currentlyHit1->setAttachedTo(&bungees[0]);
				numMarked = 0;
				currentlyHit1 = NULL;
				currentlyHit2 = NULL;
				groundLocX = 0;
				marker.setVisible(false);
			}
		}
	}

	if(numMarked == 2)
	{
		if(!bungees[0].getBungeeState() == none)  //WON'T NEED IF WE HAVE MULTIPLE BUNGEES
		{
			currentlyHit1->setMarked(false);
			currentlyHit2->setMarked(false);
		}
		else {
			currentlyHit1->setBungeed(true);
			currentlyHit2->setBungeed(true);
			bungees[0].setBungeeState(enemyToEnemy);
			bungees[0].setPointer1(currentlyHit1);
			bungees[0].setPointer2(currentlyHit2);
		}
		numMarked = 0;
		groundLocX = 0;
		marker.setVisible(false);
		currentlyHit1 = NULL;
		currentlyHit2 = NULL;
	}
}
void CollisionTypes::tanksShoot()
{
	for(int j = 0; j<numTanks; j++)
	{
		if(enemyTanks[j].getVisible() && !enemyTanks[j].getBungeed())
		{
			tempRand = rand()%400;	//MAKE VALUES DEPENDING ON LEVEL
			if(tempRand == 0)
			{
				for(int i = 0; i < numTankBullets; i++)
				{
					if(!tankBullets[i].getVisible())
					{
						audio->playCue(ENEMY_SHOT);

						double deltaX = (enemyTanks[j].getPositionX() + tankNS::WIDTH/2) - avatar.getPositionX();
						double deltaY = enemyTanks[j].getPositionY() - avatar.getPositionY();
						VECTOR2 v1(deltaX, deltaY);
						D3DXVec2Normalize(&v1, &v1);
						tankBullets[j].setRadians(atan2(deltaY, deltaX));
						tankBullets[i].setVisible(true);
						tankBullets[i].setActive(true);
						tankBullets[i].setX(enemyTanks[j].getPositionX() + tankNS::WIDTH/2);
						tankBullets[i].setY(enemyTanks[j].getY());
						tankBullets[i].setVelocity(v1 * -enemyBulletSpeed);
				
						break;
					}
				}
			}
		}
	}
}
void CollisionTypes::shipsShoot()
{
	for(int j = 0; j<numShips; j++)
	{
		if(enemyShips[j].getVisible() && !enemyShips[j].getBungeed())
		{
			tempRand = rand()%400;	//MAKE VALUES DEPENDING ON LEVEL
			if(tempRand == 0)
			{
				for(int i = 0; i < numShipBullets; i++)
				{
					if(!shipBullets[i].getVisible())
					{
						audio->playCue(ENEMY_SHOT);

						shipBullets[i].setVisible(true);
						shipBullets[i].setActive(true);
						shipBullets[i].setX(enemyShips[j].getX());
						shipBullets[i].setY(enemyShips[j].getY()+enemyShips[j].getHeight()/2);
						shipBullets[i].setVelocity(VECTOR2(-enemyBulletSpeed, 0));
						
						break;
					}
				}
			}
		}
	}
}
void CollisionTypes::avatarShoot()
{
	if (!avatar.getDead() && input->getMouseLButton() && depressedLastFrame && input->getMouseX() > avatar.getX() + avatarNS::WIDTH) {
		
		depressedLastFrame = false;
		
		VECTOR2 vel = VECTOR2(avatar.getX() + avatarNS::WIDTH, avatar.getY() + (avatarNS::HEIGHT/2)) - VECTOR2(input->getMouseX(), input->getMouseY());
		D3DXVec2Normalize(&vel, &vel);

		for (int i = 0; i < numAvatarBullets; i++) {
			if (!avatarBullets[i].getVisible()) {

				audio->playCue(GRAVITY_SHOT);

				avatarBullets[i].setVisible(true);
				avatarBullets[i].setActive(true);
				avatarBullets[i].setX(avatar.getX()+avatar.getWidth());
				avatarBullets[i].setY(avatar.getY()+avatar.getHeight()/2);
				avatarBullets[i].setVelocity(vel * -avatarBulletSpeed);

				break;
			}
		}
	}
}
void CollisionTypes::shipToGround()
{
	for(int i = 0; i < numShips; i++)
	{
		if(enemyShips[i].getHitGround())
		{
			enemyShips[i].setVisible(false);
			enemyShips[i].setActive(false);
			enemyShips[i].setMarked(false);
			if(enemyShips[i].getBungeed())
			{
				score += 1;
				//score indicators
				enemies[i]->addScore(1,enemies[i]->getX(),enemies[i]->getY());

				enemyShips[i].setBungeed(false);
				bungees[0].clear();

				// Explosion
				for (int k = 0; k < 10; k++)
				{
					if (!explosion[k].getVisible())
					{
						//die
						audio->playRandomCue(EXPLOSION_1, EXPLOSION_2, EXPLOSION_3);

						explosion[k].setX(enemyShips[i].getCenterX() - explosion[k].getWidth()/2 );
						explosion[k].setY(enemyShips[i].getCenterY() - explosion[k].getHeight()/2 );
						explosion[k].setCurrentFrame(0);
						explosion[k].setVisible(true);
						break;
					}
				}
			}
			
			enemyShips[i].setHitGround(false);
			
		}
	}
}
void CollisionTypes::resetEnemy(Enemy* enemy)
{
	//if(enemy->getType() == SHIP)
	//		baseHealth -= 5;
	//else if(enemy->getType() == TANK)    //THIS IS WHERE THE BASE HEALTH DECREASE VALUES ARE
	//	baseHealth -= 10;

	if(enemy->getMarked() && currentlyHit1 == enemy)
	{
		enemy->setMarked(false);
		numMarked--;
		if(currentlyHit2 == NULL)
			currentlyHit1 = NULL;
		else 
		{
			currentlyHit1 = currentlyHit2;
			currentlyHit2 = NULL;
		}
	}
	else if(enemy->getMarked() && currentlyHit2 == enemy)
	{
		enemy->setMarked(false);
		currentlyHit2 = NULL;
		numMarked--;
	}

	enemy->setNeedsReset(false);
}
void CollisionTypes::spawnEnemyShip()
{
	if(level == 1)
		shipSpeed = rand()%100 + 150;
	if(level == 2)
		shipSpeed = rand()%100 + 155;
	if(level == 3)
		shipSpeed = rand()%100 + 165;
	//random y location
	//set enemy location and visible and velocity
	for(int i = 0; i < numShips; i++)
	{
		if(!enemyShips[i].getVisible())
		{
			shipSpawnTime = GetTickCount();
			enemyShips[i].setPosition(VECTOR2(GAME_WIDTH+100, rand()%500));
			enemyShips[i].setX(enemyShips[i].getPositionX());
			enemyShips[i].setY(enemyShips[i].getPositionY());
			enemyShips[i].setVelocity(VECTOR2(-shipSpeed,0));
			enemyShips[i].setVisible(true);
			enemyShips[i].setActive(true);

			/*if(level == 1)
				shipSpeed = rand()%100 + 150;
			if(level == 2)
				shipSpeed = rand()%100 + 155;
			if(level == 3)
				shipSpeed = rand()%100 + 165;*/
			break;
		}
	}
}
void CollisionTypes::spawnEnemyTank()
{
	//set enemy location and visible and velocity
	for (int i = 0; i < numTanks; i++)
	{
		if(!enemyTanks[i].getVisible())
		{
			tankSpawnTime = GetTickCount();
			enemyTanks[i].setPosition(VECTOR2(GAME_WIDTH+100, GAME_HEIGHT-tankNS::HEIGHT-15));
			enemyTanks[i].setX(enemyTanks[i].getPositionX());
			enemyTanks[i].setY(enemyTanks[i].getPositionY());
			enemyTanks[i].setVelocity(VECTOR2(-tankSpeed,0));
			enemyTanks[i].setVisible(true);
			enemyTanks[i].setActive(true);
			break;
		}
	}
}

//=============================================================================
// Artificial Intelligence
//=============================================================================
void CollisionTypes::ai()
{}

//=============================================================================
// Handle collisions
//=============================================================================
void CollisionTypes::collisions()
{
    collisionVector.x = 0;      // clear collision vector
    collisionVector.y = 0;

	///////////////////////
	// Collision Detection
	///////////////////////

	//between avatar and shield
	if(avatar.collidesWith(shield, collisionVector))
	{
		shield.setAttached(true);
		shield.setHealth(2);
	}
	//between shield and enemy bullets
	if(shield.getAttached())
	{
		for(int i = 0; i < numShipBullets; i++)
		{
			if(shield.collidesWith(shipBullets[i], collisionVector))
			{
				shield.setHealth(shield.getHealth()-1);
				shipBullets[i].setVisible(false);
				shipBullets[i].setActive(false);
			}
		}
		for(int i = 0; i < numTankBullets; i++)
		{
			if(shield.collidesWith(tankBullets[i], collisionVector))
			{
				shield.setHealth(shield.getHealth()-1);
				tankBullets[i].setVisible(false);
				tankBullets[i].setActive(false);	
			}
		}
	}

	//between shield and enemy:
	if(shield.getAttached())
	{
		for(int i = 0; i < numShips+numTanks; i++)
		{
			if(shield.collidesWith(*enemies[i], collisionVector))
			{
				shield.setHealth(shield.getHealth()-1);

				for (int k = 0; k < 10; k++)
				{
					if (!explosion[k].getVisible())
					{
						//die
						audio->playRandomCue(EXPLOSION_1, EXPLOSION_2, EXPLOSION_3);

						explosion[k].setX(enemies[i]->getCenterX() - explosion[k].getWidth()/2 );
						explosion[k].setY(enemies[i]->getCenterY() - explosion[k].getHeight()/2 );
						explosion[k].setCurrentFrame(0);
						explosion[k].setVisible(true);
						break;
					}
				}
				if(!enemies[i]->getBungeed())
				{
					enemies[i]->setVisible(false);
					enemies[i]->setActive(false);
				}
			}
		}
	}

	//between avatar and enemy:
	for(int i = 0; i < numShips+numTanks; i++)
	{
		if(avatar.collidesWith(*enemies[i], collisionVector))
		{
			crashedTime = GetTickCount();

			for (int k = 0; k < 10; k++)
			{
				if (!explosion[k].getVisible())
				{
					//die
					audio->playRandomCue(EXPLOSION_1, EXPLOSION_2, EXPLOSION_3);

					explosion[k].setX(avatar.getCenterX() - explosion[k].getWidth()/2 );
					explosion[k].setY(avatar.getCenterY() - explosion[k].getHeight()/2 );
					explosion[k].setCurrentFrame(0);
					explosion[k].setVisible(true);
					break;
				}
			}
			if(!invincibility)
			{
				for (int k = 0; k < 10; k++)
				{
					if (!explosion[k].getVisible())
					{
						//die
						explosion[k].setX(enemies[i]->getCenterX() - explosion[k].getWidth()/2 );
						explosion[k].setY(enemies[i]->getCenterY() - explosion[k].getHeight()/2 );
						explosion[k].setCurrentFrame(0);
						explosion[k].setVisible(true);
						break;
					}
				}
				avatar.setVisible(false);
				avatar.setActive(false);
				avatar.setDead(true);
			}

			if(!enemies[i]->getBungeed())
			{
				enemies[i]->setVisible(false);
				enemies[i]->setActive(false);
			}
		}
	}

	//between avatar and enemy Bullets:
	for(int i = 0; i < numShipBullets; i++)
	{
		if(avatar.collidesWith(shipBullets[i], collisionVector))
		{
			if(!invincibility)
			{
				crashedTime = GetTickCount();

				//Explosion
				for (int k = 0; k < 10; k++)
				{
					if (!explosion[k].getVisible())
					{
						//die
						audio->playRandomCue(EXPLOSION_1, EXPLOSION_2, EXPLOSION_3);

						explosion[k].setX(avatar.getCenterX() - explosion[k].getWidth()/2 );
						explosion[k].setY(avatar.getCenterY() - explosion[k].getHeight()/2 );
						explosion[k].setCurrentFrame(0);
						explosion[k].setVisible(true);
						break;
					}
				}
			
				avatar.setDead(true);
				avatar.setVisible(false);
				avatar.setActive(false);
			}
			shipBullets[i].setVisible(false);
			shipBullets[i].setActive(false);
		}
	}
	for(int i = 0; i < numTankBullets; i++)
	{
		if(avatar.collidesWith(tankBullets[i], collisionVector))
		{
			if(!invincibility)
			{
				crashedTime = GetTickCount();

				for (int k = 0; k < 10; k++)
				{
					if (!explosion[k].getVisible())
					{
						//die
						audio->playRandomCue(EXPLOSION_1, EXPLOSION_2, EXPLOSION_3);

						explosion[k].setX(avatar.getCenterX() - explosion[k].getWidth()/2 );
						explosion[k].setY(avatar.getCenterY() - explosion[k].getHeight()/2 );
						explosion[k].setCurrentFrame(0);
						explosion[k].setVisible(true);
						break;
					}
				}

				avatar.setDead(true);
				avatar.setVisible(false);
				avatar.setActive(false);
			}
			tankBullets[i].setVisible(false);
			tankBullets[i].setActive(false);	
		}
	}

	//between avatar and bungee:
	//COLLISION ON BUNGEE NOT WORKING
	//for(int i = 0; i < 3; i++)
	//{
		//if(avatar.collidesWith(bungees[0], collisionVector))
		//{
		//	//die
		//	gameStates = quit;
		//	//avatar.setVisible(false);
		//	//avatar.setActive(false);
		//}
	//}


	//between enemies
	for(int i = 0; i < numShips+numTanks; i++)
	{
		for(int j = 0; j < i; j++)
		{
			if(enemies[i]->collidesWith(*enemies[j], collisionVector))
			{
				if(!enemies[i]->getBungeed() && enemies[j]->getBungeed())		// If Enemy i does not have a bungee and Enemy j 
				{																	// does then Enemy i dies 
					// Explosion
					for (int k = 0; k < 10; k++)
					{
						if (!explosion[k].getVisible())
						{
							//die
							audio->playRandomCue(EXPLOSION_1, EXPLOSION_2, EXPLOSION_3);

							explosion[k].setX(enemies[i]->getCenterX() - explosion[k].getWidth()/2 - 10 );
							explosion[k].setY(enemies[i]->getCenterY() - explosion[k].getHeight()/2 - 10 );
							explosion[k].setCurrentFrame(0);
							explosion[k].setVisible(true);
							break;
						}
					}
					
					enemies[i]->setVisible(false);
					enemies[i]->setActive(false);
					if(enemies[i]->getMarked())
					{
						enemies[i]->setMarked(false);
						numMarked--;
					}
					score += 5;
					//score indicators
					enemies[i]->addScore(5,enemies[i]->getX(),enemies[i]->getY());
				}
				if(!enemies[j]->getBungeed() && enemies[i]->getBungeed())		// If Enemy j does not have a bungee and Enemy i
				{																	// does then Enemy j dies
					// Explosion
					for (int k = 0; k < 10; k++)
					{
						if (!explosion[k].getVisible())
						{
							//die
							audio->playRandomCue(EXPLOSION_1, EXPLOSION_2, EXPLOSION_3);

							explosion[k].setX(enemies[i]->getCenterX() - explosion[k].getWidth()/2 - 10 );
							explosion[k].setY(enemies[i]->getCenterY() - explosion[k].getHeight()/2 - 10 );
							explosion[k].setCurrentFrame(0);
							explosion[k].setVisible(true);
							break;
						}
					}
					
					enemies[j]->setVisible(false);
					enemies[j]->setActive(false);
					if(enemies[j]->getMarked())
					{
						enemies[j]->setMarked(false);
						numMarked--;
					}
					score += 5;
					//score indicators
					enemies[j]->addScore(5,enemies[j]->getX(),enemies[j]->getY());
				}
				if(enemies[j]->getBungeed() && enemies[i]->getBungeed())		// If Enemies j and i both have bungies they die
				{
					// Explosion
					for (int k = 0; k < 10; k++)
					{
						if (!explosion[k].getVisible())
						{
							//die
							audio->playRandomCue(EXPLOSION_1, EXPLOSION_2, EXPLOSION_3);

							explosion[k].setX(enemies[i]->getCenterX() - explosion[k].getWidth()/2 - 10 );
							explosion[k].setY(enemies[i]->getCenterY() - explosion[k].getHeight()/2 - 10 );
							explosion[k].setCurrentFrame(0);
							explosion[k].setVisible(true);
							break;
						}
					}
					
					for (int k = 0; k < 10; k++)
					{
						if (!explosion[k].getVisible())
						{
							//die
							explosion[k].setX(enemies[j]->getCenterX() - explosion[k].getWidth()/2 );
							explosion[k].setY(enemies[j]->getCenterY() - explosion[k].getHeight()/2 );
							explosion[k].setCurrentFrame(0);
							explosion[k].setVisible(true);
							break;
						}
					}

					enemies[i]->setVisible(false);
					enemies[i]->setActive(false);
					enemies[i]->setMarked(false);

					enemies[j]->setVisible(false);
					enemies[j]->setActive(false);
					enemies[j]->setMarked(false);

					enemies[i]->setBungeed(false);
					enemies[j]->setBungeed(false);
					

					score += 2;
					//score indicators
					enemies[i]->addScore(1,enemies[i]->getX(),enemies[i]->getY());
					enemies[j]->addScore(1,enemies[j]->getX(),enemies[j]->getY());


					//make a for loop if using multiple bungees
					bungees[0].clear();

					//only needed if we're gonna have multiple bungees:
					/*enemyShips[i].getAttachedTo()->clear();
					enemyShips[i].setAttachedTo(NULL);
					enemyShips[j].setAttachedTo(NULL);*/
				}
			}
		}
	}

	//AVATAR BULLET (bungee) AND ENEMIES
	for(int j = 0; j < numAvatarBullets; j++)
	{
		for(int i = 0; i < numShips+numTanks; i++)
		{
			if(enemies[i]->collidesWith(avatarBullets[j], collisionVector))
			{
				avatarBullets[j].setVisible(false);
				avatarBullets[j].setActive(false);
				avatarBullets[j].setVelocity(VECTOR2(0,0));
				
				if(!enemies[i]->getMarked())
				{
					enemies[i]->setMarked(true);
					
					if(currentlyHit1 == NULL) {
						currentlyHit1 = enemies[i];
						numMarked++;
					}
					else if(currentlyHit2 == NULL) {
						currentlyHit2 = enemies[i];
						numMarked++;
					}
					else { 
						currentlyHit2->setMarked(false);
						currentlyHit2 = enemies[i];
					}
				}
			}
		}
	}
}

//=============================================================================
// Render game items
//=============================================================================
void CollisionTypes::render()
{
    graphics->spriteBegin();                // begin drawing sprites
	
	std::stringstream scoreStream;

	switch (gameStates)
	{
		case menu:
			menuScreen.draw();
			mainMenu->displayMenu();
			break;

		case quit:
			break;

		case restart:
			if(avatar.getDead())
				youDied.draw();
			//else baseDestroyed.draw();
			break;

		case win: 
			endScreen.draw();
			

			scoreStream << "Total Score: " << totalScore;
			scoreText.print(scoreStream.str(), GAME_WIDTH/2+100, GAME_HEIGHT/2+90);

			if(timeInState > 5)
				credits.draw();

			break;

		case levelEnd:
			levelComplete.draw();
			scoreStream << "Total Score: " << totalScore;
			scoreText.print(scoreStream.str(), GAME_WIDTH/2+60, GAME_HEIGHT/2-30);

			break;

		case gamePlay:
		{
			if(level == 1)
			{
				Level_1_Background1.draw();
				Level_1_Background2.draw();
				Level_1_Midground1.draw();
				Level_1_Midground2.draw();
				font.setFontColor(graphicsNS::BLACK);
			}
			if(level == 2)
			{
				Level_2_Background1.draw();
				Level_2_Background2.draw();
				Level_2_Midground1.draw();
				Level_2_Midground2.draw();
				font.setFontColor(graphicsNS::BLACK);
			}
			if(level == 3)
			{
				Level_3_Background1.draw();
				Level_3_Background2.draw();
				Level_3_Midground1.draw();
				Level_3_Midground2.draw();
				font.setFontColor(graphicsNS::RED);
			}

			//for (int i = 0; i < 3; i++)
			//{
				bungees[0].draw();  //draw first
			//}

			for (int i = 0; i<numShips+numTanks; i++)
			{
				if(enemies[i]->getMarked())
					enemies[i]->draw(graphicsNS::ORANGE);
				else
					enemies[i]->draw();
			}

			for (int i = 0; i<numAvatarBullets; i++)
				avatarBullets[i].draw();

			for (int i = 0; i<numShipBullets; i++)
				shipBullets[i].draw();

			for (int i = 0; i<numTankBullets; i++)
				tankBullets[i].draw();

			for (int i = 0; i<10; i++)
				explosion[i].draw();

			shield.draw();
			avatar.draw();

			marker.draw();


			enemyTanks[0].getMarked();
			enemyTanks[1].getMarked();
			

			std::stringstream marked;
			std::stringstream cheat;

			if(invincibility)
			{
				cheat << "INVINCIBILITY ACTIVATED (trophies disabled)";
				invincible.print(cheat.str(), GAME_WIDTH/2-200, 20);
			}

			marked << "Score: " << score << std::endl //<< std::setprecision(3) 
				<< "Until Next Level: " << static_cast<int>(timeLeftOnLevel);
			font.print(marked.str(), 20, 20);

			bar.draw();
			timeBar.setScaleX(timeLeftOnLevel*(100.0/45.0));
			timeBar.draw();

			//display score indicators if needed
			for(int i = 0; i < numShips+numTanks; i++)
				enemies[i]->displayScore();

			break;
		}
	}

    graphics->spriteEnd();                  // end drawing sprites
}

//=============================================================================
// The graphics device was lost.
// Release all reserved video memory so graphics device may be reset.
//=============================================================================
void CollisionTypes::releaseAll()
{
	avatarTM.onLostDevice();
    Game::releaseAll();
    return;
}

//=============================================================================
// The grahics device has been reset.
// Recreate all surfaces.
//=============================================================================
void CollisionTypes::resetAll()
{
	avatarTM.onResetDevice();
    Game::resetAll();
    return;
}
