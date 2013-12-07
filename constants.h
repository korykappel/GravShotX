// Programming 2D Games
// Copyright (c) 2011 by: 
// Charles Kelly
// Chapter 6 constants.h v1.1

#ifndef _CONSTANTS_H            // Prevent multiple definitions if this 
#define _CONSTANTS_H            // file is included in more than one place
#define WIN32_LEAN_AND_MEAN

#include <windows.h>

//=============================================================================
// Function templates for safely dealing with pointer referenced items.
// The functions defined by these templates may be called using a normal
// function call syntax. The compiler will create a function that replaces T
// with the type of the calling parameter.
//=============================================================================
// Safely release pointer referenced item
template <typename T>
inline void safeRelease(T& ptr)
{
    if (ptr)
    { 
        ptr->Release(); 
        ptr = NULL;
    }
}
#define SAFE_RELEASE safeRelease            // for backward compatiblility

// Safely delete pointer referenced item
template <typename T>
inline void safeDelete(T& ptr)
{
    if (ptr)
    { 
        delete ptr; 
        ptr = NULL;
    }
}
#define SAFE_DELETE safeDelete              // for backward compatiblility

// Safely delete pointer referenced array
template <typename T>
inline void safeDeleteArray(T& ptr)
{
    if (ptr)
    { 
        delete[] ptr; 
        ptr = NULL;
    }
}
#define SAFE_DELETE_ARRAY safeDeleteArray   // for backward compatiblility

// Safely call onLostDevice
template <typename T>
inline void safeOnLostDevice(T& ptr)
{
    if (ptr)
        ptr->onLostDevice(); 
}
#define SAFE_ON_LOST_DEVICE safeOnLostDevice    // for backward compatiblility

// Safely call onResetDevice
template <typename T>
inline void safeOnResetDevice(T& ptr)
{
    if (ptr)
        ptr->onResetDevice(); 
}
#define SAFE_ON_RESET_DEVICE safeOnResetDevice  // for backward compatiblility

//=============================================================================
//                  Constants
//=============================================================================

// window
const char CLASS_NAME[] = "Gravity Shot X";
const char GAME_TITLE[] = "Gravity Shot X";
const bool FULLSCREEN = false;              // windowed or fullscreen
const UINT GAME_WIDTH =  1200;               // width of game in pixels
const UINT GAME_HEIGHT = 700;               // height of game in pixels

// game
const double PI = 3.14159265;
const float FRAME_RATE = 200.0f;                // the target frame rate (frames/sec)
const float MIN_FRAME_RATE = 10.0f;             // the minimum frame rate
const float MIN_FRAME_TIME = 1.0f/FRAME_RATE;   // minimum desired time for 1 frame
const float MAX_FRAME_TIME = 1.0f/MIN_FRAME_RATE; // maximum time used in calculations
const RECT COLLISION_RECTANGLE = {-30, -16, 30, 16}; 
const RECT COLLISION_BOX_SHIP = {-30, -10, 30, 10};		//{ -x, -y, x, y}
const RECT COLLISION_BOX_AVATAR = {-48, -14, 48, 14};
const RECT COLLISION_BOX_SHIELD = {-60, -60, 60, 60};
const RECT COLLISION_BOX_BULLET = {-8, -8, 8, 8};
const RECT COLLISION_BOX_TANK = {-32, -14, 32, 14};
const float COLLISION_RADIUS = 29;

// graphic images
const char BUNGEE_IMAGE[] = "pictures\\bungee.png";
const char ENEMYSHIP_IMAGE[] = "pictures\\enemyShip.png";
const char AVATAR_IMAGE[] = "pictures\\AvatarShip.png";      // avatar texture
const char AVATARBULLET_IMAGE[] = "pictures\\avatarBullet.png";
const char ENEMYBULLET_IMAGE[] = "pictures\\enemyBullet.png";
const char TANK_IMAGE[] = "pictures\\Tank.png";
const char MARKER_IMAGE[] = "pictures\\marker.png";
const char BACKGROUND1_IMAGE[] = "pictures\\Background Level 1.png";
const char MIDGROUND1_IMAGE[] = "pictures\\Midground Level 1.png";
const char BACKGROUND2_IMAGE[] = "pictures\\Background Level 2.png";
const char MIDGROUND2_IMAGE[] = "pictures\\Midground Level 2.png";
const char BACKGROUND3_IMAGE[] = "pictures\\Background Level 3.png";
const char MIDGROUND3_IMAGE[] = "pictures\\Midground Level 3.png";
const char MENU_IMAGE[] = "pictures\\Menu Screen.png";
const char HEALTH_IMAGE[] = "pictures\\health.png";
const char BAR_IMAGE[] = "pictures\\bar.png";
const char EXPLOSION_IMAGE[] = "pictures\\Explosion.png";
const char SHIELD_IMAGE[] = "pictures\\shield.png";

const char BASEDESTROYED_IMAGE[] = "pictures\\Base Destroyed.png";
const char CREDITS_IMAGE[] = "pictures\\Credits.png";
const char ENDSCREEN_IMAGE[] = "pictures\\End Screen.png";
const char LEVELCOMPLETE_IMAGE[] = "pictures\\Level Complete.png";
const char YOUDIED_IMAGE[] = "pictures\\You Died.png";


// key mappings
// In this game simple constants are used for key mappings. If variables were used
// it would be possible to save and restore key mappings from a data file.
const UCHAR ESC_KEY      = VK_ESCAPE;			// Escape key
const UCHAR ALT_KEY      = VK_MENU;				// Alt key
const UCHAR PADDLE_LEFT    = VK_LEFT;			// Left arrow
const UCHAR PADDLE_RIGHT   = VK_RIGHT;			// Right arrow
const UCHAR ENTER_KEY    = VK_RETURN; 
const UCHAR A_KEY		= 0x41;
const UCHAR	D_KEY		= 0x44;
const UCHAR	S_KEY		= 0x53;
const UCHAR	W_KEY		= 0x57;


/////////
// Audio
/////////

// audio files required by audio.cpp
// WAVE_BANK must be location of .xwb file.
const char WAVE_BANK[]  = "audio\\Win\\Wave Bank.xwb";
// SOUND_BANK must be location of .xsb file.
const char SOUND_BANK[] = "audio\\Win\\Sound Bank.xsb";

// music cues
const char MENU_SONG[] = "Mighty_Eight_Bit_Ranger";
const char LEVEL_1_SONG[] = "WWWWub";
const char LEVEL_2_SONG[] = "Eight_Bit_Sahara";
const char LEVEL_3_SONG[] = "Eight_Bit_Space_Battle";
const char CREDITS_SONG[] = "Chiptune_Does_Dubstep";

// sound cues
const char GRAVITY_SHOT[] = "Gravity Shot";
const char ENEMY_SHOT[] = "Enemy Shot";
const char EXPLOSION_1[] = "Explosion 1";
const char EXPLOSION_2[] = "Explosion 2";
const char EXPLOSION_3[] = "Explosion 3";
const char AVATAR_EXPLOSION[] = "Explosion 4";


enum BungeeStates {none, enemyToEnemy, enemyToGround};
enum Type {SHIP, TANK};
enum GameStates {menu, gamePlay, quit, restart, win, levelEnd};

#endif
