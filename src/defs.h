#ifndef DEFS_H
#define DEFS_H

// easily toggle off the debug messages in the entire library
#define DEBUG true
#define PLAYER_DEBUG false
#define CURSOR_LOCK true    //Lock the cursor so that mouse movement can be used
#define ARROW_KEY_LOOK true

//Player Control Values
#define PLAYER_SENSITIVITY 0.0005
#define PLAYER_MOUSE_SMOOTHING 75.0
#define PLAYER_SPEED 3.5
#define PLAYER_JUMP_STR 6.0

#define PLAYER_ACCEL 12.0
#define PLAYER_AIR_CONTROL 8.0
#define PLAYER_AIR_FRICTION 2.5

//Terrain Genneration Constants
#define MAP_WIDTH 50				//Number of Veteces along the width
#define MAP_HEIGHT 50				//Number of Veteces along the height
#define MAP_SCALE 3.0f				//Vertex Density

#define MAP_OCTAVES 8				//leave this
#define MAP_PERSISTENCE 5.0f		//Smoothing factor
#define MAP_MAX_HEIGHT 10.0f		//Maximum mountain height
#define MAP_MOUNTAIN_SCALE 5.0f		//Scaling for mountains


//GLOBAL CONSTANTS
#define GRAVITY 12.0
#define TERMINAL_V 32.0

//SPAWN POSITION
#define SPAWN_X 84.9
#define SPAWN_Y 3.5
#define SPAWN_Z 84.5

//Number of enemies made
#define NUM_SLIMES 6
#define NUM_WOLVES 6
#define NUM_BEES 3

#endif // DEFS_H