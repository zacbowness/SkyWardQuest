#include "slime.h"
#include <godot_cpp/classes/resource_loader.hpp>


using namespace godot;

void Slime::_bind_methods() {}

Slime::Slime() {
	//Inherited From Npc
	speed = 10.0f;
	radius = 10.0f;
	enemyType = SLIME;
}

Slime::~Slime() {}

void Slime::_enter_tree(){
	
	//Initalizes The Children that makes up a Slime 
	create_or_add_child<MeshInstance3D>(npc_mesh, "Slime Mesh");
	create_or_add_child<CollisionShape3D>(npc_body, "Slime Body");

	//Initalizes Body
	
}

void Slime::_ready (){
	//Initalize Slime to be a Sphere Mesh Based Maybe (Softbody)	
	init_body();
}

void Slime::_process(double delta){
	if (Engine::get_singleton()->is_editor_hint()) return; // Early return if we are in editor
	if (playerInRadius()){
		approachPlayer(delta);
	}
}

void Slime::init_body(){
	//Create Sphere and Mesh
	SphereMesh* sphereMesh = memnew(SphereMesh);
    sphereMesh->set_height(2.0f);
	sphereMesh->set_radius(1.0f);

	StandardMaterial3D* material = memnew(StandardMaterial3D);
	material->set_albedo(Color(0, 0, 1, 1));
	sphereMesh->surface_set_material(0, material);
	npc_mesh->set_mesh(sphereMesh);

	//Create Sphere Colider 
	SphereShape3D* sphereColider = memnew(SphereShape3D);
	npc_body->set_shape(sphereColider);	
}