#include "collision_obj.h"
#include <godot_cpp/classes/resource_loader.hpp>


using namespace godot;

void CollisionObject::_bind_methods() {}

CollisionObject::CollisionObject() {}

CollisionObject::~CollisionObject() {}

void CollisionObject::_enter_tree(){
	if(DEBUG) UtilityFunctions::print("Enter Tree - CollisionObject.");
	WorldObject::_enter_tree(); //call parent enter tree function to ensure it runs
	StaticBody3D* collider = nullptr;
	collider = init_collider();
	if(collider == nullptr){if(DEBUG) UtilityFunctions::print("ERROR - Collider is nullptr (init_collider() invalid return)");}//give error output
	else{
		object_collider = collider;
	}
}