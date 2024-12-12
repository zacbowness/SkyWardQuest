#include "bee.h"
#include <godot_cpp/classes/resource_loader.hpp>


using namespace godot;

void Bee::_bind_methods() {}

Bee::Bee() {
	//Inherited From Npc
	speed = 2.5f;
	detectionRadius = 5.0f;
	enemyType = BEE;
	destination = getRandomPointInRadius(10.0f);
}

Bee::~Bee() {}

void Bee::_enter_tree(){
	//Initalize Bee's Body
	init_body();
}

void Bee::_ready (){
	set_position(startPos);
}

void Bee::_process(double delta){
	if (Engine::get_singleton()->is_editor_hint()) return; // Early return if we are in editor
	RayCast->set_position(get_position());

	float cur_y = destination.y;
	// Check Ray Cast
	if (RayCast->is_colliding()) {
		// Get Point Of Ray Cast
        Vector3 floor_position = RayCast->get_collision_point();
        
		// Set New Position
        Vector3 new_position = get_position();
        new_position.y = floor_position.y + height_from_ground;  
		cur_y = new_position.y;
    } else {
		cur_y = get_position().y - 0.1;
	}
	
	if (inRadiusFromDest(2.0f) || firstRun == true){
		destination = getRandomPointInRadius(10.0f);
		firstRun = false;
	}
	destination.y = cur_y;
	//Approach its Destination
	direction = destination - get_position();
	approachDirection(direction, delta);
	body->set_local_position((get_position()));
}

void Bee::init_body(){
	//Create Bee Parts
	create_and_add_as_child<BeeBody>(body, "Bee Body", true);
	create_and_add_as_child_parent(eye1, "Bee Eye 1", true, body, "Bee Body", Vector3(0.4, 0.075, 0.075));
	create_and_add_as_child_parent(eye2, "Bee Eye 2", true, body, "Bee Body", Vector3(0.4, 0.075, -0.075));
	create_and_add_as_child_parent(wing1, "Bee Wing 1", true, body, "Bee Body", Vector3(0.0, 0.0, 0.150));
	create_and_add_as_child_parent(wing2, "Bee Wing 2", true, body, "Bee Body", Vector3(0.0, 0.0, -0.150));
	
	// Initalize Ray Cast
	create_and_add_as_child<RayCast3D>(RayCast, "RayCast", true);
	RayCast->set_position(Vector3(0,0,0));
	RayCast->set_target_position(Vector3(0,-1,0));
	RayCast->set_scale(Vector3(get_scale().x, height_from_ground, get_scale().z));
}

//Sets The Direction the Bee wants to approach in
void Bee::approachDirection(Vector3 direction, double delta){
	look_at(direction, Vector3(0,1,0));
	Vector3 velocity = get_velocity();
	velocity = calculateMovement(direction.normalized(), velocity, delta);

	//Maybe Apply Gravity 

	move_and_slide(); //move and slide allows for smoother movement on non flat surfaces
	set_velocity(velocity);
}

Vector3 Bee::calculateMovement(Vector3 direction, Vector3 curr_vel, double delta){
	
	
	Vector3 velocity = Vector3(0,0,0);
	
	//Calculates and Moves in the Direction of the Destination
	velocity = moveInDirection(direction, velocity, delta);
	velocity.y += direction.y * delta;

	Vector3 target_velocity = velocity.normalized()*speed;
	
	Vector3 previous_velocity = Vector3(curr_vel.x, curr_vel.y, curr_vel.z);

	//Apply latteral movement interpolation
	velocity = previous_velocity.lerp(target_velocity, delta);

	return velocity;
}
