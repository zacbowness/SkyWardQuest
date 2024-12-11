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

void Tower::load_filepaths(){
	//mesh_filepaths[""] = "";
	//texture_filepaths[""] = "";
	
	//MESH FILEPATHS//
	mesh_filepaths["TowerBase"] = "res://mesh_assets/Misc Meshes/tower_1.res";
	mesh_filepaths["LowDoor_1"] = "res://mesh_assets/Ruin_Asset_Pack/low_door.res";
	mesh_filepaths["LowDoor_2"] = "res://mesh_assets/Ruin_Asset_Pack/low door closed.res";
	mesh_filepaths["Platform_1"] = "res://mesh_assets/Ruin_Asset_Pack/ruin_platform.res";
	mesh_filepaths["Pillar_1"] = "res://mesh_assets/Ruin_Asset_Pack/Low_Piller_1.res";
	mesh_filepaths["Pillar_3"] = "res://mesh_assets/Ruin_Asset_Pack/Low_Piller_3.res";
	mesh_filepaths["LowWall_Broken"] = "res://mesh_assets/Ruin_Asset_Pack/low ruin wall broken.res";
	
	//SM_Ruin_Pack
	mesh_filepaths["SM_Arch_1"] = "res://mesh_assets/Ruin_Asset_Pack_Small/SM_Arch_1.res";
	mesh_filepaths["SM_Arch_2"] = "res://mesh_assets/Ruin_Asset_Pack_Small/SM_Arch_2.res";
	mesh_filepaths["SM_Arch_3"] = "res://mesh_assets/Ruin_Asset_Pack_Small/SM_Arch_3.res";

	//Rocks
	mesh_filepaths["SM_Rock_1"] = "res://mesh_assets/Lowpoly_Forest_Pack/Rock_SM_1.res";
	mesh_filepaths["SM_Rock_3"] = "res://mesh_assets/Lowpoly_Forest_Pack/Rock_SM_3.res";
	mesh_filepaths["SM_Rock_4"] = "res://mesh_assets/Lowpoly_Forest_Pack/Rock_SM_4.res";
	mesh_filepaths["SM_Rock_5"] = "res://mesh_assets/Lowpoly_Forest_Pack/Rock_SM_5.res";
	mesh_filepaths["SM_Rock_6"] = "res://mesh_assets/Lowpoly_Forest_Pack/Rock_SM_6.res";
	
	mesh_filepaths["LG_Rock_3"] = "res://mesh_assets/Lowpoly_Forest_Pack/Rock_LG_3.res";

	//TEXTURE FILEPATHS//
	texture_filepaths["TowerBase"] = "res://mesh_assets/Misc_Textures/tower_base.png";
	
	//Rock Textures
	texture_filepaths["Rock_1"] = "res://mesh_assets/Lowpoly_Forest_Pack/Textures/rockTexture1.png";
	texture_filepaths["Rock_2"] = "res://mesh_assets/Lowpoly_Forest_Pack/Textures/RockTexture2.png";
	texture_filepaths["Rock_3"] = "res://mesh_assets/Misc_Textures/rock_rubberduck.png";
	texture_filepaths["Rock_4"] = "res://mesh_assets/Misc_Textures/Rock_Handpainted_Beefpuppy.png";
	texture_filepaths["StoneTile_1"] = "res://mesh_assets/Misc_Textures/Cethiel_Tileable_Stone/Ground_01.png";
	texture_filepaths["StoneTile_2"] = "res://mesh_assets/Misc_Textures/Cethiel_Tileable_Stone/Ground_02.png";
	texture_filepaths["StoneTile_3"] = "res://mesh_assets/Misc_Textures/Cethiel_Tileable_Stone/Ground_03.png";
	texture_filepaths["StoneTile_4"] = "res://mesh_assets/Misc_Textures/Cethiel_Tileable_Stone/Ground_04.png";
	
	
	texture_filepaths["LowDoor_1"] = "res://mesh_assets/Ruin_Asset_Pack/Textures/low_door.png";
	texture_filepaths["LowDoor_2"] = "res://mesh_assets/Ruin_Asset_Pack/Textures/low_door_closed.png";
	texture_filepaths["LowPillar_1"] = "res://mesh_assets/Ruin_Asset_Pack/Textures/Low_Piller_1.png";

}

void Tower::build_tower(){
	//make_prop(Vector3(0, 0, 0), Vector3(1,1,1), Vector3(0,0,0), mesh_filepaths[""], texture_filepaths[""], "");

	//Tower Base
	make_prop(Vector3(0,0,0), Vector3(2,2,2), Vector3(0,0,0), mesh_filepaths["TowerBase"], texture_filepaths["TowerBase"], "TowerBase");
	
	//Entryway Clutter
	make_prop(Vector3(-8.9,0,4.54), Vector3(0.012,0.012,0.012), Vector3(0,-90,0), mesh_filepaths["SM_Arch_1"], texture_filepaths["StoneTile_3"], "Entry Arch");
	make_prop(Vector3(-6.5,-0.4,2), Vector3(1,1,1), Vector3(0,0,18), mesh_filepaths["Platform_1"], texture_filepaths["StoneTile_3"], "Entry Ramp");
	make_prop(Vector3(-6.18,-0.36,3.97), Vector3(1,1,1), Vector3(0,41,-27.5), mesh_filepaths["Pillar_3"], texture_filepaths["LowPillar_1"], "Entry Pillar");
	make_prop(Vector3(-5.37,0,-2.58), Vector3(1,1,1), Vector3(0,-14.6,0), mesh_filepaths["SM_Rock_4"], texture_filepaths["Rock_1"], "Entryway Rock");
	make_prop(Vector3(-0.8, 0, -9), Vector3(1,1,1), Vector3(0,111,0), mesh_filepaths["LowWall_Broken"], texture_filepaths["LowPillar_1"], "Broken Wall");

	//Floating Structures
	make_prop(Vector3(2.65, 5.08, 1.24), Vector3(0.008,0.008,0.008), Vector3(45,32,41), mesh_filepaths["SM_Arch_3"], texture_filepaths["StoneTile_3"], "Floating Arch_1");
	make_prop(Vector3(1.35, 11.48, 1.2), Vector3(0.006,0.006,0.006), Vector3(48,78,176), mesh_filepaths["SM_Arch_2"], texture_filepaths["StoneTile_3"], "Floating Arch_2");
	
	make_prop(Vector3(2.9, 9.93, 0.73), Vector3(0.73,0.95,0.59), Vector3(-9,-57,17), mesh_filepaths["LowDoor_2"], texture_filepaths["Rock_3"], "Plat_4_Arch");
	make_prop(Vector3(5.43, 9.78, 0.13), Vector3(0.7,0.7,0.7), Vector3(-33,28,8), mesh_filepaths["Pillar_1"], texture_filepaths["StoneTile_1"], "Plat_4_Pillar");

	//Floating Rocks
	make_prop(Vector3(-5.83, 8.25, -1.56), Vector3(0.14,0.14,0.14), Vector3(0,0,0), mesh_filepaths["SM_Rock_3"], texture_filepaths["Rock_3"], "Floating Rock_1");
	make_prop(Vector3(0.81, 7.7, 0.89), Vector3(0.16,0.16,0.16), Vector3(-35,-15,26), mesh_filepaths["SM_Rock_5"], texture_filepaths["Rock_1"], "Floating Rock_2");

	//Floating jump Points (In jumping order)
	make_prop(Vector3(-3.2, 6.13, 1.1), Vector3(0.52,0.52,0.52), Vector3(78.5,-126.5,-127.3), mesh_filepaths["SM_Rock_6"], texture_filepaths["Rock_3"], "Plat_1");
	make_prop(Vector3(-2.19, 7.495, -1.827), Vector3(0.455,0.455,0.455), Vector3(81,-54,87), mesh_filepaths["SM_Rock_1"], texture_filepaths["Rock_3"], "Plat_2");
	make_prop(Vector3(1.26, 8.63, -2.68), Vector3(0.49,0.49,0.49), Vector3(-80,-74,47), mesh_filepaths["SM_Rock_3"], texture_filepaths["Rock_3"], "Plat_3");
	make_prop(Vector3(5, 9.75, 0.39), Vector3(0.486,0.66,0.3), Vector3(71,16,96), mesh_filepaths["LG_Rock_3"], texture_filepaths["Rock_3"], "Plat_4");

}

void Tower::make_prop(Vector3 pos, Vector3 scale, Vector3 rotation, String model_filepath, Vector<String> texture_filepaths, String name){
	Prop* prop;
	create_or_add_child<Prop>(prop, name);
	prop->setup_prop(pos, rotation, scale, model_filepath, texture_filepaths, name);
	obj_vector.push_back(prop);
}

//Polymorph for meshes with one texture (This avoids declaring and making vectors for these meshes)
void Tower::make_prop(Vector3 pos, Vector3 scale, Vector3 rotation, String model_filepath, String texture_filepath, String name){
	Prop* prop;
	create_or_add_child<Prop>(prop, name);
	Vector<String> texture_filepaths = {texture_filepath};
	prop->setup_prop(pos, rotation, scale, model_filepath, texture_filepaths, name);
	obj_vector.push_back(prop);
}



Vector<String> Tower::make_vector(String arr[], int numStrings){
	Vector<String> vect;
	for(int i=0;i<numStrings;i++){
		vect.push_back(arr[i]);
	}
	return vect;
}

