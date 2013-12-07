
#include "tank.h"

//=============================================================================
// default constructor
//=============================================================================
Tank::Tank() : Enemy()
{
    spriteData.width = tankNS::WIDTH;           // size of tank1
    spriteData.height = tankNS::HEIGHT;
    spriteData.x = tankNS::X;                   // location on screen
    spriteData.y = tankNS::Y;
    spriteData.rect.bottom = tankNS::HEIGHT/2;    // rectangle to select parts of an image
    spriteData.rect.right = tankNS::WIDTH;
	spriteData.scaleX = 1;
	spriteData.scaleY = 1;
    velocity.x = 0;                             // velocity X
    velocity.y = 0;                             // velocity Y
    startFrame = 0;              // first frame of tank animation
    endFrame     = 0;              // last frame of tank animation
    currentFrame = startFrame;
    collisionType =entityNS::BOX;
	edge.bottom = -tankNS::HEIGHT/2;
	edge.top = tankNS::HEIGHT/2;
	edge.right = -tankNS::WIDTH/2;
	edge.left = tankNS::WIDTH/2;

	//marked = false;
}

//=============================================================================
// Initialize the Tank.
// Post: returns true if successful, false if failed
//=============================================================================
bool Tank::initialize(Game *gamePtr, int width, int height, int ncols,
    TextureManager *textureM)
{
    return(Entity::initialize(gamePtr, width, height, ncols, textureM));
}

//=============================================================================
// update
// typically called once per frame
// frameTime is used to regulate the speed of movement and animation
//=============================================================================
void Tank::update(float frameTime)
{

    //spriteData.x += velocity.x * frameTime;
    //velocity.x = 0;
    //spriteData.y += velocity.y * frameTime;
    //velocity.y = 0;

   Enemy::update(frameTime);

    //// wrap around screen
    //if (spriteData.x > GAME_WIDTH)                  // if off screen right
    //    spriteData.x = -tankNS::WIDTH;              // position off screen left
    //else if (spriteData.x < -tankNS::WIDTH)         // else if off screen left
    //    spriteData.x = GAME_WIDTH;                  // position off screen right
    //if (spriteData.y < -tankNS::HEIGHT)             // if off screen top
    //    spriteData.y = GAME_HEIGHT;                 // position off screen bottom
    //else if (spriteData.y > GAME_HEIGHT)            // else if off screen bottom
    //    spriteData.y = -tankNS::HEIGHT;             // position off screen top
}