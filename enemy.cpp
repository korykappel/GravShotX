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
	fontDisplayFrameCount = 0;
	scoreToDisplay = 0;

}

//=============================================================================
// Initialize the Ship.
// Post: returns true if successful, false if failed
//=============================================================================
bool Enemy::initialize(Game *gamePtr, int width, int height, int ncols,
    TextureManager *textureM, TextDX* font)
{
	scoreIndicator = font;
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
			active = false;

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

void Enemy::displayScore()
{
	if (scoreToDisplay > 0)
	{

		if (++fontDisplayFrameCount < 85)
		{
			char buffer[5];
			sprintf(buffer,"+%i",scoreToDisplay);
			//for(int i=0; i<4; i++)
			//	if(scoreIndicators[i].set
			scoreIndicator->setFontColor(SETCOLOR_ARGB(255 - 3*fontDisplayFrameCount,255,0,0));
			//move to render
			scoreIndicator->print(buffer, x+(spriteData.width/2), y -25 - .2*fontDisplayFrameCount);	
		}
		else{
			fontDisplayFrameCount = 0;
			scoreToDisplay = 0;
		}
	}
}
