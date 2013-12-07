#include "enemy.h"

//=============================================================================
// default constructor
//=============================================================================
Enemy::Enemy() : Entity()
{
 //   spriteData.width = enemyNS::WIDTH;           // size of Ship1
 //   spriteData.height = enemyNS::HEIGHT;
 //   spriteData.x = enemyNS::X;                   // location on screen
 //   spriteData.y = enemyNS::Y;
 //   spriteData.rect.bottom = enemyNS::HEIGHT/2;    // rectangle to select parts of an image
 //   spriteData.rect.right = enemyNS::WIDTH;
	//spriteData.scaleX = 1;
	//spriteData.scaleY = 1;
 //   velocity.x = 0;                             // velocity X
 //   velocity.y = 0;                             // velocity Y
 //   startFrame = 0;              // first frame of ship animation
 //   endFrame     = 0;              // last frame of ship animation
 //   currentFrame = startFrame;
 //   collisionType =entityNS::BOX;
	//edge.bottom = -enemyNS::HEIGHT/2;
	//edge.top = enemyNS::HEIGHT/2;
	//edge.right = -enemyNS::WIDTH/2;
	//edge.left = enemyNS::WIDTH/2;

	marked = false;
	bungeed = false;
	needsReset = false;
	//attachedTo = NULL;
}

//=============================================================================
// Initialize the Ship.
// Post: returns true if successful, false if failed
//=============================================================================
bool Enemy::initialize(Game *gamePtr, int width, int height, int ncols,
    TextureManager *textureM)
{
    return(Entity::initialize(gamePtr, width, height, ncols, textureM));
}

//=============================================================================
// update
// typically called once per frame
// frameTime is used to regulate the speed of movement and animation
//=============================================================================
void Enemy::update(float frameTime)
{
    Entity::update(frameTime);


	//when go off the left side of screen
	if(visible && getPositionX() + getWidth() * getScale() < 0)
	{
		setPositionX(0);
		setVelocity(VECTOR2(0,0));
		if(!bungeed)
		{
			visible = false;

			//if(marked)
			//{
				needsReset = true;
				//attachedTo->clear();
			//}
		}
	}
	
	// Update enemy position
	incPositionX(velocity.x * frameTime);
	incPositionY(velocity.y * frameTime);

	// Convert World Coord to Screen Coord
	setScreenCoordX();
	setScreenCoordY();


	//velocity = D3DXVECTOR2(0,0);

	//velocity.x = enemyNS::SPEED;
}