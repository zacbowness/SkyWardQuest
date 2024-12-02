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
	if(object_mesh==nullptr){
		mesh = init_mesh();//get mesh from init_mesh() defined by child objects
		object_mesh = mesh;
	}
	
}




