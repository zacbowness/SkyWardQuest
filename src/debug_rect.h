#ifndef POWERUP_H
#define POWERUP_H

#include <godot_cpp/classes/node3d.hpp>
#include <godot_cpp/variant/utility_functions.hpp>

#include <godot_cpp/classes/standard_material3d.hpp>
#include <godot_cpp/classes/box_mesh.hpp>
#include <godot_cpp/classes/box_shape3d.hpp>
#include <godot_cpp/classes/mesh_instance3d.hpp>
#include <godot_cpp/classes/static_body3d.hpp>
#include <godot_cpp/classes/collision_shape3d.hpp>

#include "collision_obj.h"

namespace godot {
class DebugRect : public  CollisionObject{
	GDCLASS(DebugRect, CollisionObject);

protected:
	static void _bind_methods();

	

private:
	Vector3 scale;
	Color color;
	Vector3 position;

	StandardMaterial3D* material;
	CollisionShape3D* collision_shape;

public:
	DebugRect();
	~DebugRect();

	void _enter_tree() override;
	void _ready() override;

	StaticBody3D* init_collider() override;//initialize and return StaticBody3D for this object
	Mesh* init_mesh()override;//initialize and return mesh for this object
	

	void setup_rect(Vector3 scale, Vector3 pos);
	void setup_rect(Vector3 scale, Vector3 pos, Vector3 color);
	void update_rect();
	void set_color(Vector3 color);
};

}

#endif