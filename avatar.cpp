#include "avatar.h"

//=============================================================================
// default constructor
//=============================================================================
Avatar::Avatar() : Entity()
{
    spriteData.width = avatarNS::WIDTH;           
    spriteData.height = avatarNS::HEIGHT;
    spriteData.x = avatarNS::X;                   
    spriteData.y = avatarNS::Y;
    spriteData.rect.bottom = avatarNS::HEIGHT/2;    
    spriteData.rect.right = avatarNS::WIDTH;
	spriteData.scale = 1;
    velocity.x = 0;                             
    velocity.y = 0;                             
    startFrame = 0;              
    endFrame     = 0;              
    currentFrame = startFrame;
    collisionType = entityNS::BOX;
	edge.bottom = -avatarNS::HEIGHT/2;
	edge.top = avatarNS::HEIGHT/2;
	edge.right = -avatarNS::WIDTH/2;
	edge.left = avatarNS::WIDTH/2;

	dead = false;
	lastXDir = "none";
	lastYDir = "none"; 
}

//=============================================================================
// Initialize the avatar.
// Post: returns true if successful, false if failed
//=============================================================================
bool Avatar::initialize(Game *gamePtr, int width, int height, int ncols,
    TextureManager *textureM)
{
    return(Entity::initialize(gamePtr, width, height, ncols, textureM));
}

//=============================================================================
// update
// typically called once per frame
// frameTime is used to regulate the speed of movement and animation
//=============================================================================
void Avatar::update(float frameTime)
{
    Entity::update(frameTime);

    // Position Update
	incPositionX(frameTime * velocity.x);				// move avatar along X
	incPositionY(frameTime * velocity.y);				// move avatar along Y


	///////////////////////
	// Boundary Conditions
	///////////////////////

	// Right boundary
	if(getPositionX() + getWidth() * getScale() > GAME_WIDTH)
		setPositionX(GAME_WIDTH - getWidth() * getScale());
	// Left boundary
	if(getPositionX() < 0)
		setPositionX(0);
	// Top screen boundary
	if(getPositionY() < 0)
		setPositionY(0);
	// Bottom screen boundary
	if(getPositionY() + getHeight() * getScale() > GAME_HEIGHT)
		setPositionY(GAME_HEIGHT - getHeight() * getScale());
	
	// Convert from World Coordinates to Screen Coordinates
	setScreenCoordX();
	setScreenCoordY();

	
	//velocity.x = 0;
	//velocity.y = 0;
	
}