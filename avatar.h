#define WIN32_LEAN_AND_MEAN
#ifndef _AVATAR_H                 // Prevent multiple definitions if this 
#define _AVATAR_H   
class Avatar;

#include "entity.h"
#include "constants.h"

namespace avatarNS
{
    const int WIDTH = 100;                   // image width
    const int HEIGHT = 32;                  // image height	
    const int X = 100;   // location on screen
    const int Y = GAME_HEIGHT/2;
    const float SPEED = 500;        
	const int COLS = 3;
	const int START_FRAME = 0;
	const int END_FRAME = 0;
	const int FLY_START = 0;
	const int FLY_END = 2;
	const int SCALE = 1;
	
}

// inherits from Entity class
class Avatar : public Entity
{
private:
  
	bool dead;

public:
    // constructor
    Avatar();

	std::string lastXDir, lastYDir; 

    // inherited member functions
    virtual bool initialize(Game *gamePtr, int width, int height, int ncols,
                            TextureManager *textureM);
    void update(float frameTime);

    // Set collision type (NONE, CIRCLE, BOX, ROTATED_BOX)
    virtual void setCollisionType(entityNS::COLLISION_TYPE ctype)
    {collisionType = ctype;}

    // Set RECT structure used for BOX and ROTATED_BOX collision detection.
    void setEdge(RECT e) {edge = e;}

	void setDead(bool b) {dead = b;}
	bool getDead() {return dead;}

    // Get collision type
    entityNS::COLLISION_TYPE getCollisionType() {return collisionType;}

	// Movement 
    void right()     
	{
        if (velocity.x >= avatarNS::SPEED) {
             velocity.x = avatarNS::SPEED;
        } else {
			velocity.x += 6;
        }
    }
    void stopRight() {
        if (velocity.x <= 0) {
             velocity.x = 0;
        } else { 
             velocity.x += -7;
        }
    }
	void left() {
        if (velocity.x <= -avatarNS::SPEED) {
             velocity.x = -avatarNS::SPEED;
        } else {
             velocity.x += -6;
        }
    }
    void stopLeft() {
        if (velocity.x >= 0) {
            velocity.x = 0;
        } else {
              velocity.x += 7;
        }
    }
    void up() {
        if (velocity.y <= -avatarNS::SPEED) {
              velocity.y = -avatarNS::SPEED;
        } else {
            velocity.y += -5;
        }
    } 
    void stopUp() {
        if (velocity.y >= 0) {
               velocity.y = 0;
        } else {
             velocity.y += 5;
        }
    }
    void down() {
        if (velocity.y >= avatarNS::SPEED) {
             velocity.y = avatarNS::SPEED;
        } else { 
             velocity.y += 5;
        }
    }
    void stopDown() {
        if (velocity.y <= 0) {
             velocity.y = 0;
        } else {
             velocity.y += -5;
        }
    }


};
#endif