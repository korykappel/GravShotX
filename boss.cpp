#include "boss.h"

//=============================================================================
// default constructor
//=============================================================================
Boss::Boss() : Enemy()
{
    spriteData.width = bossNS::WIDTH;           // size of Ship1
    spriteData.height = bossNS::HEIGHT;
    spriteData.x = bossNS::X;                   // location on screen
    spriteData.y = bossNS::Y;
    spriteData.rect.bottom = bossNS::HEIGHT/2;    // rectangle to select parts of an image
    spriteData.rect.right = bossNS::WIDTH;
	spriteData.scaleX = 1;
	spriteData.scaleY = 1;
    velocity.x = 0;                             // velocity X
    velocity.y = 0;                             // velocity Y
    startFrame = 0;              // first frame of ship animation
    endFrame     = 0;              // last frame of ship animation
    currentFrame = startFrame;
    collisionType =entityNS::BOX;
	edge.bottom = -bossNS::HEIGHT/2;
	edge.top = bossNS::HEIGHT/2;
	edge.right = -bossNS::WIDTH/2;
	edge.left = bossNS::WIDTH/2;

	healthRemaining = 100;
	level = 1;
	locked = false;
	//state = bossNS::LEFT;
}

//=============================================================================
// Initialize the Ship.
// Post: returns true if successful, false if failed
//=============================================================================
bool Boss::initialize(Game *gamePtr, int width, int height, int ncols,
    TextureManager *textureM)
{
    return(Entity::initialize(gamePtr, width, height, ncols, textureM));
}

//=============================================================================
// update
// typically called once per frame
// frameTime is used to regulate the speed of movement and animation
//=============================================================================
void Boss::update(float frameTime, int trackX, int trackY, D3DXVECTOR2 avatarCenter)
{

    Entity::update(frameTime);

	if(visible && active) {
		if (level == 1) {
			//state = bossNS::LEFT;
			if (state == bossNS::LEFT) {
				if (spriteData.x > 300) {
					velocity.x = -100;
					spriteData.x += velocity.x * frameTime;
					velocity.x = 0;
				} else {
					state = bossNS::RIGHT;
				}
			}
			if (state == bossNS::RIGHT) {
				if (spriteData.x < (bossNS::X)) {
					velocity.x = 100;
					spriteData.x += velocity.x * frameTime;
					velocity.x = 0;
				} else {
					state = bossNS::LEFT;
				}
			}
		} else if (level == 2) {
			if (state == bossNS::LEFT) {
				if (spriteData.x > 300) {
					velocity.x = -150;
					spriteData.x += velocity.x * frameTime;
					velocity.x = 0;
				} else {
					int upOrDown = rand()%2;
					if (upOrDown == 0) {
						state = bossNS::UP;
					} else {
						state = bossNS::DOWN;
					}
				}
			}
			if (state == bossNS::UP) {
				if (spriteData.y > 100) {
					velocity.y = -150;
					spriteData.y += velocity.y * frameTime;
					velocity.y = 0;
				} else {
					state = bossNS::RIGHT;
				}
			}
			else if (state == bossNS::DOWN) {
				if (spriteData.y < 500) {
					velocity.y = 150;
					spriteData.y += velocity.y * frameTime;
					velocity.y = 0;
				} else {
					state = bossNS::RIGHT;
				}
			}
			if (state == bossNS::RIGHT) {
				if (spriteData.x + spriteData.width/2 < (bossNS::X)) {
					double deltaX = (getX() + bossNS::WIDTH/2) - bossNS::X;
					double deltaY = (getY() - bossNS::Y);
					VECTOR2 v1(deltaX, deltaY);
					D3DXVec2Normalize(&v1, &v1);
					setVelocity(v1 * -350);
					spriteData.y += velocity.y * frameTime;
					spriteData.x += velocity.x * frameTime;
					Entity::setX(spriteData.x);
					Entity::setY(spriteData.y);
					velocity.x = 0;
					velocity.y = 0;
				} else {
					state = bossNS::LEFT;
				}
			}
		} else if (level == 3) {
			if (state == bossNS::TRACK) {
				if (spriteData.x > 300) {
					VECTOR2 vel = getCenterPoint() - avatarCenter;
					VECTOR2* foo = D3DXVec2Normalize(&vel, &vel);
					setVelocity(-vel*150);
					//*foo = velocity*frameTime*150;
					spriteData.x += velocity.x * frameTime;
					spriteData.y += velocity.y * frameTime;
					setX(spriteData.x);
					setY(spriteData.y);
				} else {
					state = bossNS::RIGHT;
				}
			}
			if (state == bossNS::RIGHT) {
				if (spriteData.x + spriteData.width/2 < (bossNS::X)) {
					double deltaX = (getX() + bossNS::WIDTH/2) - bossNS::X;
					double deltaY = (getY() - bossNS::Y);
					VECTOR2 v1(deltaX, deltaY);
					D3DXVec2Normalize(&v1, &v1);
					setVelocity(v1 * -350);
					spriteData.y += velocity.y * frameTime;
					spriteData.x += velocity.x * frameTime;
					Entity::setX(spriteData.x);
					Entity::setY(spriteData.y);
					velocity.x = 0;
					velocity.y = 0;
				} else {
					state = bossNS::TRACK;
				}
			}
		}
	}



    //// wrap around screen
    //if (spriteData.x > GAME_WIDTH)                  // if off screen right
    //    spriteData.x = -bossNS::WIDTH;              // position off screen left
    //else if (spriteData.x < -bossNS::WIDTH)         // else if off screen left
    //    spriteData.x = GAME_WIDTH;                  // position off screen right
    //if (spriteData.y < -bossNS::HEIGHT)             // if off screen top
    //    spriteData.y = GAME_HEIGHT;                 // position off screen bottom
    //else if (spriteData.y > GAME_HEIGHT)            // else if off screen bottom
    //    spriteData.y = -bossNS::HEIGHT;             // position off screen top
}

//void Boss::vectorTrack()
//{
//	VECTOR2 vel = getCenterPoint() - targetEntity.getCenterPoint() ;
//	VECTOR2* foo = D3DXVec2Normalize(&vel, &vel);
//	setVelocity(-vel);
//}
