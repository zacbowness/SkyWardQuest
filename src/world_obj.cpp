#include "world_obj.h"
#include <godot_cpp/classes/resource_loader.hpp>


using namespace godot;

void WorldObject::_bind_methods() {}

WorldObject::WorldObject() {
	object_mesh = nullptr;
}

WorldObject::~WorldObject() {}

void WorldObject::_enter_tree(){
	
	Mesh* mesh = nullptr;
	mesh = init_mesh();//get mesh from init_mesh() defined by child objects
	if(mesh == nullptr){if(DEBUG) UtilityFunctions::print("ERROR - Mesh is nullptr (init_mesh() invalid)");}//give error output
	else{
		object_mesh = mesh;//object_mesh is the permenent place to store the pointer to this object's mesh
	}
}




