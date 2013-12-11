#ifndef _SHIELD_H                 // Prevent multiple definitions if this 
#define _SHIELD_H                 // file is included in more than one place
#define WIN32_LEAN_AND_MEAN

#include "constants.h"
#include "entity.h"

namespace shieldNS
{
    const int WIDTH = 120;                   // image width
    const int HEIGHT = 120;                  // image height
    const int X = GAME_WIDTH/2 - WIDTH/2;   // location on screen
    const int Y = GAME_HEIGHT/2 - HEIGHT/2;
    const float SPEED = 120;      
	const int COLS = 3;
	const int START_FRAME = 0;
	const int END_FRAME = 2;
	const int SCALE = 1;
}

// inherits from Entity class
class Shield : public Entity
{
private:
	bool attached;
	int health;

public:
    // constructor
   Shield();

    // inherited member functions
    virtual bool initialize(Game *gamePtr, int width, int height, int ncols,
                            TextureManager *textureM);
    void update(float frameTime);

    // Set collision Boolean
        // Set collision type (NONE, CIRCLE, BOX, ROTATED_BOX)
    virtual void setCollisionType(entityNS::COLLISION_TYPE ctype)
    {collisionType = ctype;}

    // Set RECT structure used for BOX and ROTATED_BOX collision detection.
    void setEdge(RECT e) {edge = e;}

    // Get collision type
    entityNS::COLLISION_TYPE getCollisionType() {return collisionType;}

	void setAttached(bool m) {attached = m;}
	bool getAttached() {return attached;}

	void setHealth(int m) {health = m;}
	int getHealth() {return health;}
};
#endif

