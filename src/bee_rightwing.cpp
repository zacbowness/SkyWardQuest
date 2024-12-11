#include "bee_rightwing.h"

using namespace godot;


void BeeRWing::_bind_methods() {
}

BeeRWing::BeeRWing() : BeePart() { 
	// This is just to line them up for the starting scene -- change this for sure. 
}

BeeRWing::~BeeRWing(){
	// Add cleanup here, if you have any. I don't, typically. 
}

void BeeRWing::_enter_tree ( ) {
	//Set up 1 Box Meshes 
	BoxMesh* Wing = memnew(BoxMesh);
    Wing->set_size(Vector3(0.70, 0.003, 0.25));
	
	StandardMaterial3D* material = memnew(StandardMaterial3D);
	material->set_albedo(Color(1, 1, 1, 1));
	Wing->surface_set_material(0, material);

	set_mesh(Wing);
}

// You may not unset this class as top level (from parent)

void BeeRWing::_process(double delta){
	set_global_transform(get_transformation_matrix());  
	float angle = (sin(timePassed) * 0.25f);
	set_local_rotation(Quaternion(1, 0, 0, angle));
	timePassed += delta * 25.0;
}

/*
*
* A class derived from CranePart.
*
* Copyright (c) 2024 Samantha Beilman (samanthabeilman@cmail.carleton.ca)
*
*/