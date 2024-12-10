#include "tower.h"


using namespace godot;

void Tower::_bind_methods() {}

Tower::Tower() : Node3D(){
	load_filepaths();
}

Tower::~Tower() {}

void Tower::_enter_tree(){
	if(DEBUG) UtilityFunctions::print("Enter Tree - Tower.");
	import_tool = memnew(AssetImporter);
	

	build_tower();
}

void Tower::_ready(){ 
	//Call the update function of props (to update position, scale, and rotation data)
	for(Prop* prop_obj : obj_vector){prop_obj->update_prop();}
}

void Tower::build_tower(){
	Vector<String> tower_tex = {texture_filepaths["TowerBase"]};
	make_prop(Vector3(0,0,0), Vector3(2,2,2), Vector3(0,0,0), mesh_filepaths["TowerBase"], tower_tex, "TowerBase");
}

void Tower::make_prop(Vector3 pos, Vector3 scale, Vector3 rotation, String model_filepath, Vector<String> texture_filepaths, String name){
	Prop* prop;
	create_or_add_child<Prop>(prop, name);
	prop->setup_prop(pos, rotation, scale, model_filepath, texture_filepaths, name);
	obj_vector.push_back(prop);
}

void Tower::load_filepaths(){
	//MESH FILEPATHS//
	mesh_filepaths["TowerBase"] = "res://mesh_assets/Ruin_Asset_Pack/tower_1.res";
	mesh_filepaths["LowDoor_1"] = "res://mesh_assets/Ruin_Asset_Pack/low_door.res";
	mesh_filepaths["LowDoor_2"] = "res://mesh_assets/Ruin_Asset_Pack/low door closed.res";

	//TEXTURE FILEPATHS//
	texture_filepaths["TowerBase"] = "res://mesh_assets/Ruin_Asset_Pack/Textures/tower_1.png";
	texture_filepaths["LowDoor_1"] = "res://mesh_assets/Ruin_Asset_Pack/Textures/low_door.png";
	texture_filepaths["LowDoor_2"] = "res://mesh_assets/Ruin_Asset_Pack/Textures/low_door_closed.png";
}

Vector<String> Tower::make_vector(String arr[], int numStrings){
	Vector<String> vect;
	for(int i=0;i<numStrings;i++){
		vect.push_back(arr[i]);
	}
	return vect;
}

