#include "custom_scene_3501.h"
#include <godot_cpp/core/memory.hpp> // for memnew
#include <godot_cpp/classes/random_number_generator.hpp>




using namespace godot;

void CustomScene3501::_bind_methods() { }

CustomScene3501::CustomScene3501() : Node3D() {
	time_passed = 0.0;
	load_filepaths();//load filepaths into hashmaps
	collectible_1_pos = Vector3(58,10,49);
	collectible_2_pos = Vector3(25,2,64);
	collectible_3_pos = Vector3(91,5,87);
}

CustomScene3501::~CustomScene3501() {}

void CustomScene3501::_enter_tree (){
	if(DEBUG) UtilityFunctions::print("Enter Tree - CustomScene3501.");

	//Add Nodes to Scene
	create_or_add_child<Player>(player, "Player");

	create_or_add_child<Map>(map,"Map");

	create_or_add_child<Skybox>(skybox,"Skybox");

	create_or_add_child<PortalEffect>(portal_effect, "portal_effect");

	create_particle_system("Snowstorm", "snow", "snow2x2", Vector2(0.25,0.25), Vector3(1.0, 1.0, 1.0), 100, 10.0); //Make a temp Particle System
	create_or_add_child<Tower>(tower, "Magical Tower");

	create_or_add_child<Mountain>(mountain, "Mountain");

	//create_particle_system("Snowstorm", "fire", "flame4x4orig", Vector2(1.0,1.0), Vector3(1.0, 1.0, 1.0)); //Make a temp Particle System
	init_debug_rects();	//add temp rect meshes to scene
	init_props();		//add props to scene
	init_enemies();
	
}

void CustomScene3501::_ready ( ){
	if(DEBUG) UtilityFunctions::print("Ready - CustomScene3501.");

	//String tree_textures[] = {texture_filepaths["OakLeaf_1"], texture_filepaths["OakTrunk_1"]};

	//Initialization Functions
	init_player(Vector3(3,4.5,3));
	
	//Generate Terrain (Values are modifiable in defs.h)
	map->generate_terrain(
		MAP_WIDTH,
		MAP_HEIGHT,
		MAP_OCTAVES,
		MAP_PERSISTENCE,
		MAP_SCALE,
		MAP_MAX_HEIGHT,
		MAP_MOUNTAIN_SCALE
	);

	//Get Valid Positions on the terrain mesh to place tree/rock/env objects
	Vector<Vector<float>> heightfield = map->get_heightfield();
	Vector<Vector3> map_pos = map->scatter_props(heightfield, MAP_WIDTH, MAP_HEIGHT, MAP_SCALE, NUM_TERRAIN_PROPS);
	Vector<Vector3> enemy_pos = map->scatter_props(heightfield, MAP_WIDTH, MAP_HEIGHT, MAP_SCALE, NUM_TERRAIN_PROPS);
	//for(Vector3 pos : map_pos) UtilityFunctions::print(pos);

	//map->scatter_circles_on_mesh(100, 1.5);
	
	//Update Particle Systems with Location and Otherwise 
	for(int index = 0; index < particle_systems.size(); index++){
		// the current particle system we are setting up
		ParticleSystem* particle_system = particle_systems[index];

		particle_system->update_particle_system();

		// this should never be needed, but can't hurt to have. 
		if(particle_system == nullptr) continue;
		
		dynamic_cast<ShaderMaterial*>(*particle_system->get_draw_pass_mesh(0)->surface_get_material(0))->set_shader_parameter("num_particles", particle_system->get_amount());
        dynamic_cast<ShaderMaterial*>(*particle_system->get_process_material())->set_shader_parameter("num_particles", particle_system->get_amount());
	}

	//for (Npc* npc : NpcList) npc->update_npc();

	//Update DebugRect objects to set their location and otherwise
	for(DebugRect* obj : rect_instances) obj->update_rect();
	
	//Update Prop Objects to set their location and positions
	for(Prop* obj : prop_instances) obj->update_prop();

	update_terrain_props(map_pos);
	update_terrain_enemies(enemy_pos);
	collectibles_in_scene();

	//Update Tower Position
	tower->set_position(Vector3(57, -1.49, 45));
	tower->set_rotation_degrees(Vector3(0,-56,0));
}


// called every frame (as often as possible)
void CustomScene3501::_process(double delta) {
	if (Engine::get_singleton()->is_editor_hint()) return; // Early return if we are in editor

	time_passed += delta;
}

void CustomScene3501::create_prop(Vector3 size, Vector3 pos, Node* parentNode, String obj_name, String mesh_filepath, Vector<String> texture_filepaths){
	Prop* prop;
	create_or_add_child<Prop>(prop,obj_name,parentNode);
	prop->setup_prop(pos, Vector3(0,0,0), size, mesh_filepath, texture_filepaths, obj_name);
	prop_instances.push_back(prop);
}

void CustomScene3501::create_prop(Vector3 size, Vector3 pos, Vector3 rotation, Node* parentNode, String obj_name, String mesh_filepath, Vector<String> texture_filepaths){
	Prop* prop;
	create_or_add_child<Prop>(prop,obj_name,parentNode);
	prop->setup_prop(pos, rotation, size, mesh_filepath, texture_filepaths, obj_name);
	prop_instances.push_back(prop);
}

void CustomScene3501::create_terrain_prop(Vector3 size, Vector3 rotation, Node* parentNode, String obj_name, String mesh_filepath, Vector<String> texture_filepaths){
	Prop* prop;
	create_or_add_child<Prop>(prop,obj_name,parentNode);
	prop->setup_prop(Vector3(0,0,0), rotation, size, mesh_filepath, texture_filepaths, obj_name);
	terrain_prop_instances.push_back(prop);
}

void CustomScene3501::update_terrain_props(Vector<Vector3> pos_vect){
	int count = 0;
	for(Prop* obj : terrain_prop_instances){
		if(count<pos_vect.size()){
			obj->new_position(pos_vect[count]);
		} 
		else UtilityFunctions::print("ERROR: Not Enough Unique Positions For Terrain Props");
		obj->update_prop();
		count++;
	}
}

void CustomScene3501::update_terrain_enemies(Vector<Vector3> pos_vect){
	for(int i=0; i<NpcList.size(); i++){
		NpcList[i]->update_npc_position(pos_vect[i]);
	}
}

void CustomScene3501::create_rect(Vector3 scale, Vector3 pos, Node* parentNode, String name){
	DebugRect* rect;
	create_or_add_child<DebugRect>(rect, name, parentNode);
	rect->setup_rect(scale, pos);
	rect_instances.push_back(rect);
}

void CustomScene3501::create_rect(Vector3 scale, Vector3 pos, Node* parentNode, String name, Vector3 color){
	DebugRect* rect;
	create_or_add_child<DebugRect>(rect, name, parentNode);
	rect->setup_rect(scale, pos, color);
	rect_instances.push_back(rect);
}

void CustomScene3501::create_particle_system(String node_name, String shader_name, String texture_name, Vector2 size, Vector3 pos, int32_t amount_in, double lifetime_in){
	// if you want to use non-zero argument constructors, here is an example of how to do that
	ParticleSystem* system;
	create_or_add_child<ParticleSystem>(system, node_name);
	system->init_particle_system(shader_name, texture_name, size, pos, amount_in, lifetime_in);
	particle_systems.push_back(system);
}

void CustomScene3501::collectibles_in_scene(){
	createCollectable(collectible_1_pos, "collectable_1");
	createCollectable(collectible_2_pos, "collectable_2");
	createCollectable(collectible_3_pos, "collectable_3");
}

void CustomScene3501::create_npc(SpawnNPC type, Vector3 pos, Node* parentNode, String name){
    if (type == SlimeNpc){
        Slime* temp;
        create_or_add_child<Slime>(temp, name, parentNode);
        temp->setStartPos(pos);
        temp->setPlayerPointer(player);
        NpcList.push_back(temp);

    } else if (type == WolfNpc){
        Wolf* temp;
        create_or_add_child<Wolf>(temp, name, parentNode);
        temp->setStartPos(pos);
        temp->setPlayerPointer(player);
        temp->setScale(Vector3(0.175, 0.175, 0.175));
        NpcList.push_back(temp);

    } else if (type == BeeNpc){
        Bee* temp;
        create_or_add_child<Bee>(temp, name, parentNode);
        temp->setStartPos(pos);
        NpcList.push_back(temp);
    } 
}

void CustomScene3501::createCollectable(Vector3 pos, String name){
	Collectable* temp;
	create_or_add_child<Collectable>(temp, name);
	temp->setPlayer(player);
	temp->set_position(pos);
	collectableList.push_back(temp);
}

void CustomScene3501::createPortal(Vector3 pos){
	create_or_add_child<Portal>(portal, "Portal");
	portal->setPlayer(player);
	portal->set_position(pos);
}


/*
*
* The usual container class added to the demos. This one should be used to create a racetrack.
*
* Copyright (c) 2024 Samantha Beilman (samanthabeilman@cmail.carleton.ca)
*
*/