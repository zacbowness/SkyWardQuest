#include "quat_camera.h"
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/classes/mesh.hpp>
#include <godot_cpp/classes/engine.hpp>
#include <godot_cpp/classes/input_event.hpp>

using namespace godot;

void QuatCamera::_bind_methods() {}

QuatCamera::QuatCamera() : Camera3D() {
	// Initialize any variables here.
	our_quaternion = Quaternion(Vector3(0, 0, 1), 0.0f);
}

void QuatCamera::_enter_tree(){

}

void QuatCamera::_ready(){
	// this is the Godot-assisted equivalent of SetView
	// Setup the initial unit vectors for each
	// using this setup allows the user to set the position of the camera in the editor. 
	
	// Don't change this
	forward_ = Vector3(get_global_transform().basis[0][2], get_global_transform().basis[1][2], get_global_transform().basis[2][2]);
	side_ = Vector3(get_global_transform().basis[0][0], get_global_transform().basis[1][0], get_global_transform().basis[2][0]);
	// do not save _up as a member -- derive it. You will get a bad grade if you add it as a member variable like these two are. 

	throttle = 0.0f; //Initialize throttle to 0
	top_speed = 10.0f; //Initialize top speed at 10
	accel_factor = 0.005f; //initialize acceleration factor at 0.005f

	GameOver = false; //initialize game over bool
}

QuatCamera::~QuatCamera() {
	// Add your cleanup here.
}

void QuatCamera::_process(double delta){
	if (Engine::get_singleton()->is_editor_hint()||GameOver) return; // Early return if we are in editor

	// you can speed up by changing these, if desired. 
	float rotation_factor = 1.0f;	
	float translation_factor = top_speed;
	
	//Handle Forward Movement
	//set position every frame even if no input
	set_position(get_position() + GetForward() * delta * translation_factor * throttle);
	
	Input* _input = Input::get_singleton();
	if(_input->is_action_pressed("move_forward")){
		if(throttle < 1) throttle += accel_factor;// If throttle is less than 1.0f, increase it by acceleration factor
	}
	if(_input->is_action_pressed("move_backward")){
		if(throttle > 0) throttle -= 0.005f;// If throttle is more than 0, decrease it by acceleration factor
		else if(throttle < 0) throttle = 0.0f;
		//UtilityFunctions::print(throttle); //debug output
	}
	
	if(_input->is_action_pressed("move_right")){
		set_position(get_position() + GetSide() * delta * translation_factor);
	}
	if(_input->is_action_pressed("move_left")){
		set_position(get_position() - GetSide() * delta * translation_factor);
	}
	if(_input->is_action_pressed("move_up")){
		set_position(get_position() + GetUp() * delta * translation_factor);
	}
	if(_input->is_action_pressed("move_down")){
		set_position(get_position() - GetUp() * delta * translation_factor);
	}
	if(_input->is_action_pressed("yaw_increase")){
		Yaw(1.0f * delta * rotation_factor);
	}
	if(_input->is_action_pressed("yaw_decrease")){
		Yaw(-1.0f * delta * rotation_factor);
	}
	if(_input->is_action_pressed("pitch_increase")){
		Pitch(1.0f * delta * rotation_factor);
	}
	if(_input->is_action_pressed("pitch_decrease")){
		Pitch(-1.0f * delta * rotation_factor);
	}
	if(_input->is_action_pressed("roll_increase")){
		Roll(1.0f * delta * rotation_factor);
	}
	if(_input->is_action_pressed("roll_decrease")){
		Roll(-1.0f * delta * rotation_factor);
	}
}

Vector3 QuatCamera::GetForward(void) const {
    Vector3 current_forward = (our_quaternion.xform(forward_));
    return -current_forward.normalized(); // Return -forward since the camera coordinate system points in the opposite direction
}


Vector3 QuatCamera::GetSide(void) const {
	//replaced static vector with value derrived from current rotation quaternion
    Vector3 current_side = (our_quaternion.xform(side_));
    return current_side;
}


Vector3 QuatCamera::GetUp(void) const {
    //replaced static up vector with vector derrived from our current rotation by using cross product
	//to get the local up vector based on our current forward anf side facing vectors
    Vector3 current_up = GetForward().cross(GetSide().normalized());
    return -current_up.normalized();
}


void QuatCamera::Pitch(float angle){
	//The angle value is negative because I wanted the controlls to better allign with flight simulators *typically pitch controlls are inverted
    Quaternion rotation = Quaternion(GetSide(), -angle);//create a quaternion, rotated by angle around side axis
	Quaternion new_quat = rotation * our_quaternion;//make new quaternion that takes current orientation and multiplies it by our new quaternion to rotate it
	our_quaternion = new_quat.normalized();//set our_quaternion to a normalized version of the new one
	set_quaternion((rotation*get_quaternion()).normalized());
}


void QuatCamera::Yaw(float angle){
    Quaternion rotation = Quaternion(GetUp(),angle); // not the correct axis
    Quaternion new_quat = rotation * our_quaternion;
	our_quaternion = (new_quat.normalized());
    set_quaternion((rotation * get_quaternion()).normalized());	// we need to keep the internal quaternion separate from our quaternion representation
}


void QuatCamera::Roll(float angle){
    Quaternion rotation = Quaternion(GetForward(),angle); // what axis is used for rolling?
    Quaternion new_quat = rotation * our_quaternion;
	our_quaternion = (new_quat.normalized());
    set_quaternion((rotation * get_quaternion()).normalized());	// we need to keep the internal quaternion separate from our quaternion representation
}

/*
*
* A camera class which uses an internal quaternion representation to allow students to do motion calculations themselves. 
*
* Copyright (c) 2024 Samantha Beilman (samanthabeilman@cmail.carleton.ca)
* Code based on previous versions of COMP 3501 using OpenGL at Carleton. 
*
*/