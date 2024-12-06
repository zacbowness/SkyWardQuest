#include "bee_eyes.h"

using namespace godot;


void BeeEye::_bind_methods() {
}

BeeEye::BeeEye() : BeePart() { 
	// This is just to line them up for the starting scene -- change this for sure. 
}

BeeEye::~BeeEye(){
	// Add cleanup here, if you have any. I don't, typically. 
}

void BeeEye::_enter_tree ( ) {
	//Set up 1 Box Meshes 
	BoxMesh* blackBody = memnew(BoxMesh);
    blackBody->set_size(Vector3(0.05, 0.05, 0.05));
	
	StandardMaterial3D* material = memnew(StandardMaterial3D);
	material->set_albedo(Color(0, 0, 0, 1));
	blackBody->surface_set_material(0, material);

	set_mesh(blackBody);
}

// You may not unset this class as top level (from parent)

void BeeEye::_process(double delta){
	set_global_transform(get_transformation_matrix());  
}

/*
*
* A class derived from CranePart.
*
* Copyright (c) 2024 Samantha Beilman (samanthabeilman@cmail.carleton.ca)
*
*/