#include "custom_scene_3501.h"
#include <godot_cpp/core/memory.hpp> // for memnew
#include <godot_cpp/classes/random_number_generator.hpp>


using namespace godot;

//load filepaths into hashmaps of important resources
//USE UNIQUE KEY VALUES
void CustomScene3501::load_filepaths(){
	String dir = "res://mesh_assets/";
	
	//MESH FILEPATHS//
	mesh_filepaths["OakTree_1"] = dir+"tree_mesh1.res";
	mesh_filepaths["OakTree_2"] = dir+"tree_mesh2.res";

	//TEXTURE FILEPATHS//
	texture_filepaths["OakLeaf_1"] = dir+"OakTreeLeaf.png";
	texture_filepaths["OakTrunk_1"] = dir+"OakTreeTrunk.png";
}

void CustomScene3501::init_debug_rects(){
	Node* rectGroup;
	create_or_add_child<Node>(rectGroup, "Debug Rect Group");//create grouping node
	create_rect(Vector3(1,1,1), Vector3(0,2,-5), rectGroup, "Test Cube", Vector3(0.8, 0.1, 0.1));
}

void CustomScene3501::init_props(){
	Node* propGroup;
	create_or_add_child<Node>(propGroup, "Game Props");//Create group node 

	Node* terrainPropGroup;
	create_or_add_child<Node>(terrainPropGroup, "Terrain Props", propGroup);

	Vector<String> tree_textures = {texture_filepaths["OakLeaf_1"], texture_filepaths["OakTrunk_1"]};
	create_prop(Vector3(10,10,10), Vector3(5,5,0), terrainPropGroup,"Test Tree", String(mesh_filepaths["OakTree_1"]), tree_textures);
	create_prop(Vector3(10,10,10), Vector3(-5,5,0), propGroup,"Test Tree 2", String(mesh_filepaths["OakTree_2"]), tree_textures);

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