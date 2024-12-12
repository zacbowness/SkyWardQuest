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
		- Creates an illusion of symbols spawning from the ground into the air
	
	snow_ps/_ss.gdshader
		- Creates a light snow effect that appears around the mountain 

	spiralScreenEffect.gdshader
		- shader creates a spiraling effect on a 3D object, and animates the colour based on polar coordinates

	skybox.gdshader
		- Applies a scrolling effect and maps a texture to a 3D object using z and y coordinates

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
	
	portal classes {portal.cpp/h, portal_effect.cpp/h}
		- portal.cpp creates a mesh for the portal, that when the player collides with it after c

	map.cpp/h
		- Class used for the creation of the heightfield, creating a mesh given a heightfield, and for giving valid position where objects can be placed on the heightfield

	player_scene.cpp/h 
		- Instantiates player that inherits a CharacterBody3D to control movement
		- Has a child of QuatCamera to provide sight to player
		- Has a ScreenMesh to provide screen effects
		- Has functions related to dying and respawning

	tower.cpp/h
		- Instantiates the tower and props/particle systems related to tower

	mountain.cpp/h
		- Generates a height field to replicate a mountain

	prop.cpp/h 
		- A overall function that provides meshes and colliders using asset_importer 
		to create terrain objects 

### 
	asset_importer.cpp/h
		-  Used to import assests into godot and provides their meshes, textures and colliders

	QuatCamera.cpp/h
		- Creates a QuatCamera to provide vision

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
- Due to Look_At() Function not working the enemies do not face the direction they are moving
