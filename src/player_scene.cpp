#include "player_scene.h"
#include <godot_cpp/core/memory.hpp> // for memnew
#include <godot_cpp/classes/random_number_generator.hpp>


using namespace godot;

void Player::_bind_methods() {}

Player::Player() : CharacterBody3D() {
	time_passed = 0.0;
	player_quat = Quaternion(Vector3(0, 0, 1), 0.0f);
}

Player::~Player() {}

void Player::_enter_tree (){
	if(DEBUG) UtilityFunctions::print("Enter Tree - Player.");

	//Add & Create Child Nodes
	create_or_add_child<QuatCamera>(main_camera, "First Person Camera");
	create_or_add_child<MeshInstance3D>(player_mesh, "Player Mesh");
	create_or_add_child<CollisionShape3D>(player_body, "Player Body");

}

void Player::_ready ( ){
	if(DEBUG) UtilityFunctions::print("Ready - Player.");
	//Init Quaternion
	forward_ = Vector3(get_global_transform().basis[0][2], get_global_transform().basis[1][2], get_global_transform().basis[2][2]);
	side_ = Vector3(get_global_transform().basis[0][0], get_global_transform().basis[1][0], get_global_transform().basis[2][0]);

	//Run initialization functions
	init_camera();
	init_body();
}

// called every frame (as often as possible)
void Player::_process(double delta) {
	if (Engine::get_singleton()->is_editor_hint()) return; // Early return if we are in editor
	time_passed += delta;

	//Current velocity vector
	Vector3 velocity = get_velocity();
	velocity = apply_input(velocity, delta);
	
	
	//Apply Gravity
	if(!is_on_floor())velocity.y -= GRAVITY*delta;//if player is not on the ground, apply gravity
	if(is_on_floor()&&velocity.y<0)velocity.y = 0.0f;//if player is falling and hits the ground->stop downward momentum
	if(!is_on_floor()&&is_on_ceiling()&&velocity.y>0)velocity.y = 0.0f;//if player jumps and hits a ceiling->stop upward momentum
	//else velocity.y = 0.0;

	//Apply Velocity To Player
	//if(PLAYER_DEBUG&&DEBUG)UtilityFunctions::print(velocity);
	move_and_slide();//move and slide allows for smoother movement on non flat surfaces
	set_velocity(velocity);
}

//==== INITIALIZATION FUNCTIONS ====//

void Player::init_camera(){
	main_camera->set_position(Vector3(0.0f, PLAYER_EYELINE, 0.0f));
	main_camera->_ready();
}

void Player::init_body(){
	//INITIALIZE MESH & MATERIAL
	CylinderMesh* cylinder = memnew(CylinderMesh);
	StandardMaterial3D* material = memnew(StandardMaterial3D);
	material->set_albedo(Color(0.4,0.4,0.4));//Color of player mesh
	cylinder->surface_set_material(0, material);
	
	//mesh sizing
	cylinder->set_top_radius(PLAYER_RADIUS);
	cylinder->set_bottom_radius(PLAYER_RADIUS);
	cylinder->set_height(PLAYER_HEIGHT);

	player_mesh->set_mesh(cylinder);
	//Place properly with feet on the ground
	player_mesh->set_position(Vector3(0.0, PLAYER_HEIGHT/2, 0));

	//INITIALIZE COLLIDER
	CapsuleShape3D* capsule = memnew(CapsuleShape3D);
	capsule->set_radius(PLAYER_RADIUS);
	capsule->set_height(PLAYER_HEIGHT);
	player_body->set_shape(capsule);
	player_body->set_position(Vector3(0.0, PLAYER_HEIGHT/2, 0.0));//place so that player origin is on the ground
}

//==== MOVEMENT AND TRANSFORMATION FUNCTIONS ====//
Vector3 Player::apply_input(Vector3 current_vel, double delta){
	Vector3 velocity = Vector3(0,0,0);

	Input* _input = Input::get_singleton();//get input singleton
	if(CURSOR_LOCK) _input->set_mouse_mode(Input::MOUSE_MODE_CAPTURED);//Lock Cursor

	//Mouse Inputs
	Vector2 mouse_input = _input->get_last_mouse_velocity()*-1;
	main_camera->pitch_camera(mouse_input.y, delta);
	turn_player(mouse_input.x * delta * PLAYER_SENSITIVITY);
	
	//Movement Inputs
	if(_input->is_action_pressed("move_forward")){
		velocity = move_in_direction(get_forward(), velocity, delta);
	}
	if(_input->is_action_pressed("move_backward")){
		velocity = move_in_direction(-get_forward(), velocity, delta);
	}
	if(_input->is_action_pressed("move_right")){
		velocity = move_in_direction(get_side(), velocity, delta);
	}
	if(_input->is_action_pressed("move_left")){
		velocity = move_in_direction(-get_side(), velocity, delta);
	}

	bool has_input = false;
	if(
		_input->is_action_pressed("move_forward")||
		_input->is_action_pressed("move_backward")||
		_input->is_action_pressed("move_right")||
		_input->is_action_pressed("move_left")
	)has_input = true;

	Vector3 target_velocity = velocity.normalized()*PLAYER_SPEED;
	
	Vector3 previous_velocity = Vector3(current_vel.x, 0, current_vel.z);

	//Decide how aggresive the lateral movement interpolation should be based on the following factors
	float control_value;
	if(is_on_floor())control_value = PLAYER_ACCEL;//If on ground maintain good control
	else if(has_input) control_value = PLAYER_AIR_CONTROL;//if off ground and giving input maintain some control
	else control_value = PLAYER_AIR_FRICTION;//if off ground with no input maintain little control (dont slow lateral movement much)
	
	//Apply latteral movement interpolation
	velocity = previous_velocity.lerp(target_velocity, delta*control_value);

	//maintain y velocity from previous frame
	velocity.y = current_vel.y;

	//jump
	if(_input->is_action_just_pressed("jump")&&is_on_floor()){
		velocity.y+=PLAYER_JUMP_STR;
	}

	//Turning/looking around inputs for arrow keys
	if(_input->is_action_pressed("look_right")){
		turn_player(-1.0f * delta * PLAYER_SENSITIVITY);
	}
	if(_input->is_action_pressed("look_left")){
		turn_player(1.0f * delta * PLAYER_SENSITIVITY);
	}

	if(DEBUG&&PLAYER_DEBUG) UtilityFunctions::print(_input->Input::get_last_mouse_velocity());

	return velocity;
}

Vector3 Player::move_in_direction(Vector3 dir, Vector3 velocity, double delta){

	//Scale up speed by 60 to have PLAYER_SPEED be similar to other movement constants
	//delta value is likely to be about 1/60 if the game is running at 60fps, so rescale accordingly
	float speed_factor = PLAYER_SPEED*60.0f;
	
	//velocity.x += dir.x*speed_factor*delta;
	//velocity.z += dir.z*speed_factor*delta;
	velocity.x += dir.x;
	velocity.z += dir.z;

	//apply speed factor and delta after velocity direction is applied so that diagonal movement is the same speed as forward
	return velocity;
}

Vector3 Player::get_forward(){
    Vector3 current_forward = (player_quat.xform(forward_));
    return -current_forward.normalized(); // Return -forward since the camera coordinate system points in the opposite direction
}

Vector3 Player::get_side(){
	//replaced static vector with value derrived from current rotation quaternion
    Vector3 current_side = (player_quat.xform(side_));
    return current_side.normalized();
}

void Player::turn_player(float angle){
	Quaternion rotation = Quaternion(Vector3(0,1,0),angle);
    Quaternion new_quat = rotation * player_quat;
	player_quat = (new_quat.normalized());
    set_quaternion((rotation * get_quaternion()).normalized());	// we need to keep the internal quaternion separate from our quaternion representation
}


/*
*
* Copyright (c) 2024 Samantha Beilman (samanthabeilman@cmail.carleton.ca)
*
*/