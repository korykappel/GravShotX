
              // file is included in more than one place
#define WIN32_LEAN_AND_MEAN
#ifndef MENU_H                 // Prevent multiple definitions if this 
#define MENU_H 

class Menu;

#include "graphics.h"
#include "constants.h"
#include "textDX.h"
#include <string>
#include <vector>
#include <sstream>
#include "input.h"

namespace menuNS
{
	const std::string MENU_HEADING = "Test Menu";
	const COLOR_ARGB HIGHTLIGHT_COLOR = graphicsNS::RED;
	const COLOR_ARGB NORMAL_COLOR = graphicsNS::WHITE;
	const D3DXVECTOR2 MENU_ANCHOR = D3DXVECTOR2(90, GAME_HEIGHT / 2 - 90);
	const int VERTICAL_OFFSET = 50;
	const int HEADING_FONT_SIZE = 50;
	const int ITEM_FONT_SIZE = 30;
	const int HIGHLIGHT_FONT_SIZE = 30;
}

// inherits from Entity class
class Menu 
{
private:
   TextDX *menuItemFont;
   TextDX *menuItemFontHighlight;
   TextDX *menuHeadingFont;

   Input   *input;         // pointer to the input system
   Graphics *graphics;

   std::string selectedItem;
   std::vector<std::string> menuItems;
   std::string menuHeading;

   D3DXVECTOR2 menuAnchor;
   int verticalOffset;
   int linePtr;
   COLOR_ARGB highlightColor ;
   COLOR_ARGB normalColor;
   bool visible;
   bool active;
   bool upDepressedLastFrame;
   bool downDepressedLastFrame;
   bool returnDepressedLastFrame;

public:
    // constructor
    Menu();
	void initialize(Graphics *g, Input *i);
	void update();
	std::string getSelectedItem() {return selectedItem;}
	void displayMenu();

	// Set Functions
	void setMenuHeader(std::string menuName)		{menuHeading = menuName;}
	void setMenuItem(std::string itemName)			{menuItems.push_back(itemName);}
	void setVisible(bool b)							{visible = b;}
	void setActive(bool b)							{active = b;}

	// Get Functions
	std::string getMenuHeader()				{return menuHeading;}		
	std::string getMenuItem(int number)		{return menuItems[number];}
	bool getVisible()						{return visible;}
	bool getActive()						{return active;}

};
#endif

