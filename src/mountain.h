#ifndef MOUNTAIN_H
#define MOUNTAIN_H

#include <godot_cpp/classes/node3d.hpp>

#include <godot_cpp/classes/engine.hpp>
#include <godot_cpp/classes/input.hpp>
#include <godot_cpp/classes/input_event.hpp>
#include <godot_cpp/classes/resource_loader.hpp>
#include <godot_cpp/classes/scene_tree.hpp>
#include <godot_cpp/variant/utility_functions.hpp>

#include <godot_cpp/variant/quaternion.hpp>
#include <godot_cpp/variant/vector3.hpp>
#include <godot_cpp/variant/color.hpp>
#include <godot_cpp/variant/transform3d.hpp>

#include <godot_cpp/templates/vector.hpp> // GODOT EQUIVALENT TO std::vector !!!! 

#include <godot_cpp/classes/sphere_mesh.hpp>
#include <godot_cpp/classes/cylinder_mesh.hpp>
#include <godot_cpp/classes/box_mesh.hpp>
#include <godot_cpp/classes/standard_material3d.hpp>

#include <godot_cpp/variant/rect2.hpp> // for viewport size
#include <godot_cpp/classes/canvas_item.hpp> // for viewport size
#include <godot_cpp/classes/control.hpp> // for the anchors preset
#include <godot_cpp/classes/color_rect.hpp>

//Default C++ Inclusions
#include <unordered_map>

#include "defs.h"
#include "map.h"
#include "prop.h"



namespace godot {
class Mountain : public Node3D {

	GDCLASS(Mountain, Node3D);

private:
	double time_passed;
	Map* map;

	//Vector of stored Prop Instances for platforms to jump on
	Vector<Prop*> prop_instances;

	//Filepath HashMaps
	Dictionary mesh_filepaths;
	Dictionary texture_filepaths;

	//Initialize props around the mountain for jump puzzle
	void build_props();
	
	//Instantiate a prop with the given parameters
	void make_prop(Vector3 pos, Vector3 scale, Vector3 rotation, String model_filepath, Vector<String> texture_filepaths, String name);
	//Plymorph function for meshes with only one texture (avoids making a vector for no reason)
	void make_prop(Vector3 pos, Vector3 scale, Vector3 rotation, String model_filepath, String texture_filepath, String name);

	void load_filepaths();//Load filepaths into dictionaries/hashmaps

protected:
    // a static function that Godot will call to find out which methods can be called and which properties it exposes
	static void _bind_methods();

public:
	Mountain();
	~Mountain();

	void _process(double delta) override;
	void _enter_tree ( ) override;
	void _ready ( ) override;

	//Function to add nodes as children to this one
	//Used to add objects like colliders & paraticle systems or any sub-objects under the one that calls this function
	template <class T>
	bool create_or_add_child(T* &pointer, String name){
		Node* child = find_child(name);//find node with the given name (NAME MUST BE UNIQUE)

		if(child == nullptr){//if child node was not found, create it
			pointer = memnew(T);
			pointer->set_name(name);
			this->add_child(pointer);
			pointer->set_owner(get_tree()->get_edited_scene_root());
			return true;
		} else {
			pointer = dynamic_cast<T*>(child);//if node with name already exists, assign it to pointer
			return false;
		}
	}

	//A Polymorph of the above function where a parent node is given
	//Use this if you want a node to be added underneath the given parent node in the scene tree
	template <class T>
	bool create_or_add_child(T* &pointer, String name, Node3D* parent){
		
		Node* child = find_child(name);//find node with the given name (NAME MUST BE UNIQUE)
		if(child == nullptr){//if child node was not found, create it
			pointer = memnew(T);
			pointer->set_name(name);
			parent->add_child(pointer);//Add node as child of given node
			pointer->set_owner(get_tree()->get_edited_scene_root());
			return true;
		} else {
			pointer = dynamic_cast<T*>(child);//if node with name already exists, assign it to pointer
			return false;
		}
	}
};
}

#endif