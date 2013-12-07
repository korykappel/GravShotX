#include "bungee.h"

//=============================================================================
// default constructor
//=============================================================================
Bungee::Bungee() : Entity()
{
    spriteData.width = bungeeNS::WIDTH;           // size of Ship1
    spriteData.height = bungeeNS::HEIGHT;
    spriteData.x = bungeeNS::X;                   // location on screen
    spriteData.y = bungeeNS::Y;
    spriteData.rect.bottom = bungeeNS::HEIGHT/2;    // rectangle to select parts of an image
    spriteData.rect.right = bungeeNS::WIDTH;
	spriteData.scaleX = 1;
	spriteData.scaleY = 1;
    collisionType =entityNS::BOX;
	edge.bottom = -bungeeNS::HEIGHT/2;
	edge.top = bungeeNS::HEIGHT/2;
	edge.right = -bungeeNS::WIDTH/2;
	edge.left = bungeeNS::WIDTH/2;

	pointer1 = NULL;
	pointer2 = NULL;
	groundLocX, enemy1LocX, enemy1LocY, enemy2LocX, enemy2LocY = 0;
	bungeeState = none;
	deltaY, deltaX, angleBetween = 0;
	distance = 0;
}

//=============================================================================
// Initialize the Ship.
// Post: returns true if successful, false if failed
//=============================================================================
bool Bungee::initialize(Game *gamePtr, int width, int height, int ncols,
    TextureManager *textureM)
{
    return(Entity::initialize(gamePtr, width, height, ncols, textureM));
}

//=============================================================================
// update
// typically called once per frame
// frameTime is used to regulate the speed of movement and animation
//=============================================================================
void Bungee::update(float frameTime)
{
    Entity::update(frameTime);
	

	switch (bungeeState)
	{
	case none:
		break;
	case enemyToEnemy:
		smashEnemies();
		visible = true;
		break;
	case enemyToGround:
		smashGround();
		visible = true;
		break;
	}
	
	//put this before or after?
	if(pointer1 != NULL)
	{
		enemy1LocX = pointer1->getCenterX();
		enemy1LocY = pointer1->getCenterY();
	}
	if(pointer2 != NULL)
	{
		enemy2LocX = pointer2->getCenterX();
		enemy2LocY = pointer2->getCenterY();
	}
}

void Bungee::smashEnemies()
{
	deltaY = enemy2LocY - enemy1LocY;
	deltaX = enemy2LocX - enemy1LocX;
	angleBetween = atan2(deltaY, deltaX);
	spriteData.angle = angleBetween;
	distance = sqrt(deltaX*deltaX + deltaY*deltaY);
	spriteData.scaleX = distance;
	spriteData.x = enemy1LocX;
	spriteData.y = enemy1LocY;

	VECTOR2 v1(deltaX, deltaY);
	//graphics->Vector2Normalize(&v1);
	D3DXVec2Normalize(&v1, &v1);

	RECT temp = {-distance/2, -1, distance/2, 1}; //{-1, -1, 1, 1} ?
	setEdge(temp);

	pointer1->setVelocity(pointer1->getVelocity()+v1*bungeeNS::SMASH_SPEED);
	pointer2->setVelocity(pointer2->getVelocity()-v1*bungeeNS::SMASH_SPEED);
}

void Bungee::smashGround()
{
	deltaY = GAME_HEIGHT-10 - enemy1LocY;
	deltaX = groundLocX - enemy1LocX;
	angleBetween = atan2(deltaY, deltaX);
	spriteData.angle = angleBetween;
	spriteData.scaleX = sqrt(deltaX*deltaX + deltaY*deltaY);
	spriteData.x = enemy1LocX;
	spriteData.y = enemy1LocY;

	VECTOR2 v1(deltaX, deltaY);
	graphics->Vector2Normalize(&v1);

	pointer1->setVelocity(pointer1->getVelocity()+v1*bungeeNS::SMASH_SPEED);
	//pointer2->setVelocity(pointer2->getVelocity()-v1*bungeeNS::SMASH_SPEED);
}

void Bungee::clear()
{
	pointer1 = 0;
	pointer2 = 0;
	groundLocX, enemy1LocX, enemy1LocY, enemy2LocX, enemy2LocY = 0;
	bungeeState = none;
	visible = false;
}