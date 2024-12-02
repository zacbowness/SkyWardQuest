#include "custom_scene_3501.h"
#include <godot_cpp/core/memory.hpp> // for memnew
#include <godot_cpp/classes/random_number_generator.hpp>


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

	create_and_add_as_child<Slime>(slime, "Test Slime");

	create_and_add_as_child<Map>(map,"Map");

	//create_particle_system("Snowstorm", "fire", "flame4x4orig", Vector2(1.0,1.0), Vector3(1.0, 1.0, 1.0)); //Make a temp Particle System
	init_debug_rects();	//add temp rect meshes to scene
	init_props();		//add props to scene
}

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
	create_and_add_as_child<Node>(rectGroup, "Debug Rect Group");//create grouping node
	create_rect(Vector3(1,1,1), Vector3(0,2,-5), rectGroup, "Test Cube", Vector3(0.8, 0.1, 0.1));
}

void CustomScene3501::init_props(){
	Node* propGroup;
	create_and_add_as_child<Node>(propGroup, "Game Props");//Create group node

	Node* terrainPropGroup;
	create_and_add_as_child_of_Node<Node>(terrainPropGroup, "Terrain Props", propGroup);

	String tree_textures[] = {texture_filepaths["OakLeaf_1"], texture_filepaths["OakTrunk_1"]};
	create_prop(Vector3(10,10,10), Vector3(5,5,0), terrainPropGroup,"Test Tree", String(mesh_filepaths["OakTree_1"]), tree_textures, 2);
	create_prop(Vector3(10,10,10), Vector3(-5,5,0), terrainPropGroup,"Test Tree 2", String(mesh_filepaths["OakTree_2"]), tree_textures, 2);
}

void CustomScene3501::_ready ( ){
	if(DEBUG) UtilityFunctions::print("Ready - CustomScene3501.");

	//Initialization Functions
	init_player(Vector3(200,4.5,200));
	
	slime->setPlayerPointer(player);
	slime->_ready();

	map->generate_terrain(
		15,      // Width
		15,      // Height
		8,        // Octaves (keep it at 4 for more detail, but adjust if needed)
		3.0f,     // Persistence (adjust for smoother or more jagged terrain)
		20.0f,    // Scale (higher scale spreads out the features more)
		40.0f,    // Max height (increase for taller mountains)
		30.0f    // Mountain scale (increase for taller and more exaggerated mountains)
	);
	
	

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

void CustomScene3501::init_player(Vector3 start_pos){
	player->set_position(start_pos);
	player->_ready();//call the player's ready function after we set the attributes we want !!IMPORTANT!!
}

void CustomScene3501::create_prop(Vector3 size, Vector3 pos, Node* parentNode, String obj_name, String mesh_filepath, String texture_filepath_arr[], int num_textures){
	Prop* prop;
	bool isNew = create_and_add_as_child_of_Node<Prop>(prop,obj_name,parentNode);
	prop->setup_prop(pos, size, mesh_filepath, texture_filepath_arr,num_textures,obj_name);
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

template <class T>
// returns true if pointer is brand-new; false if retrieved from SceneTree
bool CustomScene3501::create_and_add_as_child(T* &pointer, String name){

	Node* child = find_child(name);
	
	if(child == nullptr){
		pointer = memnew(T);
		pointer->set_name(name);
		add_child(pointer);
		pointer->set_owner(get_tree()->get_edited_scene_root());
		return true;
	}
	else{
		pointer = dynamic_cast<T*>(child);
		return false;
	}
}


template <class T>
// returns true if pointer is brand-new; false if retrieved from SceneTree
bool CustomScene3501::create_and_add_as_child_of_Node(T* &pointer, String name, Node* parent){
	
	Node* child = find_child(name);//find node with the given name

	if(child == nullptr){//if child node was not found, create it
		pointer = memnew(T);
		pointer->set_name(name);
		parent->add_child(pointer);
		pointer->set_owner(get_tree()->get_edited_scene_root());
		return true;
	} else {
		pointer = dynamic_cast<T*>(child);//if node with name already exists, assign it to pointer
		return false;
	}
}

template <class T>
bool CustomScene3501::add_as_child(T* &pointer, String name, bool search){
	// this is the default behaviour
	// added the search parameter so that we can skip the slow "find_child" call during runtime
	if(search == false){
		pointer->set_name(name);
		add_child(pointer);
		pointer->set_owner(get_tree()->get_edited_scene_root());
		return true;
	}

	// always only have to search once if we save it here
	Node* child = find_child(name);
	
	// if the node hasn't been added to the SceneTree yet
	if(child == nullptr){
		pointer->set_name(name);
		add_child(pointer);
		pointer->set_owner(get_tree()->get_edited_scene_root());
		return true;
	}
	// if we are grabbing the existent one, clean up the memory to the new one that was just made and passed as an argument
	else{
		if(pointer == nullptr){
			UtilityFunctions::print("There is a nullptr being passed to add_as_child...");
		}
		else{
			memdelete(pointer);
		}
		pointer = dynamic_cast<T*>(child);
		return false;
	}
}


/*
*
* The usual container class added to the demos. This one should be used to create a racetrack.
*
* Copyright (c) 2024 Samantha Beilman (samanthabeilman@cmail.carleton.ca)
*
*/