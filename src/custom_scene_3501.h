#ifndef CUSTOM_SCENE_H
#define CUSTOM_SCENE_H

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
#include "quat_camera.h"
#include "enemy.h"
#include "debug_rect.h"
#include "player_scene.h"
#include "slime.h"
#include "map.h"
#include "particle_system.h"
#include "asset_importer.h"
#include "prop.h"
#include "skybox.h"
#include "portal.h"
#include "portal_effect.h"
#include "collectable.h"
#include "tower.h"
#include "mountain.h"

//Enemies 
#include "bee.h"
#include "wolf.h"
#include "slime.h"

//LOCAL DEFINITIONS
#define NUM_TERRAIN_PROPS 60


// everything in gdextension is defined in this namespace
namespace godot {
class CustomScene3501 : public Node3D {
    // this macro sets up a few internal things
	GDCLASS(CustomScene3501, Node3D);

private:
	double time_passed;

	Player* player;
	Slime* slime;
	Map* map;
	Skybox* skybox;
	PortalEffect* portal_effect;
	Portal* portal;
	Tower* tower;
	Mountain* mountain;

	Vector<ParticleSystem*> particle_systems;
	Vector<Collectable*> collectableList;
	Vector<MeshInstance3D*> objects;
	Vector<Npc*> NpcList;
	
	Vector<DebugRect*> rect_instances;
	Vector<Prop*> prop_instances;
	Vector<Prop*> terrain_prop_instances;

	Vector3 collectible_1_pos;
	Vector3 collectible_2_pos;
	Vector3 collectible_3_pos;
	
	enum SpawnNPC{
		SlimeNpc,
		WolfNpc,
		BeeNpc
	};
	
	//Setup Functions
	void init_debug_rects();
	void create_rect(Vector3 size, Vector3 pos, Node* parentNode, String name);
	void create_rect(Vector3 size, Vector3 pos, Node* parentNode, String name, Vector3 color);

	void init_player(Vector3 start_pos);

	void init_props();
	void create_prop(Vector3 size, Vector3 pos, Node* parentNode, String obj_name, String mesh_filepath, Vector<String> texture_filepaths);
    void create_prop(Vector3 size, Vector3 pos, Vector3 rotation, Node* parentNode, String obj_name, String mesh_filepath, Vector<String> texture_filepaths);//Polymorph that takes rotation
    void create_terrain_prop(Vector3 size, Vector3 rotation, Node* parentNode, String obj_name, String mesh_filepath, Vector<String> texture_filepaths);
	void update_terrain_props(Vector<Vector3> pos_vect);
	void update_terrain_enemies(Vector<Vector3> pos_vect);

	//Other Creation Functions
	void createCollectable(Vector3 pos, String name);
	void createPortal(Vector3 pos);
	void create_npc(SpawnNPC type, Vector3 pos, Node* parentNode, String name);
	void collectibles_in_scene();

	Dictionary mesh_filepaths;//Hash Map for mesh filepaths
	Dictionary texture_filepaths;//Hash Map for texture filepaths
	void load_filepaths();

	void init_enemies();

	

protected:
    // a static function that Godot will call to find out which methods can be called and which properties it exposes
	static void _bind_methods();

public:
	CustomScene3501();
	~CustomScene3501();

	void _process(double delta) override;
	void _enter_tree ( ) override;
	void _ready ( ) override;

	//Takes in The Node Name, Name of the Shader File, Name of the Texture File, Size and Position to make a particle System
	void create_particle_system(String node_name, String shader_name, String texture_name, Vector2 size, Vector3 pos, int32_t amount_in, double lifetime_in);

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
	bool create_or_add_child(T* &pointer, String name, Node* parent){
		
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