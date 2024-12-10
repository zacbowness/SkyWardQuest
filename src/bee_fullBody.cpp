#include "bee_fullBody.h"



using namespace godot;


void BeeBody::_bind_methods() {
}

BeeBody::BeeBody() : BeePart() { 
	// This is just to line them up for the starting scene -- change this for sure. 
}

BeeBody::~BeeBody(){
	// Add cleanup here, if you have any. I don't, typically. 
}

void BeeBody::_enter_tree ( ) {
	if(DEBUG) UtilityFunctions::print("Enter Tree - Bee Body.");
	//Set up 3 Box Meshes 
	create_and_add_as_child<BeeYBody>(yellowBody1, "Yellow Body 1", true);
	create_and_add_as_child<BeeYBody>(yellowBody2, "Yellow Body 2", true);
	create_and_add_as_child<BeeBBody>(blackBody1, "Black Body 1", true);
	yellowBody1->set_local_position(Vector3(0.25, 0, 0));
	yellowBody2->set_local_position(Vector3(-0.25, 0, 0));
}

// You may not unset this class as top level (from parent)

void BeeBody::_process(double delta){
	set_global_transform(get_transformation_matrix());  
	Vector3 position = get_global_position();
    set_global_position(position);
}

/*
*
* A class derived from CranePart.
*
* Copyright (c) 2024 Samantha Beilman (samanthabeilman@cmail.carleton.ca)
*
*/