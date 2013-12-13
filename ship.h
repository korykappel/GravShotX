// Programming 2D Games
// Copyright (c) 2012 by: 
// Charles Kelly
// Collision Types ship.h v1.0

#ifndef _SHIP_H                 // Prevent multiple definitions if this 
#define _SHIP_H                 // file is included in more than one place
#define WIN32_LEAN_AND_MEAN

#include "enemy.h"
#include "constants.h"

namespace shipNS
{
    const int WIDTH = 64;                   // image width
    const int HEIGHT = 64;                  // image height
    const int X = GAME_WIDTH/2 - WIDTH/2;   // location on screen
    const int Y = GAME_HEIGHT/2 - HEIGHT/2;
    const float SPEED = 120;      
	const int COLS = 3;
	const int START_FRAME = 0;
	const int END_FRAME = 0;
	const int FLY_START = 0;
	const int FLY_END = 2;
	const int SCALE = 1;
}

// inherits from Entity class
class Ship : public Enemy
{
private:
	bool hitGround;
	//bool marked;

public:
    // constructor
    Ship();

    // inherited member functions
    virtual bool initialize(Game *gamePtr, int width, int height, int ncols,
                            TextureManager *textureM, TextDX* font);
    void update(float frameTime);

    // Set collision Boolean
        // Set collision type (NONE, CIRCLE, BOX, ROTATED_BOX)
    virtual void setCollisionType(entityNS::COLLISION_TYPE ctype)
    {collisionType = ctype;}

    // Set RECT structure used for BOX and ROTATED_BOX collision detection.
    void setEdge(RECT e) {edge = e;}

    // Get collision type
    entityNS::COLLISION_TYPE getCollisionType() {return collisionType;}

	void setHitGround(bool m) {hitGround = m;}
	bool getHitGround() {return hitGround;}
};
#endif

