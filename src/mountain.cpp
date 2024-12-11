#include "mountain.h"
#include <godot_cpp/core/memory.hpp> // for memnew
#include <godot_cpp/classes/random_number_generator.hpp>


using namespace godot;

void  Mountain::_bind_methods() { }

 Mountain:: Mountain() : Node3D() {
	time_passed = 0.0;
	load_filepaths();
}

 Mountain::~ Mountain() {}

void  Mountain::_enter_tree (){
	if(DEBUG) UtilityFunctions::print("Enter Tree - CustomScene3501.");

	create_or_add_child<Map>(map,"Map");

	build_props();
}

void  Mountain::_ready ( ){
	if(DEBUG) UtilityFunctions::print("Ready - CustomScene3501.");

    Vector3 start = Vector3(5.0f, 0.0f, 5.0f);
	Vector3 stop= Vector3(25.0f, 0.0f, 100.0f);
	float path_width = 15.0f;

    map->generate_mountain(
        70,    // Terrain width
        70,    // Terrain height
        1,      // Octaves (not used here)
        0.0f,   // Persistence
        1.0f,   // Scale
        20.0f,  // Maximum height
        10.0f,    // Mountain scale
        start,
		stop,
		path_width,
		false
    );

	//Call the update function of props (to update position, scale, and rotation data)
	for(Prop* prop_obj : prop_instances){prop_obj->update_prop();}

}

// called every frame (as often as possible)
void Mountain::_process(double delta) {
	if (Engine::get_singleton()->is_editor_hint()) return; // Early return if we are in editor

	time_passed += delta;
}


void Mountain::make_prop(Vector3 pos, Vector3 scale, Vector3 rotation, String model_filepath, Vector<String> texture_filepaths, String name){
	Prop* prop;
	create_or_add_child<Prop>(prop, name);
	prop->setup_prop(pos, rotation, scale, model_filepath, texture_filepaths, name);
	prop_instances.push_back(prop);
}

//Polymorph for meshes with one texture (This avoids declaring and making vectors for these meshes)
void Mountain::make_prop(Vector3 pos, Vector3 scale, Vector3 rotation, String model_filepath, String texture_filepath, String name){
	Prop* prop;
	create_or_add_child<Prop>(prop, name);
	Vector<String> texture_filepaths = {texture_filepath};
	prop->setup_prop(pos, rotation, scale, model_filepath, texture_filepaths, name);
	prop_instances.push_back(prop);
}

void Mountain::load_filepaths(){
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
	mesh_filepaths["SM_Wall_1"] = "res://mesh_assets/Ruin_Asset_Pack_Small/SM_RuinWalls_1.res";

	//Rocks
	mesh_filepaths["SM_Rock_1"] = "res://mesh_assets/Lowpoly_Forest_Pack/Rock_SM_1.res";
	mesh_filepaths["SM_Rock_2"] = "res://mesh_assets/Lowpoly_Forest_Pack/Rock_SM_2.res";
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

void Mountain::build_props(){
	//make_prop(Vector3(0, 0, 0), Vector3(1,1,1), Vector3(0,0,0), mesh_filepaths[""], texture_filepaths[""], "");

	//PLATFORMS
	make_prop(Vector3(25.99, -2.65, 72.9), Vector3(1.43,1.43,1.43), Vector3(25,161,0), mesh_filepaths["Platform_1"], texture_filepaths["StoneTile_3"], "Entry_Platform");
	make_prop(Vector3(22.24, 0.76, 76.05), Vector3(0.532,0.532,0.532), Vector3(88,0,-81), mesh_filepaths["SM_Rock_2"], texture_filepaths["Rock_3"], "Plat_1");
	make_prop(Vector3(21.4, 2.36, 77.75), Vector3(0.405,0.405,0.405), Vector3(90,-25,0), mesh_filepaths["SM_Rock_2"], texture_filepaths["Rock_3"], "Plat_2");
	make_prop(Vector3(20.3, 3.8, 79.6), Vector3(0.429,0.429,0.429), Vector3(-89,0,59), mesh_filepaths["SM_Rock_3"], texture_filepaths["Rock_3"], "Plat_3");
	make_prop(Vector3(19.86, 5.35, 82.5), Vector3(0.542,0.542,0.542), Vector3(72,-21,13), mesh_filepaths["SM_Rock_1"], texture_filepaths["Rock_3"], "Plat_4");
	make_prop(Vector3(18.82, 6.93, 85.32), Vector3(0.46,0.46,0.46), Vector3(77,-20,-18), mesh_filepaths["SM_Rock_6"], texture_filepaths["Rock_3"], "Plat_5");
	make_prop(Vector3(18.97, 8.6, 89.06), Vector3(0.615,0.615,0.615), Vector3(90,36,0), mesh_filepaths["SM_Rock_2"], texture_filepaths["Rock_3"], "Plat_6");
	make_prop(Vector3(22.98, 9.78, 86.55), Vector3(1.24,0.9,1), Vector3(88,-180,166), mesh_filepaths["SM_Rock_2"], texture_filepaths["Rock_3"], "Plat_7");

	//Decoration
	make_prop(Vector3(29.02, -2.04, 77.8), Vector3(0.012,0.012,0.012), Vector3(0,-19,0), mesh_filepaths["SM_Arch_1"], texture_filepaths["StoneTile_3"], "Entry Arch");
	make_prop(Vector3(21.1, 10.7, 88.7), Vector3(1,1,0.85), Vector3(0,0,0), mesh_filepaths["LowDoor_2"], texture_filepaths["Rock_3"], "Plat_7 Arch");
	make_prop(Vector3(28.34, 7.19, 84.12), Vector3(0.98,1.23,1.315), Vector3(-6,-54,52), mesh_filepaths["SM_Rock_5"], texture_filepaths["Rock_2"], "Hole Plug_1");
}


