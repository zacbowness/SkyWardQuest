#include "custom_scene_3501.h"
#include <godot_cpp/core/memory.hpp> // for memnew
#include <godot_cpp/classes/random_number_generator.hpp>


using namespace godot;

void CustomScene3501::_bind_methods() { }

CustomScene3501::CustomScene3501() : Node3D() {
	time_passed = 0.0;
}

CustomScene3501::~CustomScene3501() {}

void CustomScene3501::_enter_tree (){
	if(DEBUG) UtilityFunctions::print("Enter Tree - CustomScene3501."); 

	//Add Nodes to Scene
	create_and_add_as_child<Player>(player, "Player");

	create_and_add_as_child<Slime>(slime, "Test Slime");

	create_and_add_as_child<Map>(map,"Map");

	init_debug_rects();//add temp rect meshes to scene
}

void CustomScene3501::init_debug_rects(){
	Node* rectGroup;
	create_and_add_as_child<Node>(rectGroup, "Debug Rect Group");//create grouping node
	create_rect(Vector3(1,1,1), Vector3(0,2,-5), rectGroup, "Test Cube", Vector3(0.8, 0.1, 0.1));
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
	
	//Update DebugRect objects to set their location and otherwise
	for(DebugRect* obj : rect_instances){obj->update_rect();}
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


/*
*
* The usual container class added to the demos. This one should be used to create a racetrack.
*
* Copyright (c) 2024 Samantha Beilman (samanthabeilman@cmail.carleton.ca)
*
*/