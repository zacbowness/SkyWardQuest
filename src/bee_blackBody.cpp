#include "bee_blackBody.h"

using namespace godot;


void BeeBBody::_bind_methods() {
}

BeeBBody::BeeBBody() : BeePart() { 
	// This is just to line them up for the starting scene -- change this for sure. 
}

BeeBBody::~BeeBBody(){
	// Add cleanup here, if you have any. I don't, typically. 
}

void BeeBBody::_enter_tree ( ) {
	//Set up 3 Box Meshes 
	BoxMesh* blackBody = memnew(BoxMesh);
    blackBody->set_size(Vector3(0.25, 0.25, 0.25));
	
	StandardMaterial3D* material = memnew(StandardMaterial3D);
	material->set_albedo(Color(0, 0, 0, 1));
	blackBody->surface_set_material(0, material);

	set_mesh(blackBody);
}

// You may not unset this class as top level (from parent)

void BeeBBody::_process(double delta){
	set_global_transform(get_transformation_matrix());  
}

/*
*
* A class derived from CranePart.
*
* Copyright (c) 2024 Samantha Beilman (samanthabeilman@cmail.carleton.ca)
*
*/