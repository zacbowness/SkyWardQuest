#ifndef POWERUP_H
#define POWERUP_H

#include <godot_cpp/classes/node3d.hpp>
#include <godot_cpp/classes/sphere_mesh.hpp>

#include <godot_cpp/variant/utility_functions.hpp>

#include <godot_cpp/classes/mesh_instance3d.hpp>
#include <godot_cpp/godot.hpp>
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/classes/engine.hpp>

namespace godot {
class Powerup : public  MeshInstance3D{
	GDCLASS(Powerup, MeshInstance3D);

protected:
	static void _bind_methods();

private:

public:
	Powerup();
	~Powerup();
};

}

#endif