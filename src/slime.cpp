#include "slime.h"
#include <godot_cpp/classes/resource_loader.hpp>

//Math for Random Point
#include <cmath>
#include <cstdlib>
#include <ctime>

using namespace godot;

void Slime::_bind_methods() {}

Slime::Slime() {
	//Inherited From Npc
	speed = 1.5f;
	detectionRadius = 5.0f;
	enemyType = SLIME;
	slimeState = IDLE;
	aggroRadius = 10.0f;
	destination = Vector3(0,0,0);
}

Slime::~Slime() {}

void Slime::_enter_tree(){
	//Initalizes The Children that makes up a Slime 
	import_tool = memnew(AssetImporter);
	init_body();
}

void Slime::_ready (){
	//Initalize Slime to be a Sphere Mesh Based Maybe (Softbody)	
	
}

void Slime::_process(double delta){
	if (Engine::get_singleton()->is_editor_hint()) return; // Early return if we are in editor
	switch (slimeState)
	{
	
	//Idle State
	//Sets Velocity to 0,0,0 and Switches States to Chase or Wander
	case IDLE:
		set_velocity(Vector3(0,0,0));
		if (playerInRadius()){
			slimeState = CHASE;
		} else {
			slimeState = WANDER;
		}
		break;
	//Wander State
	//Walks to the Destination once it reaches it will swap to a random Destination within 10 Radius
	case WANDER:
		//checks if the player is in range
		if (playerInRadius()){
			slimeState = CHASE; 
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
			slimeState = IDLE;
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

void Slime::init_body(){
	String dir = "res://mesh_assets/Slime/";
	mesh_filepath = dir + "slime.res";
	texture_filepaths = {dir + "Slime_SlimeBody_Texture_Cyan.png", dir + "Slime_SlimeEyes_Texture.png", dir + "Slime_SlimeTooth_Texture.png"};
	create_or_add_child<MeshInstance3D>(npc_mesh, "Slime Mesh");
	init_mesh();
	init_collider();
}

//Sets Poisition Of Slime 
void Slime::approachDirection(Vector3 direction, double delta){
	Vector3 velocity = get_velocity();
	velocity = calculateMovement(direction.normalized(), velocity, delta);

	//Apply Gravity
	if(!is_on_floor())velocity.y -= GRAVITY*delta; //if Slime is not on the ground, apply gravity
	if(is_on_floor()&&velocity.y<0)velocity.y = 0.0f; //if Slime is falling and hits the ground->stop downward momentum

	move_and_slide(); //move and slide allows for smoother movement on non flat surfaces
	set_velocity(velocity);
}

Vector3 Slime::calculateMovement(Vector3 direction, Vector3 curr_vel, double delta){
	
	
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

