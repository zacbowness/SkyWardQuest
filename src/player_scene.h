#ifndef PLAYER_SCENE_H
#define PLAYER_SCENE_H

#include <godot_cpp/classes/node3d.hpp>

//Misc
#include <godot_cpp/classes/engine.hpp>
#include <godot_cpp/classes/resource_loader.hpp>
#include <godot_cpp/classes/scene_tree.hpp>
#include <godot_cpp/variant/utility_functions.hpp>

//Datatypes & Transforms
#include <godot_cpp/variant/quaternion.hpp>
#include <godot_cpp/variant/vector3.hpp>
#include <godot_cpp/variant/color.hpp>
#include <godot_cpp/variant/transform3d.hpp>
#include <godot_cpp/templates/vector.hpp> // GODOT EQUIVALENT TO std::vector !!!! 

//Meshes, Textures, and Shapes
#include <godot_cpp/classes/mesh_instance3d.hpp>
#include <godot_cpp/classes/cylinder_mesh.hpp>
#include <godot_cpp/classes/box_mesh.hpp>
#include <godot_cpp/classes/standard_material3d.hpp>
#include <godot_cpp/classes/color_rect.hpp>
#include <godot_cpp/classes/collision_shape3d.hpp>
#include <godot_cpp/classes/capsule_shape3d.hpp>
#include <godot_cpp/classes/character_body3d.hpp>

//Input
#include <godot_cpp/classes/input_event.hpp>
#include <godot_cpp/classes/input.hpp>
#include <godot_cpp/variant/rect2.hpp> // for viewport size
#include <godot_cpp/classes/canvas_item.hpp> // for viewport size
#include <godot_cpp/classes/control.hpp> // for the anchors preset
#include <godot_cpp/classes/quad_mesh.hpp>
#include <godot_cpp/classes/standard_material3d.hpp>
#include <godot_cpp/classes/shader_material.hpp>
#include <godot_cpp/classes/shader.hpp>

//Screen Effects
#include <godot_cpp/classes/quad_mesh.hpp>
#include <godot_cpp/classes/shader_material.hpp>

//File Inclusions
#include "defs.h"
#include "quat_camera.h"

//Definitions
#define PLAYER_HEIGHT 1.6f
#define PLAYER_EYELINE 1.4f
#define PLAYER_RADIUS 0.35f


// everything in gdextension is defined in this namespace
namespace godot {
class Player : public CharacterBody3D {
    // this macro sets up a few internal things
	GDCLASS(Player, CharacterBody3D);

private:
	double time_passed;
	int collectableAmount = 0;

	//Object Pointers
	QuatCamera* main_camera;
	MeshInstance3D* player_mesh;
	CollisionShape3D* player_body;
	
	Quaternion player_quat;
	Vector3 forward_;
	Vector3 side_;

	Vector2 perspective_change;

	// Fixed-size array of shaders
	std::array<godot::Ref<godot::Shader>, 1> shaders;
	// Index of the shader in the current array
	int current_shader_index;

	Vector<Ref<Shader>> effect_array;

	Vector<String> effect_shaders = {
		"earthquake" //At Location 0...
	};

	QuadMesh* screen_mesh;

	//Screen Shader
	MeshInstance3D* screen_quad_instance;
	ShaderMaterial* screen_space_shader_material;


protected:
    // a static function that Godot will call to find out which methods can be called and which properties it exposes
	static void _bind_methods();

	//Initialization functions
	void init_camera();
	void init_body();

	Vector3 apply_input(Vector3 velocity, double delta);
	Vector3 move_in_direction(Vector3 dir, Vector3 velocity);
	void player_look(Vector2 input, double delta);//change the direction the player is looking
	void turn_player(float angle);//for rotation left and right
	Vector3 get_forward();
	Vector3 get_side();
	

public:
	Player();
	~Player();

	void _process(double delta) override;
	void _enter_tree ( ) override;
	void _ready ( ) override;

	void init_screen_effects();

	void setEffectScreen(int);

	void resetEffectScreen();

	inline int getCollectable(){return collectableAmount;}
	inline void setCollectable(int newAmount){collectableAmount = newAmount;}



	//GETTER AND SETTER FUNCTIONS
	CollisionShape3D* get_collider(){return player_body;}

	// Loads the shaders and adds them to the shaders array
	void load_shaders();


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

};

}

#endif