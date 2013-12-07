#ifndef _TANK_H                 // Prevent multiple definitions if this 
#define _TANK_H                 // file is included in more than one place
#define WIN32_LEAN_AND_MEAN

#include "enemy.h"
#include "constants.h"

namespace tankNS
{
    const int WIDTH = 64;                   // image width
    const int HEIGHT = 28;                  // image height
    const int X = GAME_WIDTH/2 - WIDTH/2;   // location on screen
    const int Y = GAME_HEIGHT/2 - HEIGHT/2;
    const float SPEED = 80;      
	const int SCALE = 1;
}

// inherits from Entity class
class Tank : public Enemy
{
private:

	//bool marked;

public:
    // constructor
	Tank();

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

	/*void setMarked(bool m) {marked = m;}
	bool getMarked() {return marked;}*/
};
#endif
