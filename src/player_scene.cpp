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
	if(!is_on_floor())velocity.y -= GRAVITY*delta;
	//else velocity.y = 0.0;

	//Apply Velocity
	move_and_slide();
	set_velocity(velocity);
	//UtilityFunctions::print(velocity);
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
	Vector3 velocity = current_vel;

	Input* _input = Input::get_singleton();//get input singleton
	if(_input->is_action_pressed("move_forward")){
		velocity = move_in_direction(get_forward(), velocity, delta);
		//UtilityFunctions::print("Forward");
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
	return velocity;
}

Vector3 Player::move_in_direction(Vector3 dir, Vector3 velocity, double delta){
	velocity.x = dir.x*PLAYER_SPEED*delta;
	velocity.z = dir.z*PLAYER_SPEED*delta;
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


/*
*
* Copyright (c) 2024 Samantha Beilman (samanthabeilman@cmail.carleton.ca)
*
*/