#include "bee_yellowBody.h"

using namespace godot;


void BeeYBody::_bind_methods() {
}

BeeYBody::BeeYBody() : BeePart() { 
	// This is just to line them up for the starting scene -- change this for sure. 
}

BeeYBody::~BeeYBody(){
	// Add cleanup here, if you have any. I don't, typically. 
}

void BeeYBody::_enter_tree ( ) {
	//Set up 3 Box Meshes 
	BoxMesh* yellowBody = memnew(BoxMesh);
    yellowBody->set_size(Vector3(0.25, 0.25, 0.25));
	

	StandardMaterial3D* material = memnew(StandardMaterial3D);
	material->set_albedo(Color(1, 1, 0, 1));
	yellowBody->surface_set_material(0, material);

	set_mesh(yellowBody);
}

// You may not unset this class as top level (from parent)

void BeeYBody::_process(double delta){
	set_global_transform(get_transformation_matrix());  
}

/*
*
* A class derived from CranePart.
*
* Copyright (c) 2024 Samantha Beilman (samanthabeilman@cmail.carleton.ca)
*
*/