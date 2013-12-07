#define WIN32_LEAN_AND_MEAN
#ifndef _ENEMY_H                 // Prevent multiple definitions if this 
#define _ENEMY_H   
//class Enemy;

#include "entity.h"
#include "constants.h"
#include "textDX.h"
//#include "bungee.h"

namespace enemyNS
{
 //   const int WIDTH = 64;                   // image width
 //   const int HEIGHT = 64;                  // image height
 //   const int X = GAME_WIDTH/2 - WIDTH/2;   // location on screen
 //   const int Y = GAME_HEIGHT/2 - HEIGHT/2;
 //   const float SPEED = 120;      
	//const int COLS = 3;
	//const int START_FRAME = 0;
	//const int END_FRAME = 0;
	//const int FLY_START = 0;
	//const int FLY_END = 2;
	//const int SCALE = 1;
}

// inherits from Entity class
class Enemy : public Entity
{
private:
      
	bool marked;
	bool needsReset;
	bool bungeed;

	//score indicator stuff
	int scoreToDisplay;
	int fontDisplayFrameCount;
	TextDX* scoreIndicator;
	int x, y;

	Type type;
	
	//Bungee* attachedTo;

public:
    // constructor
    Enemy();

	bool initialize(Game *gamePtr, int width, int height, int ncols, TextureManager *textureM, TextDX* font)
	{scoreIndicator = font; return Entity::initialize(gamePtr, width, height, ncols, textureM);}


    // inherited member functions
    virtual bool initialize(Game *gamePtr, int width, int height, int ncols,
                            TextureManager *textureM);
    void update(float frameTime);

	void setNeedsReset(bool r) {needsReset = r;}
	bool getNeedsReset() {return needsReset;}

	void setMarked(bool m) {marked = m;}
	bool getMarked() {return marked;}

	void setBungeed(bool m) {bungeed = m;}
	bool getBungeed() {return bungeed;}

	/*void setAttachedTo(Bungee* b) {attachedTo = b;}
	Bungee* getAttachedTo() {return attachedTo;}*/

	void setType(Type t) {type = t;}
	Type getType() {return type;}

	void addScore(int score, int posx, int posy) {x=posx; y=posy; scoreToDisplay = score; fontDisplayFrameCount = 0;}
	void displayScore();
};
#endif

