#include "custom_scene_3501.h"
#include <godot_cpp/core/memory.hpp> // for memnew
#include <godot_cpp/classes/random_number_generator.hpp>




using namespace godot;

void CustomScene3501::_bind_methods() { }

CustomScene3501::CustomScene3501() : Node3D() {
	time_passed = 0.0;
	load_filepaths();//load filepaths into hashmaps
	
	//Define positions for collectible objects
	collectible_1_pos = Vector3(58.94,9.08,49.1);
	collectible_2_pos = Vector3(28.7,9.4,83.5);
	collectible_3_pos = Vector3(86,3.7,90);
}

CustomScene3501::~CustomScene3501() {}

void CustomScene3501::_enter_tree (){
	if(DEBUG) UtilityFunctions::print("Enter Tree - CustomScene3501.");

	//Add Nodes to Scene
	create_or_add_child<Player>(player, "Player");

	create_or_add_child<Map>(map,"Map");

	create_or_add_child<Skybox>(skybox,"Skybox");

	createPortal(Vector3(90.26,5.8,89.67));

	create_particle_system("Magic Glyphs", "glyph", "glyph4x4", Vector2(0.5,0.5), Vector3(57.0, -1.5, 45.0), 0,  80, 10.0); //Make a magical glyph Particle System
	
	create_particle_system("Snowstorm", "snow", "snow2x2", Vector2(0.25,0.25), Vector3(17.4, 11.5, 85.0),0, 500, 10.0); //Make a snowstorm Particle System
	
	create_or_add_child<Tower>(tower, "Magical Tower");

	create_or_add_child<Mountain>(mountain, "Mountain");

	init_props();		//add props to scene
	init_enemies();
	
}

void CustomScene3501::_ready ( ){
	if(DEBUG) UtilityFunctions::print("Ready - CustomScene3501.");

	//Initialize player location
	init_player(Vector3(SPAWN_X,SPAWN_Y,SPAWN_Z));
	
	//Generate Terrain (Values are modifiable in defs.h)
	map->generate_terrain(
		MAP_WIDTH,
		MAP_HEIGHT,
		MAP_OCTAVES,
		MAP_PERSISTENCE,
		MAP_SCALE,
		MAP_MAX_HEIGHT,
		MAP_MOUNTAIN_SCALE,
		1
	);

	//Get Valid Positions on the terrain mesh to place tree/rock/env objects
	Vector<Vector<float>> heightfield = map->get_heightfield();
	map->add_mesh(heightfield, Vector3(0,0,0), Color(0.1, 0.9, 0.1));//
	
	Vector<Vector3> map_pos = map->scatter_props(heightfield, MAP_WIDTH, MAP_HEIGHT, MAP_SCALE, NUM_TERRAIN_PROPS);
	
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
	
	//Update Prop Objects to set their location and positions
	for(Prop* obj : prop_instances) obj->update_prop();

	//Update game objects with positional data
	update_terrain_props(map_pos);
	update_terrain_enemies();
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

void CustomScene3501::update_terrain_enemies(){
	for(int i=0; i<NpcList.size(); i++){
		NpcList[i]->update_npc_position(EnemySpawnLocations[i]);
	}
}

//Create a particle system with the given parameters
void CustomScene3501::create_particle_system(String node_name, String shader_name, String texture_name, Vector2 size, Vector3 pos, float angle, int32_t amount_in, double lifetime_in){
	// if you want to use non-zero argument constructors, here is an example of how to do that
	ParticleSystem* system;
	create_or_add_child<ParticleSystem>(system, node_name);
	system->init_particle_system(shader_name, texture_name, size, pos, angle, amount_in, lifetime_in);
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

//Create the portal structure that the player spawns near
void CustomScene3501::createPortal(Vector3 pos){
	//create portal node
	create_or_add_child<Portal>(portal, "Portal");
	Node3D* portal_effect_parent;
	create_or_add_child<Node3D>(portal_effect_parent, "Portal Effect Parent",portal);
	create_or_add_child<PortalEffect>(portal_effect, "portal_effect", portal_effect_parent);
	portal->setPlayer(player);
	portal->set_position(pos);
	portal_effect_parent->set_scale(Vector3(0.22,1, 1));

	Vector<String> portalFrameTex = {texture_filepaths["Rock_3"]};
	Vector<String> portalPlatformTex = {texture_filepaths["Rock_4"]};
	create_prop(Vector3(0.541,0.541,0.541), Vector3(0.02,-0.11,0), Vector3(0,0,-90), portal, "Portal Frame", mesh_filepaths["PortalFrame"], portalFrameTex);
	create_prop(Vector3(1.192,1.192,1.192), Vector3(0.07, -1.97, 2.55), Vector3(0,0,0), portal, "Portal Platform Top", mesh_filepaths["StonePlatform"], portalPlatformTex);
	create_prop(Vector3(1.938,1.938,1.938), Vector3(0.17,-3.07,3.83), Vector3(0,0,0), portal, "Portal Platform Bottom", mesh_filepaths["StonePlatform"], portalPlatformTex);
	
}


/*
*
* The usual container class added to the demos. This one should be used to create a racetrack.
*
* Copyright (c) 2024 Samantha Beilman (samanthabeilman@cmail.carleton.ca)
*
*/