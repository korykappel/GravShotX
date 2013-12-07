#include "bullet.h"

//=============================================================================
// default constructor
//=============================================================================
Bullet::Bullet() : Entity()
{
    spriteData.width = bulletNS::WIDTH;           // size of Ship1
    spriteData.height = bulletNS::HEIGHT;
    spriteData.x = bulletNS::X;                   // location on screen
    spriteData.y = bulletNS::Y;
    spriteData.rect.bottom = bulletNS::HEIGHT/2;    // rectangle to select parts of an image
    spriteData.rect.right = bulletNS::WIDTH;
	spriteData.scaleX = 1;
	spriteData.scaleY = 1;
    velocity.x = 0;                             // velocity X
    velocity.y = 0;                             // velocity Y
    startFrame = 0;              // first frame of ship animation
    endFrame     = 0;              // last frame of ship animation
    currentFrame = startFrame;
    collisionType =entityNS::BOX;
	edge.bottom = -bulletNS::HEIGHT/2;
	edge.top = bulletNS::HEIGHT/2;
	edge.right = -bulletNS::WIDTH/2;
	edge.left = bulletNS::WIDTH/2;

	groundLoc = 0;
}

//=============================================================================
// Initialize the Ship.
// Post: returns true if successful, false if failed
//=============================================================================
bool Bullet::initialize(Game *gamePtr, int width, int height, int ncols,
    TextureManager *textureM)
{
    return(Entity::initialize(gamePtr, width, height, ncols, textureM));
}

//=============================================================================
// update
// typically called once per frame
// frameTime is used to regulate the speed of movement and animation
//=============================================================================
void Bullet::update(float frameTime)
{
    Entity::update(frameTime);


	//incPositionX(velocity.x * frameTime);
	//incPositionY(velocity.y * frameTime);

	spriteData.x += velocity.x * frameTime;
	spriteData.y += velocity.y * frameTime;


	// Right boundary
	if(spriteData.width * spriteData.scale + spriteData.x >= GAME_WIDTH || spriteData.x < 0)
	{
		visible = false;
		active = false;
		velocity.x = 0;
		velocity.y = 0;
	}
	//bottom boundary
	if (spriteData.height * spriteData.scale + spriteData.y >= GAME_HEIGHT - 5) {
		visible = false;
		active = false;	
		velocity.x = 0;
		velocity.y = 0;
		groundLoc = spriteData.x;
		spriteData.x = 0;
	}
	//top boundary
	if (spriteData.y < 0) {
		visible = false;
		active = false;
	}

	//setScreenCoordX();
	//setScreenCoordY();

	Entity::setX(spriteData.x);
	Entity::setY(spriteData.y);

	//velocity = D3DXVECTOR2(0,0);

	//velocity.x = enemyNS::SPEED;
}