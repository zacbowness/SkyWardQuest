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

//LOCAL DEFINITIONS
#define NUM_TERRAIN_PROPS 20


// everything in gdextension is defined in this namespace
namespace godot {
class Mountain : public Node3D {
    // this macro sets up a few internal things
	GDCLASS(Mountain, Node3D);

private:
	double time_passed;
	Map* map;

protected:
    // a static function that Godot will call to find out which methods can be called and which properties it exposes
	static void _bind_methods();

public:
	Mountain();
	~Mountain();

	void _process(double delta) override;
	void _enter_tree ( ) override;
	void _ready ( ) override;

	template <class T>
	// returns true if pointer is brand-new; false if retrieved from SceneTree
	bool create_and_add_as_child(T* &pointer, String name){

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
	bool create_and_add_as_child_of_Node(T* &pointer, String name, Node* parent){
		
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
	bool add_as_child(T* &pointer, String name, bool search){
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

};

}

#endif