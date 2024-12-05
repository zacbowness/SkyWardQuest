#include "populate_mesh.h"
#include <godot_cpp/core/memory.hpp> // for memnew
#include <godot_cpp/classes/random_number_generator.hpp>


using namespace godot;

void Populatemesh::_bind_methods() { }

Populatemesh::Populatemesh() : Node3D() {
	time_passed = 0.0;
	load_filepaths();//load filepaths into hashmaps
}

Populatemesh::~Populatemesh() {}

void Populatemesh::_enter_tree (){
	if(DEBUG) UtilityFunctions::print("Enter Tree - PopulateMesh added."); 

	//init_props();		//add props to scene
}

//load filepaths into hashmaps of important resources
//USE UNIQUE KEY VALUES
void Populatemesh::load_filepaths(){
	String dir = "res://mesh_assets/";
	
	//MESH FILEPATHS//
	mesh_filepaths["OakTree_1"] = dir+"tree_mesh1.res";
	mesh_filepaths["OakTree_2"] = dir+"tree_mesh2.res";

	//TEXTURE FILEPATHS//
	texture_filepaths["OakLeaf_1"] = dir+"OakTreeLeaf.png";
	texture_filepaths["OakTrunk_1"] = dir+"OakTreeTrunk.png";
}


void Populatemesh::init_props(){

	Node* terrainPropGroup;
	create_and_add_as_child(terrainPropGroup, "Terrain Props");

	String tree_textures[] = {texture_filepaths["OakLeaf_1"], texture_filepaths["OakTrunk_1"]};

	create_prop(Vector3(10,10,10), Vector3(5,5,0), terrainPropGroup,"Test Tree", String(mesh_filepaths["OakTree_1"]), tree_textures, 2);
	create_prop(Vector3(10,10,10), Vector3(-5,5,0), terrainPropGroup,"Test Tree 2", String(mesh_filepaths["OakTree_2"]), tree_textures, 2);
}

void Populatemesh::_ready ( ){
	if(DEBUG) UtilityFunctions::print("Ready - CustomScene3501.");
	
}

// called every frame (as often as possible)
void Populatemesh::_process(double delta) {
	if (Engine::get_singleton()->is_editor_hint()) return; // Early return if we are in editor

	time_passed += delta;
}

Prop* Populatemesh::create_prop(Vector3 size, Vector3 pos, Node* parentNode, String obj_name, String mesh_filepath, String texture_filepath_arr[], int num_textures) {
    Prop* prop;
    bool isNew = create_and_add_as_child_of_Node<Prop>(prop, obj_name, parentNode);
    if (isNew) {
        prop->setup_prop(pos, size, mesh_filepath, texture_filepath_arr, num_textures, obj_name);
        prop_instances.push_back(prop);
    }
    return prop; // Return the created or retrieved prop
}

void Populatemesh::scatter_props(Node *parent, const Vector<Vector<float>> &heightfield, int width, int height, float scale, int prop_count) {
    String tree_textures[] = {texture_filepaths["OakLeaf_1"], texture_filepaths["OakTrunk_1"]};

	for (int i = 0; i < sizeof(tree_textures) / sizeof(tree_textures[0]); i++) {
    UtilityFunctions::print("tree_textures[", i, "]: ", tree_textures[i]);
	}

    
    if (heightfield.is_empty() || heightfield[0].is_empty()) {
        UtilityFunctions::print("Heightfield is not generated.");
        return;
    }

    RandomNumberGenerator *rng = memnew(RandomNumberGenerator);
    rng->randomize();

    for (int i = 0; i < prop_count; ++i) {
        // Randomly select a position on the heightfield
        int x = rng->randf_range(0, width - 1);
        int y = rng->randf_range(0, height - 1);
        float terrain_height = heightfield[y][x];

        // Calculate the world position for the prop
        Vector3 position = Vector3(x * scale, terrain_height + 0.5, y * scale);

        Prop* prop = create_prop(Vector3(10,10,10), Vector3(-5,5,0), parent,"Test Tree 2", String(mesh_filepaths["OakTree_2"]), tree_textures, 2);

        create_and_add_as_child_of_Node(prop,"prop",parent);
    }

    memdelete(rng);
}

template <class T>
// returns true if pointer is brand-new; false if retrieved from SceneTree
bool Populatemesh::create_and_add_as_child(T* &pointer, String name){

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
bool Populatemesh::create_and_add_as_child_of_Node(T* &pointer, String name, Node* parent){
	
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