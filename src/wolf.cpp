#include "wolf.h"
#include <godot_cpp/classes/resource_loader.hpp>

//Math for Random Point
#include <cmath>
#include <cstdlib>
#include <ctime>

using namespace godot;

void Wolf::_bind_methods() {}

Wolf::Wolf() {
	//Inherited From Npc
	speed = 2.0f;
	detectionRadius = 7.0f;
	enemyType = WOLF;
	WolfState = IDLE;
	aggroRadius = 7.0f;
	destination = Vector3(0,0,0);
}

Wolf::~Wolf() {}

void Wolf::_enter_tree(){
	
	//Initalizes The Children that makes up a Wolf 
	create_or_add_child<MeshInstance3D>(npc_mesh, "Wolf Mesh");
	create_or_add_child<CollisionShape3D>(npc_body, "Wolf Body");

}

void Wolf::_ready (){
	//Initalize Wolf to be a Sphere Mesh Based Maybe (Softbody)	
	init_body();
}

void Wolf::_process(double delta){
	if (Engine::get_singleton()->is_editor_hint()) return; // Early return if we are in editor
	switch (WolfState)
	{
	
	//Idle State
	//Sets Velocity to 0,0,0 and Switches States to Chase or Wander
	case IDLE:
		set_velocity(Vector3(0,0,0));
		if (playerInRadius()){
			WolfState = CHASE;
		} else {
			WolfState = WANDER;
		}
		break;
	//Wander State
	//Walks to the Destination once it reaches it will swap to a random Destination within 10 Radius
	case WANDER:
		//checks if the player is in range
		if (playerInRadius()){
			WolfState = CHASE; 
		} else {
			//Implement A Wandering Algorithm
			//If the Enemy is within 2.0f Radius of its destination get a random destination
			if (inRadiusFromDest(2.0f)){
				destination = getRandomPointInRadius(10.0f);
			}
			//Approach its Destination
			direction = destination - get_position();
			approachDirection(direction, delta);
		}
		
		break;
	//Chase State
	//Finds Player and Chases It
	case CHASE: 
		//Checks if the player is in the Aggro Range if not idle
		if (distanceFromPlayer() >= aggroRadius){
			WolfState = IDLE;
		} else {
			//Sets destination to Player's Position 
			destination = player->get_position();
			direction = (destination - get_position() );
			//Approach the direction of the player
			approachDirection(direction, delta);
		}
		break;
	
	
	}
}

void Wolf::init_body(){
	String dir = "res://mesh_assets/Wolf/";
	mesh_filepath = dir + "Wolf.res";
	texture_filepaths;
	create_or_add_child<MeshInstance3D>(npc_mesh, "Slime Mesh");
	init_mesh();
	init_collider();
}

//Sets Poisition Of Wolf 
void Wolf::approachDirection(Vector3 direction, double delta){
	Vector3 velocity = get_velocity();
	velocity = calculateMovement(direction.normalized(), velocity, delta);

	//Apply Gravity
	if(!is_on_floor())velocity.y -= GRAVITY*delta; //if Wolf is not on the ground, apply gravity
	if(is_on_floor()&&velocity.y<0)velocity.y = 0.0f; //if Wolf is falling and hits the ground->stop downward momentum

	move_and_slide(); //move and slide allows for smoother movement on non flat surfaces
	set_velocity(velocity);
}

Vector3 Wolf::calculateMovement(Vector3 direction, Vector3 curr_vel, double delta){
	
	
	Vector3 velocity = Vector3(0,0,0);
	
	//Calculates and Moves in the Direction of the Destination
	velocity = moveInDirection(direction, velocity, delta);

	Vector3 target_velocity = velocity.normalized()*speed;
	
	Vector3 previous_velocity = Vector3(curr_vel.x, 0, curr_vel.z);

	//Apply latteral movement interpolation
	velocity = previous_velocity.lerp(target_velocity, delta);

	//maintain y velocity from previous frame
	velocity.y = curr_vel.y;

	return velocity;
}

