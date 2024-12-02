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

//GLOBAL CONSTANTS
#define GRAVITY 12.0
#define TERMINAL_V 32.0


#endif // DEFS_H