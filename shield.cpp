#include "shield.h"

//=============================================================================
// default constructor
//=============================================================================
Shield::Shield() : Entity()
{
    spriteData.width = shieldNS::WIDTH;           // size of Ship1
    spriteData.height = shieldNS::HEIGHT;
    spriteData.x = shieldNS::X;                   // location on screen
    spriteData.y = shieldNS::Y;
    spriteData.rect.bottom = shieldNS::HEIGHT/2;    // rectangle to select parts of an image
    spriteData.rect.right = shieldNS::WIDTH;
	spriteData.scaleX = shieldNS::SCALE;
	spriteData.scaleY = shieldNS::SCALE;
	velocity.x = -shieldNS::SPEED;                             // velocity X
    velocity.y = 0;                             // velocity Y
    //startFrame = 0;              // first frame of ship animation
    //endFrame     = 0;              // last frame of ship animation
    //currentFrame = startFrame;
    collisionType =entityNS::BOX;
	edge.bottom = -shieldNS::HEIGHT/2;
	edge.top = shieldNS::HEIGHT/2;
	edge.right = -shieldNS::WIDTH/2;
	edge.left = shieldNS::WIDTH/2;

	attached = false;
	health = 0;
}

//=============================================================================
// Initialize the Ship.
// Post: returns true if successful, false if failed
//=============================================================================
bool Shield::initialize(Game *gamePtr, int width, int height, int ncols,
    TextureManager *textureM)
{
    return(Entity::initialize(gamePtr, width, height, ncols, textureM));
}

//=============================================================================
// update
// typically called once per frame
// frameTime is used to regulate the speed of movement and animation
//=============================================================================
void Shield::update(float frameTime)
{

    //spriteData.x += velocity.x * frameTime;
    //velocity.x = 0;
    //spriteData.y += velocity.y * frameTime;
    //velocity.y = 0;

    Entity::update(frameTime);

	if(!attached) //if it's attached, we just want to draw it where the avatar is
	{
		//when go off the left side of screen
		if(visible && getPositionX() + getWidth() * getScale() <= 0)
		{
			setPositionX(0);
			setVelocity(VECTOR2(0,0));
			visible = false;
		}
	
		// Update position
		incPositionX(velocity.x * frameTime);
		incPositionY(velocity.y * frameTime);

		// Convert World Coord to Screen Coord
		setScreenCoordX();
		setScreenCoordY();
	}

	if(health==2)
		this->setColorFilter(graphicsNS::BLACK);
	//MIGHT HAVE TO USE ANIMATIONS



    //// wrap around screen
    //if (spriteData.x > GAME_WIDTH)                  // if off screen right
    //    spriteData.x = -shipNS::WIDTH;              // position off screen left
    //else if (spriteData.x < -shipNS::WIDTH)         // else if off screen left
    //    spriteData.x = GAME_WIDTH;                  // position off screen right
    //if (spriteData.y < -shipNS::HEIGHT)             // if off screen top
    //    spriteData.y = GAME_HEIGHT;                 // position off screen bottom
    //else if (spriteData.y > GAME_HEIGHT)            // else if off screen bottom
    //    spriteData.y = -shipNS::HEIGHT;             // position off screen top
}

