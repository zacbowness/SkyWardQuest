#ifndef BEE_H
#define BEE_H

#include <godot_cpp/classes/node3d.hpp>
#include <godot_cpp/classes/sphere_mesh.hpp>
#include <godot_cpp/classes/box_mesh.hpp>
#include <godot_cpp/classes/box_shape3d.hpp>

#include <godot_cpp/variant/utility_functions.hpp>

#include <godot_cpp/classes/mesh_instance3d.hpp>
#include <godot_cpp/godot.hpp>
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/classes/engine.hpp>

#include <vector>

#include "friendly.h"
#include "flower.h"


enum State {
    IDLE, //Will Stand Still But if a Player enters its range it will Chase
    WANDER, //Will Randomly Move But Overtime scan more of the area for a flower
    CHASE, //Will Go to the Flower it Finds and Gathers when it arrives
	GATHER //Will stay at the flower and produce pollen partacles then leave
};

namespace godot {

class QuatCamera;
class Bee : public  Friend{
	GDCLASS(Bee, Friend);

protected:
	static void _bind_methods();
	


private:
	//Vector of Every Flower
	std::vector<Flower*> flowerVector;

	bool checkForPlayer();
	void chasePlayer();
	void init_body();
	void approachDirection(Vector3, double) override;
	inline float distanceFromFlower(Flower* flower){return get_position().distance_to(flower->get_position());}
	bool flowerInRadius();
	
	Vector3 calculateMovement(Vector3 direction, Vector3 velocity, double delta);
	State beeState = IDLE;
	Flower* closestFlower = NULL;
	

public:
	Bee();
	~Bee();

	void _enter_tree() override;
    void _ready() override;
	void _process(double delta) override;
	void setFlowerVector(std::vector<Flower*>);
	std::vector<Flower*> getFlowerVector();

};

}

#endif