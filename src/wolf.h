#ifndef WOLF_H
#define WOLF_H

#include <godot_cpp/classes/node3d.hpp>
#include <godot_cpp/classes/sphere_mesh.hpp>

#include <godot_cpp/variant/utility_functions.hpp>

#include <godot_cpp/classes/mesh_instance3d.hpp>
#include <godot_cpp/classes/sphere_shape3d.hpp>
#include <godot_cpp/godot.hpp>
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/classes/engine.hpp>
#include "enemy.h"

namespace godot {

class QuatCamera;
class Wolf : public  Enemy{
	GDCLASS(Wolf, Enemy);

protected:
	static void _bind_methods();
	void approachDirection(Vector3, double) override;
	Vector3 calculateMovement(Vector3 direction, Vector3 velocity, double delta);


private:
	bool checkForPlayer();
	void chasePlayer();
	void init_body();
	State WolfState;
	
	
	

public:
	Wolf();
	~Wolf();

	void _enter_tree ( ) override;
    void _ready() override;
	void _process(double delta) override;

};

}

#endif