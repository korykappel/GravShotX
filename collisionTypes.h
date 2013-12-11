// Programming 2D Games
// Copyright (c) 2011,2012 by: 
// Charles Kelly
// collisionTypes.h v1.0

#ifndef _COLLISION_TYPES_H      // Prevent multiple definitions if this 
#define _COLLISION_TYPES_H      // file is included in more than one place
#define WIN32_LEAN_AND_MEAN

class CollisionTypes;

#include "game.h"
#include "textureManager.h"
#include "image.h"
#include <cmath>
#include <ctime>
#include "enemy.h"
#include "ship.h"
#include "tank.h"
#include "bungee.h"
#include "avatar.h"
#include "bullet.h"
#include "textDX.h"
#include "menu.h"
#include "shield.h"
#include "HighScoreEntry.h"
#include <sstream>
#include <iomanip>
#include <fstream>
#include <algorithm>

using namespace std;

enum TutorialScreen {tutorial1, tutorial2, tutorial3, tutorial4, tutorial5};

//=============================================================================
// This class is the core of the game
//=============================================================================
class CollisionTypes : public Game
{
private:
	// MENU
	Menu *mainMenu;

    // game items
    TextureManager bungeeTM, enemyShipTM, enemyTankTM, avatarTM, avatarBulletTM, enemyBulletTM, background1TM,
		midground1TM, background2TM, midground2TM, background3TM, midground3TM, markerTM, menuScreenTM, timeTM, barTM, explosionTM,
		baseDestroyedTM, creditsTM, endScreenTM, levelCompleteTM, youDiedTM, shieldTM, tut1TM, tut2TM, tut3TM, tut4TM, tut5TM;   // game texture
    VECTOR2 collisionVector;    // collision vector
	Ship enemyShips[7];
	Tank enemyTanks[7];
	Bullet avatarBullets[3];
	Bullet shipBullets[10];
	Bullet tankBullets[10];
	//Bungee bungee1, bungee2, bungee3;
	Bungee bungees[3];
	Image Level_1_Background1, Level_1_Background2, Level_1_Midground1, Level_1_Midground2, Level_2_Background1, Level_2_Background2,
		Level_2_Midground1, Level_2_Midground2, Level_3_Background1, Level_3_Background2, Level_3_Midground1, Level_3_Midground2, menuScreen,
		baseDestroyed, credits, endScreen, levelComplete, youDied, tut1, tut2, tut3, tut4, tut5;
	
	Image marker, timeBar, bar;
	Image explosion[10];
	Avatar avatar;
	Enemy* enemies[14];
	Shield shield;

	int score;
	int totalScore;
	//bool collision;
	int numMarked;
	Enemy* currentlyHit1;
	Enemy* currentlyHit2;
	int groundLocX;
	bool depressedLastFrame;
	bool enterDepressedLastFrame;
	int tempRand;
	int tankSpawnTime, shipSpawnTime;
	int baseHealth;
	int level;
	int endLevelTime;
	float startLevelTime;
	float timeLeftOnLevel;
	bool invincibility;
	int crashedTime;
	bool showHighScores;

	TextDX font;
	TextDX invincible;
	TextDX scoreText;
	TextDX* scoreIndicator;
	
	std::vector<HighScoreEntry> highScores;


	// State 
	GameStates gameStates;
	float timeInState;
	void gameStateUpdate();
	bool gameStart;
	bool exitReadyToPlay;

public:
    // Constructor
    CollisionTypes();

    // Destructor
    virtual ~CollisionTypes();

    // Initialize the game
    void initialize(HWND hwnd);
    void update();      // must override pure virtual from Game
    void ai();          // "
    void collisions();  // "
    void render();      // "
    void releaseAll();
    void resetAll();

	void spawnEnemyShip();
	void spawnEnemyTank();
	void updateShield();
	void waves();

	void resetEnemy(Enemy*);

	void tanksShoot();
	void shipsShoot();
	void createBungee();
	void avatarShoot();
	void shipToGround();
	void initializeLevel();
	void moveBackground();
	void resetEverything();

	void getScores();
	void outputScores(std::string);
	

	int enemyBulletSpeed;
	int avatarBulletSpeed;
	int numTanks;
	int numShips;
	int numShipBullets;
	int numTankBullets;
	int numAvatarBullets;
	int tankSpeed;
	int shipSpeed;
	int tankSpawnRate;
	int shipSpawnRate;

	TutorialScreen tutScreen;
};

#endif
