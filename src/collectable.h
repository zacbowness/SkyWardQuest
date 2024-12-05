#ifndef COLLECTABLE_H
#define COLLECTABLE_H

#include <godot_cpp/classes/node.hpp>
#include <godot_cpp/classes/node3d.hpp>
#include <godot_cpp/classes/mesh_instance3d.hpp>
#include <godot_cpp/classes/standard_material3d.hpp>
#include <godot_cpp/classes/shader_material.hpp>
#include <godot_cpp/classes/sphere_mesh.hpp>
#include <godot_cpp/classes/area3d.hpp>
#include <godot_cpp/classes/collision_shape3d.hpp>
#include <godot_cpp/core/memory.hpp> // for memnew
#include <godot_cpp/variant/vector3.hpp>
#include <godot_cpp/classes/sphere_shape3d.hpp>
#include "player_scene.h"


// everything in gdextension is defined in this namespace
namespace godot {
class Collectable : public Area3D {
	GDCLASS(Collectable, Area3D);

private:
	double time_passed; // maybe you don't need this, just an example
	void init_body();
	MeshInstance3D* collectable_mesh;
	CollisionShape3D* collectable_body;
	Player* player; 
	
protected:
	static void _bind_methods();

public:
	Collectable();
	~Collectable();
	
	void _enter_tree ( ) override;
	void _ready ( ) override;
	void _process(double delta) override;
	void body_entered(Node3D*);
	inline Player* getPlayer(){return player;}
	inline void setPlayer(Player* newPlayer){player = newPlayer;}

	// the return type represents whether it existed already; true if it is brand-new; false if it was retrieved from the SceneTree
	// search defines whether the scenetree should be checked for an instance
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