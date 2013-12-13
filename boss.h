#ifndef _BOSS_H                 // Prevent multiple definitions if this 
#define _BOSS_H                 // file is included in more than one place
#define WIN32_LEAN_AND_MEAN

#include "enemy.h"
#include "constants.h"


namespace bossNS
{
    const int WIDTH = 160;                   // image width
    const int HEIGHT = 160;                  // image height
    const int X = GAME_WIDTH - ( WIDTH + GAME_WIDTH/12 );   // location on screen
    const int Y = GAME_HEIGHT/2 - HEIGHT/2;
    const float SPEED = 120;      
	const int COLS = 3;
	const int START_FRAME = 0;
	const int END_FRAME = 0;
	const int FLY_START = 0;
	const int FLY_END = 2;
	const int SCALE = 1;
	enum MOVE_STATE {LEFT, RIGHT, UP, DOWN, TRACK};
}

class Boss : public Enemy
{
private:
	int level;
	bool dead;
	bool target;
	bool locked;
	int healthRemaining;
	bossNS::MOVE_STATE state;


public:
    // constructor
    Boss();

    // inherited member functions
    virtual bool initialize(Game *gamePtr, int width, int height, int ncols,
                            TextureManager *textureM);
    void update(float frameTime, int trackX, int trackY, D3DXVECTOR2 avatarCenter);

    // Set collision Boolean
        // Set collision type (NONE, CIRCLE, BOX, ROTATED_BOX)
    virtual void setCollisionType(entityNS::COLLISION_TYPE ctype)
    {collisionType = ctype;}

    // Set RECT structure used for BOX and ROTATED_BOX collision detection.
    void setEdge(RECT e) {edge = e;}

    // Get collision type
    entityNS::COLLISION_TYPE getCollisionType() {return collisionType;}

	void setCurrentLevel(int l) { level = l; }
	void setDead(bool dead) { Boss::dead = dead; }
	bool isDead() { return dead; }
	void setTarget(bool t) {target = t;}
	//void ai(float time, Entity &t) { targetEntity = t; }
	void setInitialState(bossNS::MOVE_STATE s) { state = s; }
	int getLevel() { return level; }
	bool isLocked() { return locked; }
	void setLocked(bool l) { locked = l; }
	void vectorTrack();

	int getHealth() { return healthRemaining; }
	void setHealth(int l) { healthRemaining = l; }
};
#endif

