# SkyWardQuest
Contributors:
	- Zac Bowness
	- Ellie
	- Sam Abraham 101249272

# Design Decisions


# Question Completion


# Manifest
## Shader Files
*Particle and Spatial Shaders are combined into one entry for convenience if applicable
	glyph_ps/_ss.gdshader
		- Code for the particle effect near the magical Tower class
		- 
	snow_ps/_ss.gdshader

	spiralScreenEffect.gdshader

	skybox.gdshader

## SRC Files
*source and header files are combined into 1 entry for simplicity*
### Instantiated Object Classes
	
	startScene.cpp/ .h
		- Instantiates a Starting screen that can be swapped to the main game by pressing enter

	gameOverScene.cpp/ .h
		- Instantiates a Game Over Screen that is swapped to when you win the game

	bee classes {Bee.cpp/h, Bee_fullBody.cpp/h, Bee_LeftWing.cpp/h, Bee_RightWing.cpp/h, Bee_EyesWing.cpp/h}
		- Instantiate and animate 
	
	collectable.cpp/.h
		- Class for the collectible items that need to be picked up in order to complete the game

	slime.cpp/ .h
		- Instantiates and creates Physics for a Slime Enemy
		- Uses state machines to control how the enemy moves

	wolf.cpp/ .h
		- Instantiates and creates Physics for a Wolf Enemy
		- Uses state machines to control how the enemy moves

	
	
	
	
### 
	custom_scene_3501.cpp/.h
		- The main node of the game
		- Instantiates and updates all the objects in the game world
		- Creates and places particle systems
		- passes relevent values to Map class for terrain generation
	particle_system_3501.cpp/.h
		- Class used to manage and instantiate the game's particle systems
		- Takes parameters from CustomScene3501 and creates particle systems accordingly
	
	
	defs.h
		- Contains important definitions used across the game
		- Defines player control values like mouse sensitivity and movement speed
		- Defines Map generation constants
		- Defines global variables like gravity and player spawn position
		
	2dScene.cpp/.h
		- Provides a overall 2d Scene for the game

	register_types.cpp/.h
		- register all the classes and files required for the project

	npc.cpp/h
		- Provides overall basic functions for NPCs
		- This includes path finding functions

	enemy.cpp/h
		- Overall Enemy Functionality

	friendly.cpp/h
		- Overall Passive Npc Functionality

# Bugs
- for some reason 2 or 3 individual particles like to flicker between runes (its just wild magic I think)
