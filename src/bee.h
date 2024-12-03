#ifndef BEE_H
#define BEE_H

#include <godot_cpp/classes/node3d.hpp>
#include <godot_cpp/classes/sphere_mesh.hpp>

#include <godot_cpp/variant/utility_functions.hpp>

#include <godot_cpp/classes/mesh_instance3d.hpp>
#include <godot_cpp/godot.hpp>
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/classes/engine.hpp>
#include "friendly.h"

enum State {
    IDLE, //Will Stand Still But if a Player enters its range it will Chase
    WANDER, //Random Walks around if there is a Flower in Range it will Chase
    CHASE //Follow the Last Seen Position in a Radius of a Flower 
};

namespace godot {

class QuatCamera;
class Bee : public  Friend{
	GDCLASS(Bee, Friend);

protected:
	static void _bind_methods();
	


private:
	bool checkForPlayer();
	void chasePlayer();
	
	

public:
	Bee();
	~Bee();

    void _ready() override;
	void _process(double delta) override;

};

}

#endif