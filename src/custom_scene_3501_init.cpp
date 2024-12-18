#include "custom_scene_3501.h"
#include <godot_cpp/core/memory.hpp> // for memnew
#include <godot_cpp/classes/random_number_generator.hpp>


using namespace godot;

//load filepaths into hashmaps of important resources
//USE UNIQUE KEY VALUES
void CustomScene3501::load_filepaths(){
	//MESH FILEPATHS//
	//mesh_filepaths[""] = "";
	mesh_filepaths["OakTree_1"] = "res://mesh_assets/Lowpoly_Forest_Pack/oaktree_1.res";
	mesh_filepaths["PineTree_1"] = "res://mesh_assets/Lowpoly_Forest_Pack/pinetree_1.res";
	mesh_filepaths["PortalFrame"] = "res://mesh_assets/Misc Meshes/portal_frame.res";
	mesh_filepaths["StonePlatform"] = "res://mesh_assets/Ruin_Asset_Pack/ruin_platform.res";

	//TEXTURE FILEPATHS//
	//texture_filepaths[""] = "";
	texture_filepaths["Leaf_1"] = "res://mesh_assets/Lowpoly_Forest_Pack/Textures/OakTreeLeaf.png";
	texture_filepaths["Leaf_2"] = "res://mesh_assets/Lowpoly_Forest_Pack/Textures/SpruceTreeLeaf.png";
	texture_filepaths["Trunk_1"] = "res://mesh_assets/Lowpoly_Forest_Pack/Textures/OakTreeTrunk.png";
	texture_filepaths["Trunk_2"] = "res://mesh_assets/Lowpoly_Forest_Pack/Textures/SpruceTreeTrunk.png";
	texture_filepaths["Rock_1"] = "res://mesh_assets/Lowpoly_Forest_Pack/Textures/rockTexture1.png";
	texture_filepaths["Rock_2"] = "res://mesh_assets/Lowpoly_Forest_Pack/Textures/rockTexture2.png";
	texture_filepaths["Rock_3"] = "res://mesh_assets/Misc_Textures/Rock_Handpainted_Beefpuppy.png";
	texture_filepaths["Rock_4"] = "res://mesh_assets/Misc_Textures/Cethiel_Tileable_Stone/Ground_03.png";
}

void CustomScene3501::init_props(){
	UtilityFunctions::print("Prop Call");
	Node* propGroup;
	create_or_add_child<Node>(propGroup, "Game Props");//Create group node 

	Node* terrainPropGroup;
	create_or_add_child<Node>(terrainPropGroup, "Terrain Props", propGroup);

	Vector<String> tree_textures = {texture_filepaths["Leaf_1"], texture_filepaths["Trunk_1"]};

	//INITIALIZE TERRAIN PROPS
	for(int i=0;i<NUM_TERRAIN_PROPS;i++){
		create_terrain_prop(Vector3(30.0,30.0,30.0), Vector3(-90.0, 4.0*i,0), terrainPropGroup,vformat("Gen_Tree_%d",i), String(mesh_filepaths["OakTree_1"]), tree_textures);
	}
}

void CustomScene3501::init_enemies(){
	Node* enemyGroup;
	create_or_add_child<Node>(enemyGroup, "Enemies");//Create group node 

	Node* terrainEnemyGroup;
	create_or_add_child<Node>(terrainEnemyGroup, "Terrain Enemies", enemyGroup);

	//INITIALIZE TERRAIN PROPS
	for(int i=0;i<NUM_WOLVES;i++){
		create_npc(WolfNpc, Vector3(0,0,0),terrainEnemyGroup,vformat("Wolf_%d",i));
	}
	for(int i=0;i<NUM_SLIMES;i++){
		create_npc(SlimeNpc, Vector3(0,0,0),terrainEnemyGroup,vformat("Slime_%d",i));
	}
	for(int i=0;i<NUM_BEES;i++){
		create_npc(BeeNpc, Vector3(0,0,0),terrainEnemyGroup, vformat("Bee_%d",i));
	}
}

void CustomScene3501::init_player(Vector3 start_pos){
	player->set_position(start_pos);
	player->_ready();//call the player's ready function after we set the attributes we want !!IMPORTANT!!
}
/*
*
* The usual container class added to the demos. This one should be used to create a racetrack.
*
* Copyright (c) 2024 Samantha Beilman (samanthabeilman@cmail.carleton.ca)
*
*/