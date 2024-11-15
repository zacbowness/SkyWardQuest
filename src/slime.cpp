#include "slime.h"
#include <godot_cpp/classes/resource_loader.hpp>


using namespace godot;

void Slime::_bind_methods() {}

Slime::Slime() {
	//Inherited From Enemy
	speed = 10.0f;
	radius = 10.0f;
	enemyType = SLIME;
}

Slime::~Slime() {}

void Slime::_ready (){
	//Initalize Slime to be a Sphere Mesh Based Maybe (Softbody)
	//Create Sphere and Mesh
	SphereMesh* sphere = memnew(SphereMesh);
    sphere->set_height(2.0f);
	sphere->set_radius(1.0f);

	StandardMaterial3D* material = memnew(StandardMaterial3D);
	material->set_albedo(Color(0, 0, 1, 1));
	sphere->surface_set_material(0, material);
	set_mesh(sphere);
	set_position(Vector3(0,5,0));
}

void Slime::_process(double delta){
	if (playerInRadius()){
		approachPlayer(delta);
	}
}