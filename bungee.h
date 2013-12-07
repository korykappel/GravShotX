#define WIN32_LEAN_AND_MEAN
#ifndef _BUNGEE_H                 // Prevent multiple definitions if this 
#define _BUNGEE_H   
//class Bungee;

#include "entity.h"
#include "enemy.h"
#include "constants.h"

namespace bungeeNS
{
    const int WIDTH = 1;                   // image width
    const int HEIGHT = 3;                  // image height
    const int X = 0;		 // location on screen
    const int Y = 0; 
	const float SMASH_SPEED = 8.0;
}

// inherits from Entity class
class Bungee : public Entity
{
private:
  
   Enemy* pointer1;
   Enemy* pointer2;
   float groundLocX, enemy1LocX, enemy1LocY, enemy2LocX, enemy2LocY;
   BungeeStates bungeeState;
   float deltaY, deltaX, angleBetween;
   float distance;

public:
    // constructor
    Bungee();

    // inherited member functions
    virtual bool initialize(Game *gamePtr, int width, int height, int ncols,
                            TextureManager *textureM);
    void update(float frameTime);

    // Set collision type (NONE, CIRCLE, BOX, ROTATED_BOX)
    virtual void setCollisionType(entityNS::COLLISION_TYPE ctype)
    {collisionType = ctype;}

    // Set RECT structure used for BOX and ROTATED_BOX collision detection.
    void setEdge(RECT e) {edge = e;}

    // Get collision type
    entityNS::COLLISION_TYPE getCollisionType() {return collisionType;}


	void setBungeeState(BungeeStates b) {bungeeState = b;}  //MIGHT NOT NEED
	void setPointer1(Enemy* p) {pointer1 = p;}
	void setPointer2(Enemy* p) {pointer2 = p;}
	void setGroundLoc(int x) {groundLocX = x;}
	int getGroundLoc() {return groundLocX;}
	void smashEnemies();
	void smashGround();
	void clear();

	Enemy* getPointer1() {return pointer1;}
	BungeeStates getBungeeState() {return bungeeState;}

};
#endif
