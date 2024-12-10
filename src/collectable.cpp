#include "defs.h"
#include "collectable.h"

#include <godot_cpp/classes/resource_loader.hpp>
#include <godot_cpp/variant/utility_functions.hpp> // for the debug statements
#include <godot_cpp/classes/engine.hpp>
#include <godot_cpp/classes/scene_tree.hpp>



using namespace godot;

void Collectable::_bind_methods() {
	// Allows us to use the Body_Entered Function of the Area3D
    ClassDB::bind_method(D_METHOD("body_entered", "body"), &Collectable::body_entered);
}

Collectable::Collectable() : Area3D() {
	time_passed = 0.0;
}

Collectable::~Collectable(){

}

void Collectable::_enter_tree ( ){
	if(DEBUG) UtilityFunctions::print("Enter Tree - Collectable."); 
	
    set_monitoring(true);  // Enable monitoring of overlapping bodies

	create_or_add_child<MeshInstance3D>(collectable_mesh, "Collectable Mesh");
	create_or_add_child<CollisionShape3D>(collectable_body, "Collectable Body");
}

void Collectable::_ready ( ){
	if(DEBUG) UtilityFunctions::print("Ready - Collectable."); 

	//Connects the body_entered signal from Area3D to the Function
	//of the Collectable so it is always in use 
	connect("body_entered", Callable(this, "body_entered"));

	init_body();
}

void Collectable::_process(double delta){
	if (Engine::get_singleton()->is_editor_hint()) return; // Early return if we are in editor

}

void Collectable::body_entered(Node3D *body) {
    if (body == player) {
        player->setCollectable(player->getCollectable() + 1);
		UtilityFunctions::print(player->getCollectable());
		collectable_mesh->set_visible(false);
        collectable_body->call_deferred("set_disabled", true);
		
	}
}

void Collectable::init_body(){
	//Create Sphere and Mesh
	SphereMesh* sphereMesh = memnew(SphereMesh);
    sphereMesh->set_height(2.0f);
	sphereMesh->set_radius(1.0f);

	StandardMaterial3D* material = memnew(StandardMaterial3D);
	material->set_albedo(Color(0, 0, 1, 1));
	sphereMesh->surface_set_material(0, material);
	collectable_mesh->set_mesh(sphereMesh);

	//Create Sphere Colider 
	SphereShape3D* sphereColider = memnew(SphereShape3D);
	sphereColider->set_radius(1.0);
	collectable_body->set_shape(sphereColider);	
}