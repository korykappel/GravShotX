
#include "menu.h"

Menu::Menu()
{
	selectedItem = -1;	//nothing return
	menuItemFont = new TextDX();
	menuHeadingFont = new TextDX();
}

void Menu::initialize(Graphics *g, Input *i)
{
	menuHeading = menuNS::MENU_HEADING;

	highlightColor = menuNS::HIGHTLIGHT_COLOR;
	normalColor = menuNS::NORMAL_COLOR;
	menuAnchor = menuNS::MENU_ANCHOR;
	input = i;
	verticalOffset = menuNS::VERTICAL_OFFSET;
	linePtr = 0;
	selectedItem = -1;
	graphics = g;

	visible = false;
	active = false;

	menuItemFont = new TextDX();
	menuHeadingFont = new TextDX();
	menuItemFontHighlight = new TextDX();

	if(menuItemFont->initialize(graphics, menuNS::ITEM_FONT_SIZE, true, false, "Small Fonts") == false)
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing menuItem font"));
	if(menuItemFontHighlight->initialize(graphics, menuNS::HIGHLIGHT_FONT_SIZE, true, false, "Small Fonts") == false)
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing menuItem font"));
	if(menuHeadingFont->initialize(graphics, menuNS::HEADING_FONT_SIZE, true, false, "Small Fonts") == false)
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing menuHeading font"));

	menuHeadingFont->setFontColor(normalColor);
	menuItemFont->setFontColor(normalColor);
	menuItemFontHighlight->setFontColor(highlightColor);

	upDepressedLastFrame = false;
	downDepressedLastFrame = false;
}

void Menu::update()
{
	// If not active only clear selectedItem and reset LinePtr
	if (getActive() == false)
	{
		linePtr = 0;
		selectedItem = -1;
		return;
	}

	// Scroll though menu with arrow keys
	if (input->isKeyDown(W_KEY) && !upDepressedLastFrame)
	{
		upDepressedLastFrame = true;
		linePtr--;
	}
	if (!input->isKeyDown(W_KEY))
		upDepressedLastFrame = false;

	if (input->isKeyDown(S_KEY) && !downDepressedLastFrame)
	{
		downDepressedLastFrame = true;
		linePtr++;
	}
	if (!input->isKeyDown(S_KEY))
		downDepressedLastFrame = false;

	// Wrap Menu
	if (linePtr > menuItems.size()-1 && linePtr != -1)			// Why????
		linePtr = 0;
	if (linePtr < 0) 
		linePtr = menuItems.size()-1;

	// Get Menu Item
	if (input->isKeyDown(VK_RETURN) &&!returnDepressedLastFrame)
	{
		returnDepressedLastFrame = true;
		selectedItem = getMenuItem(linePtr);
	}
	if (!input->isKeyDown(VK_RETURN))
	{
		returnDepressedLastFrame = false;
		selectedItem = -1;
	}
}

void Menu::displayMenu()
{
	// Do nothing if not visible
	if (getVisible() == false)
		return;

	// Display Header
	menuHeadingFont->print(menuHeading, menuAnchor.x, menuAnchor.y);

	// If there are no menu items return 
	if (menuItems.size() == 0)
		return;

	// Display Menu Items
	for (int i = 0; i < menuItems.size(); i++)
	{
		int offset = (i+1)*verticalOffset;
		if (linePtr == i)
			menuItemFontHighlight->print(menuItems[i], menuAnchor.x, menuAnchor.y+offset);
		else
			menuItemFont->print(menuItems[i], menuAnchor.x, menuAnchor.y+offset);
	}
}