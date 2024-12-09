#include "custom_scene_3501.h"
#include <godot_cpp/core/memory.hpp> // for memnew
#include <godot_cpp/classes/random_number_generator.hpp>

//Enemies 
#include "bee.h"
#include "wolf.h"
#include "slime.h"


using namespace godot;

void CustomScene3501::_bind_methods() { }

CustomScene3501::CustomScene3501() : Node3D() {
	time_passed = 0.0;
	load_filepaths();//load filepaths into hashmaps
}

CustomScene3501::~CustomScene3501() {}

void CustomScene3501::_enter_tree (){
	if(DEBUG) UtilityFunctions::print("Enter Tree - CustomScene3501.");

	//Add Nodes to Scene
	create_and_add_as_child<Player>(player, "Player");

	create_and_add_as_child<Map>(map,"Map");

	create_and_add_as_child<Skybox>(skybox,"Skybox");

	//create_particle_system("Snowstorm", "fire", "flame4x4orig", Vector2(1.0,1.0), Vector3(1.0, 1.0, 1.0)); //Make a temp Particle System
	init_debug_rects();	//add temp rect meshes to scene
	init_props();		//add props to scene
}

void CustomScene3501::_ready ( ){
	if(DEBUG) UtilityFunctions::print("Ready - CustomScene3501.");

	//Initialization Functions
	init_player(Vector3(200,4.5,200));
	
	map->generate_terrain(
		15,      // Width
		15,      // Height
		8,        // Octaves (keep it at 4 for more detail, but adjust if needed)
		3.0f,     // Persistence (adjust for smoother or more jagged terrain)
		20.0f,    // Scale (higher scale spreads out the features more)
		40.0f,    // Max height (increase for taller mountains)
		30.0f    // Mountain scale (increase for taller and more exaggerated mountains)
	);

	map->scatter_circles_on_mesh(100, 1.5);
	
	//Update Particle Systems with Location and Otherwise 
	for(int index = 0; index < particle_systems.size(); index++){
		// the current particle system we are setting up
		ParticleSystem* particle_system = particle_systems[index];

		// this should never be needed, but can't hurt to have. 
		if(particle_system == nullptr) continue;
		
		dynamic_cast<ShaderMaterial*>(*particle_system->get_draw_pass_mesh(0)->surface_get_material(0))->set_shader_parameter("num_particles", particle_system->get_amount());
        dynamic_cast<ShaderMaterial*>(*particle_system->get_process_material())->set_shader_parameter("num_particles", particle_system->get_amount());
	}
	
	//Update DebugRect objects to set their location and otherwise
	for(DebugRect* obj : rect_instances) obj->update_rect();
	
	//Update Prop Objects to set their location and positions
	for(Prop* obj : prop_instances) obj->update_prop();
}

// called every frame (as often as possible)
void CustomScene3501::_process(double delta) {
	if (Engine::get_singleton()->is_editor_hint()) return; // Early return if we are in editor

	time_passed += delta;
}

void CustomScene3501::create_prop(Vector3 size, Vector3 pos, Node* parentNode, String obj_name, String mesh_filepath, String texture_filepath_arr[], int num_textures){
	Prop* prop;
	create_and_add_as_child_of_Node<Prop>(prop,obj_name,parentNode);
	prop->setup_prop(pos, size, mesh_filepath, texture_filepath_arr, num_textures, obj_name);
	prop_instances.push_back(prop);
}

void CustomScene3501::create_rect(Vector3 scale, Vector3 pos, Node* parentNode, String name){
	DebugRect* rect;
	create_and_add_as_child_of_Node<DebugRect>(rect, name, parentNode);
	rect->setup_rect(scale, pos);
	rect_instances.push_back(rect);
}

void CustomScene3501::create_rect(Vector3 scale, Vector3 pos, Node* parentNode, String name, Vector3 color){
	DebugRect* rect;
	create_and_add_as_child_of_Node<DebugRect>(rect, name, parentNode);
	rect->setup_rect(scale, pos, color);
	rect_instances.push_back(rect);
}

void CustomScene3501::create_particle_system(String node_name, String shader_name, String texture_name, Vector2 size, Vector3 pos){
	// if you want to use non-zero argument constructors, here is an example of how to do that
	ParticleSystem* system = memnew(ParticleSystem(shader_name, texture_name, size, pos));
	add_as_child(system, node_name, true);
	particle_systems.push_back(system);
}



void CustomScene3501::create_npc(NpcType type, Vector3 pos){
	if (type == SlimeNpc){
		Slime* temp;
		create_and_add_as_child<Slime>(temp, vformat("NPC %s", NpcList.size()));
		temp->set_position(pos);
		temp->setPlayerPointer(player);
		NpcList.push_back(temp);
		
	} else if (type == WolfNpc){
		Wolf* temp;
		create_and_add_as_child<Wolf>(temp, vformat("NPC %s", NpcList.size()));
		temp->set_position(pos);
		temp->setPlayerPointer(player);
		NpcList.push_back(temp);

	} else if (type == BeeNpc){
		Bee* temp;
		create_and_add_as_child<Bee>(temp, vformat("NPC %s", NpcList.size()));
		temp->set_position(pos);
		NpcList.push_back(temp);
	} 
}

void CustomScene3501::createCollectable(Vector3 pos){
	Collectable* temp;
	create_and_add_as_child<Collectable>(temp, vformat("Collectable %d", collectableList.size()));
	temp->setPlayer(player);
	temp->set_position(pos);
	collectableList.push_back(temp);
}

void CustomScene3501::createPortal(Vector3 pos){
	create_and_add_as_child<Portal>(portal, "Portal");
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