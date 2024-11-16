#ifndef COLLISION_OBJ_H
#define COLLISION_OBJ_H

//Parent Class Already Has These (Left For Clarity)
#include <godot_cpp/classes/node3d.hpp>
#include <godot_cpp/variant/utility_functions.hpp>
#include <godot_cpp/classes/mesh_instance3d.hpp>
#include <godot_cpp/godot.hpp>
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/classes/engine.hpp>

//New Inclusions
#include <godot_cpp/classes/static_body3d.hpp>
#include <godot_cpp/classes/collision_shape3d.hpp>

#include "world_obj.h"

namespace godot {
class CollisionObject : public  WorldObject{
	GDCLASS(CollisionObject, WorldObject);

protected:
	static void _bind_methods();

	virtual StaticBody3D* init_collider(){return nullptr;}//bogus definition to please the compiler

private:
	StaticBody3D* object_collider;

public:
	CollisionObject();
	~CollisionObject();

	void _enter_tree()override;

	//Getters
	StaticBody3D* get_collider(){return object_collider;}
};

}

#endif