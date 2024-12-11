#ifndef NPC_H
#define NPC_H

#include <godot_cpp/classes/node3d.hpp>
#include <godot_cpp/classes/sphere_mesh.hpp>
#include <godot_cpp/variant/utility_functions.hpp>
#include <godot_cpp/classes/mesh_instance3d.hpp>
#include <godot_cpp/godot.hpp>
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/classes/engine.hpp>
#include <godot_cpp/classes/standard_material3d.hpp>
#include <godot_cpp/classes/shader_material.hpp>
#include <godot_cpp/classes/scene_tree.hpp>
#include <godot_cpp/classes/character_body3d.hpp>
#include <godot_cpp/classes/collision_shape3d.hpp>
#include <godot_cpp/core/memory.hpp> // for memnew
#include <godot_cpp/classes/static_body3d.hpp>
#include <godot_cpp/classes/array_mesh.hpp>
#include <godot_cpp/classes/concave_polygon_shape3d.hpp>
#include <godot_cpp/classes/shape3d.hpp>
#include "defs.h"
#include "asset_importer.h"
#include "player_scene.h"



namespace godot {

enum NpcType{
	ENEMY,
	FRIENDLY
};

class CharacterBody3D;
class Npc : public  CharacterBody3D{
	GDCLASS(Npc, CharacterBody3D);

protected:
	static void _bind_methods();
	float speed;	
	float detectionRadius;
	virtual void approachDirection(Vector3, double);
	Player* player;
	enum NpcType type;
	MeshInstance3D* npc_mesh;
	CollisionShape3D* npc_body;
	Vector3 direction;
	Vector3 destination;
	Vector3 startPos;
	Vector3 scale = Vector3(1.0,1.0,1.0);
	
	Vector3 moveInDirection(Vector3 dir, Vector3 velocity, double delta);
	inline float distanceFromPlayer(){return get_position().distance_to(player->get_position());}
	inline bool inRadiusFromDest(float radius){return get_position().distance_to(destination) <= radius;}
	Vector3 getRandomPointInRadius(float radius);
	
	//Mesh Importer
	AssetImporter* import_tool;
	String mesh_filepath;
	Vector<String> texture_filepaths;
	Ref<ArrayMesh> obj_mesh;


	enum State {
    IDLE, //Will Stand Still But if a Player enters its range it will Chase
    WANDER, //Random Walks around if there is a Player in Range it will Chase
    CHASE //Follow the Last Seen Position in a Radius of a Player
	};


private:	
	bool GameOver;
	
public:
	Npc();
	~Npc();

	void _process(double delta) override;	
	void setPlayerPointer(Player* player);
	inline Player* getPlayerPointer(){return player;}
	void game_over() {GameOver = true;}
	//Checks if the player is within Radius
	//Uses the detectionRadius of the NPC
	bool playerInRadius();
	//Checks if you are in a certain radius of your destination
	void update_npc();
	void update_npc_position(Vector3 position);

	inline void setStartPos(Vector3 new_pos){startPos = new_pos;}
	inline void setScale(Vector3 new_scale){scale = new_scale;}

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