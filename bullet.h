#define WIN32_LEAN_AND_MEAN
#ifndef _BULLET_H                 // Prevent multiple definitions if this 
#define _BULLET_H   
//class Bullet;

#include "entity.h"
#include "constants.h"

namespace bulletNS
{
    const int WIDTH = 16;                   // image width
    const int HEIGHT = 16;                  // image height
    const int X = 0;				 // location on screen
    const int Y = 0;
    const float SPEED = 300;      
}

// inherits from Entity class
class Bullet : public Entity
{
private:

	int groundLoc;

public:
    // constructor
    Bullet();

    // inherited member functions
    virtual bool initialize(Game *gamePtr, int width, int height, int ncols,
                            TextureManager *textureM);
    void update(float frameTime);

	//// Set collision Boolean
 //   void setCollision(bool c)
 //   {collision = c;}

    // Set collision type (NONE, CIRCLE, BOX, ROTATED_BOX)
    virtual void setCollisionType(entityNS::COLLISION_TYPE ctype)
    {collisionType = ctype;}

    // Set RECT structure used for BOX and ROTATED_BOX collision detection.
    void setEdge(RECT e) {edge = e;}

    // Get collision type
    entityNS::COLLISION_TYPE getCollisionType() {return collisionType;}

	int getGroundLoc() {return groundLoc;}
	void setGroundLoc(int x) {groundLoc = x;}

};
#endif

