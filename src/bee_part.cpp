#include "bee_part.h"


using namespace godot;

void BeePart::_bind_methods() {}

BeePart::BeePart() : MeshInstance3D(), parent(nullptr) {
	time_passed = 0.0;

	// primary attributes
	local_position = Vector3();
	local_rotation = Quaternion();

	joint_position = Vector3(0, 0, 0);
	orbit_rotation = Quaternion();

	scale = Vector3(1, 1, 1);

	// this makes it so that any hierarchy established in the node structure does not apply to the hierarchical transformations done by Godot for us, which would interfere
	set_as_top_level(true); // DO NOT CHANGE THIS LINE
}

BeePart::~BeePart(){
	// Add cleanup here, if you have any. I don't, typically. 
}

void BeePart::_enter_tree ( ){
	if(DEBUG) UtilityFunctions::print("Enter Tree - Bee_Part."); 
}

// Since most of the Bee_part use the default hierarchical transformation, we can just use the parent class's implementation (this one); the hook will need to be overridden
void BeePart::_ready ( ){
	if(DEBUG) UtilityFunctions::print("Ready - ", get_name()); // since this will be called by many of the parts

	set_global_transform(get_transformation_matrix());  
}

void BeePart::set_parent(BeePart* par){
	this->parent = par;
}

BeePart* BeePart::get_parent(){
	return parent;
}

// This function is specifically for use as a parent for hierarchical transformations. 
Transform3D BeePart::get_transformation_matrix(){	

	Transform3D translation = Transform3D().translated(local_position);
	Transform3D orbit = Transform3D(); 
	Transform3D rotation = Transform3D(local_rotation);
	Transform3D scaling = Transform3D().scaled(scale);
	// UtilityFunctions::print(get_name()); 

	Transform3D local_transform = translation * orbit * rotation * scaling;

	return (get_parent() == nullptr)? local_transform : parent->get_transformation_matrix_without_scaling() * local_transform; // for hierarchical transformations, we typically leave scaling off
}

// You usually don't want to encorporate the parent's scaling.
Transform3D BeePart::get_transformation_matrix_without_scaling(){	
	Transform3D translation = Transform3D().translated(local_position);
	Transform3D orbit = Transform3D(); 
	Transform3D rotation = Transform3D(local_rotation);
	// UtilityFunctions::print(get_name()); 

	Transform3D local_transform = translation * orbit * rotation;

	return (get_parent() == nullptr)? local_transform : parent->get_transformation_matrix_without_scaling() * local_transform; // for hierarchical transformations, we typically leave scaling off
}


#pragma region SIMPLE GETTERS & SETTERS
Vector3 BeePart::get_local_position(){
	return local_position;
}

void BeePart::set_local_position(Vector3 input){
	local_position = input;
}

Quaternion BeePart::get_local_rotation(){
	return local_rotation;
}

void BeePart::set_local_rotation(Quaternion input){
	local_rotation = input;
}

Vector3 BeePart::get_scale(){
	return scale;
}

void BeePart::set_scale(Vector3 input){
	scale = input;
}

Quaternion BeePart::get_orbit_rotation(){
	return orbit_rotation;
}

void BeePart::set_orbit_rotation(Quaternion input){
	orbit_rotation = input;
}

Vector3 BeePart::get_joint_position(){
	return joint_position;
}

void BeePart::set_joint_position(Vector3 input){
	joint_position = input;
}
#pragma endregion SIMPLE GETTERS & SETTERS

/*
*
* A class which acts as the parent class for all of the Bee_part parts used to build a toy Bee_part. Specifically allows students to do the hierarchical transformations themselves. 
*
* Copyright (c) 2024 Samantha Beilman (samanthabeilman@cmail.carleton.ca)
*
*/