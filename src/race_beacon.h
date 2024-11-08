#ifndef RACEBEACON_H
#define RACEBEACON_H

#include <godot_cpp/classes/node3d.hpp>
#include <godot_cpp/classes/sphere_mesh.hpp>

#include <godot_cpp/variant/utility_functions.hpp>

#include <godot_cpp/classes/mesh_instance3d.hpp>
#include <godot_cpp/godot.hpp>
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/classes/engine.hpp>

namespace godot {
class RaceBeacon : public  MeshInstance3D{
	GDCLASS(RaceBeacon, MeshInstance3D);

protected:
	static void _bind_methods();

private:
	bool isNextBeacon;

public:
	RaceBeacon();
	~RaceBeacon();

	bool isNext(){return isNextBeacon;}
	void set_as_next(){isNextBeacon = true;}
};

}

#endif