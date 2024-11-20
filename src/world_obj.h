#ifndef WORLD_OBJ_H
#define WORLD_OBJ_H

#include <godot_cpp/classes/node3d.hpp>
#include <godot_cpp/variant/utility_functions.hpp>
#include <godot_cpp/classes/mesh_instance3d.hpp>
#include <godot_cpp/godot.hpp>
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/classes/engine.hpp>
#include <godot_cpp/classes/scene_tree.hpp>

#include "defs.h"

namespace godot {
class WorldObject : public  MeshInstance3D{
	GDCLASS(WorldObject, MeshInstance3D);

protected:
	static void _bind_methods();
	Mesh* object_mesh;

	//Virtual Functions to override
	virtual Mesh* init_mesh(){return nullptr;}//function returns the mesh for the object and is set in _ready()

private:
	

public:
	WorldObject();
	~WorldObject();

	void _enter_tree() override;

	//Getters
	Mesh* get_object_mesh(){return object_mesh;}


	//create_or_add_child() functions need to be defined in this header file to please the compiler for some reason
	//Dont take it up with me take it up with the compiler

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

}//namespace end

#endif