#ifndef SLIME_H
#define SLIME_H

#include <godot_cpp/classes/node3d.hpp>
#include <godot_cpp/classes/sphere_mesh.hpp>

#include <godot_cpp/variant/utility_functions.hpp>

#include <godot_cpp/classes/mesh_instance3d.hpp>
#include <godot_cpp/classes/sphere_shape3d.hpp>
#include <godot_cpp/godot.hpp>
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/classes/engine.hpp>
#include "enemy.h"

enum State {
    IDLE, //Will Stand Still But if a Player enters its range it will Chase
    WANDER, //Random Walks around if there is a Player in Range it will Chase
    CHASE //Follow the Last Seen Position in a Radius of a Player
};

namespace godot {

class QuatCamera;
class Slime : public  Enemy{
	GDCLASS(Slime, Enemy);

protected:
	static void _bind_methods();
	


private:
	bool checkForPlayer();
	void chasePlayer();
	void init_body();
	
	

public:
	Slime();
	~Slime();

	void _enter_tree ( ) override;
    void _ready() override;
	void _process(double delta) override;

};

}

#endif