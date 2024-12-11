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

	//TEXTURE FILEPATHS//
	//texture_filepaths[""] = "";
	texture_filepaths["Leaf_1"] = "res://mesh_assets/Lowpoly_Forest_Pack/Textures/OakTreeLeaf.png";
	texture_filepaths["Leaf_2"] = "res://mesh_assets/Lowpoly_Forest_Pack/Textures/SpruceTreeLeaf.png";
	texture_filepaths["Trunk_1"] = "res://mesh_assets/Lowpoly_Forest_Pack/Textures/OakTreeTrunk.png";
	texture_filepaths["Trunk_2"] = "res://mesh_assets/Lowpoly_Forest_Pack/Textures/SpruceTreeTrunk.png";
	texture_filepaths["Rock_1"] = "res://mesh_assets/Lowpoly_Forest_Pack/Textures/rockTexture1.png";
	texture_filepaths["Rock_2"] = "res://mesh_assets/Lowpoly_Forest_Pack/Textures/rockTexture2.png";
}

void CustomScene3501::init_debug_rects(){
	Node* rectGroup;
	create_or_add_child<Node>(rectGroup, "Debug Rect Group");//create grouping node
	create_rect(Vector3(1,1,1), Vector3(0,2,-5), rectGroup, "Test Cube", Vector3(0.8, 0.1, 0.1));
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