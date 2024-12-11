#ifndef BEE_H
#define BEE_H

#include <godot_cpp/classes/node3d.hpp>
#include <godot_cpp/classes/sphere_mesh.hpp>
#include <godot_cpp/classes/box_mesh.hpp>
#include <godot_cpp/classes/box_shape3d.hpp>

#include <godot_cpp/variant/utility_functions.hpp>

#include <godot_cpp/classes/mesh_instance3d.hpp>
#include <godot_cpp/godot.hpp>
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/classes/engine.hpp>
#include <godot_cpp/classes/Ray_Cast3D.hpp>
#include <vector>

#include "friendly.h"
#include "flower.h"
#include "bee_part.h"
#include "bee_fullBody.h"
#include "bee_eyes.h"
#include "bee_leftwing.h"
#include "bee_rightwing.h"


namespace godot {

class QuatCamera;
class BeeBody;
class Bee : public  Friend{
	GDCLASS(Bee, Friend);

protected:
	static void _bind_methods();
	
enum State {
    IDLE, //Will Stand Still But if a Player enters its range it will Chase
    WANDER, //Random Walks around if there is a Player in Range it will Chase
    CHASE //Follow the Last Seen Position in a Radius of a Player
};


private:
	const float height_from_ground = 2.0f;

	BeeBody* body; 
	BeeEye* eye1; 
	BeeEye* eye2; 
	BeeLWing* wing1; 
	BeeRWing* wing2; 
	RayCast3D* RayCast;
	//Vector of Every Flower
	//std::vector<Flower*> flowerVector;

	bool checkForPlayer();
	void chasePlayer();
	void init_body();
	void approachDirection(Vector3, double) override;
	//inline float distanceFromFlower(Flower* flower){return get_position().distance_to(flower->get_position());}
	//bool flowerInRadius();
	
	

	Vector3 calculateMovement(Vector3 direction, Vector3 velocity, double delta);
	State beeState = WANDER;
	//Flower* closestFlower = nullptr;
	

public:
	Bee();
	~Bee();

	void _enter_tree() override;
    void _ready() override;
	void _process(double delta) override;
	void setFlowerVector(std::vector<Flower*>);
	std::vector<Flower*> getFlowerVector();

	template <class T>
	// returns true if pointer is brand-new; false if retrieved from SceneTree
	bool create_and_add_as_child_parent(T* &pointer, String name, bool search, BeePart* parent, String parentName, Vector3 changePos){
	// this is the default behaviour
	// added the search parameter so that we can skip the slow "find_child" call during runtime (not applicable to this demo, you should always use search = true until next assignment)
	if(search == false){
		pointer = memnew(T);
		pointer->set_name(name);
		add_child(pointer);
		pointer->set_owner(get_tree()->get_edited_scene_root());
		pointer->set_parent(parent);
		pointer->set_local_position(changePos);
		return true;
	}

	// always only have to search once if we save it here
	Node* child = find_child(name);
	Node* parentNode = find_child(parentName);
	
	if(child == nullptr){
		pointer = memnew(T);
		pointer->set_name(name);
		add_child(pointer);
		pointer->set_owner(get_tree()->get_edited_scene_root());
		pointer->set_parent(parent);
		pointer->set_local_position(changePos);
		return true;
	}
	else{
		pointer = dynamic_cast<T*>(child);
		pointer->set_parent(parent);
		pointer->set_local_position(changePos);
		return false;
	}
}

template <class T>
// returns true if pointer is brand-new; false if retrieved from SceneTree
bool create_and_add_as_child(T* &pointer, String name, bool search){
	// this is the default behaviour
	// added the search parameter so that we can skip the slow "find_child" call during runtime (not applicable to this demo, you should always use search = true until next assignment)
	if(search == false){
		pointer = memnew(T);
		pointer->set_name(name);
		add_child(pointer);
		pointer->set_owner(get_tree()->get_edited_scene_root());
		return true;
	}

	// always only have to search once if we save it here
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

};

}

#endif