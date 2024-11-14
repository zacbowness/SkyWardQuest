#ifndef POWERUP_H
#define POWERUP_H

#include <godot_cpp/classes/node3d.hpp>
#include <godot_cpp/classes/sphere_mesh.hpp>

#include <godot_cpp/variant/utility_functions.hpp>

#include <godot_cpp/classes/mesh_instance3d.hpp>
#include <godot_cpp/classes/standard_material3d.hpp>
#include <godot_cpp/classes/box_mesh.hpp>
#include <godot_cpp/classes/scene_tree.hpp>

#include <godot_cpp/godot.hpp>
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/classes/engine.hpp>

namespace godot {
class DebugRect : public  MeshInstance3D{
	GDCLASS(DebugRect, MeshInstance3D);

protected:
	static void _bind_methods();

private:
	Vector3 scale;
	Color color;
	Vector3 position;

	StandardMaterial3D* material;

public:
	DebugRect();
	~DebugRect();
	void _enter_tree ( ) override;

	void setup_rect(Vector3 scale, Vector3 pos);
	void update_rect();
	void set_color(Vector3 color);
};

}

#endif