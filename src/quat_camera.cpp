#include "quat_camera.h"
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/classes/mesh.hpp>
#include <godot_cpp/classes/node3d.hpp>
#include <godot_cpp/classes/engine.hpp>
#include <godot_cpp/classes/input_event.hpp>
#include <godot_cpp/classes/input_event_mouse_motion.hpp>
#include <godot_cpp/core/class_db.hpp>

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
	//Viewport* viewport = Engine::get_singleton()->get_main_viewport();
	//last_mouse_position = get_viewport();
}

QuatCamera::~QuatCamera() {
	// Add your cleanup here.
}

void QuatCamera::_process(double delta){
	if (Engine::get_singleton()->is_editor_hint()||GameOver) return; // Early return if we are in editor

	// you can speed up by changing these, if desired. 
	float rotation_factor = PLAYER_SENSITIVITY;
	float translation_factor = top_speed;
	
	//Handle Forward Movement
	//set position every frame even if no input
	//set_position(get_position() + GetForward() * delta * translation_factor * throttle);
	
	//Movement
	Input* _input = Input::get_singleton();
	

	//Looking Around

	//Detect Mouse Inputs

	bool restrict_up = false;
	bool restrict_down = false;
	//UtilityFunctions::print(Math::rad_to_deg(GetForward().angle_to(Vector3(0,1,0))));

	if(angle_diff(GetForward(), Vector3(0,1,0)) <= 10.0) restrict_up = true;
	if(angle_diff(GetForward(), Vector3(0,-1,0)) <= 15.0) restrict_down = true;

	//restrict_pitch = false;
	
	if(_input->is_action_pressed("look_up")&&!restrict_up){
		Pitch(1.0f * delta * rotation_factor);
	}
	if(_input->is_action_pressed("look_down")&&!restrict_down){
		Pitch(-1.0f * delta * rotation_factor);
	}
}

float QuatCamera::angle_diff(Vector3 vec1, Vector3 vec2){
	return Math::rad_to_deg(vec1.angle_to(vec2));
}

Vector3 QuatCamera::GetForward(void) const {
    Vector3 current_forward = (our_quaternion.xform(forward_));
    return -current_forward.normalized(); // Return -forward since the camera coordinate system points in the opposite direction
}


Vector3 QuatCamera::GetSide(void) const {
	//replaced static vector with value derrived from current rotation quaternion
    Vector3 current_side = (our_quaternion.xform(side_));
    return current_side.normalized();
}


Vector3 QuatCamera::GetUp(void) const {
    //replaced static up vector with vector derrived from our current rotation by using cross product
	//to get the local up vector based on our current forward anf side facing vectors
    Vector3 current_up = GetForward().cross(GetSide().normalized());
    return -current_up.normalized();
}


void QuatCamera::Pitch(float angle){
    Quaternion rotation = Quaternion(GetSide(), angle);//create a quaternion, rotated by angle around side axis
	Quaternion new_quat = rotation * our_quaternion;//make new quaternion that takes current orientation and multiplies it by our new quaternion to rotate it
	our_quaternion = new_quat.normalized();//set our_quaternion to a normalized version of the new one
	set_quaternion((rotation*get_quaternion()).normalized());
}


void QuatCamera::Yaw(float angle){
    Quaternion rotation = Quaternion(Vector3(0,1,0),angle);
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