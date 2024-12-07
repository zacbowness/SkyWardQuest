#include "defs.h"
#include "Portal.h"

#include <godot_cpp/classes/resource_loader.hpp>
#include <godot_cpp/variant/utility_functions.hpp> // for the debug statements
#include <godot_cpp/classes/engine.hpp>
#include <godot_cpp/classes/scene_tree.hpp>



using namespace godot;

void Portal::_bind_methods() {
	// Allows us to use the Body_Entered Function of the Area3D
    ClassDB::bind_method(D_METHOD("body_entered", "body"), &Portal::body_entered);
}

Portal::Portal() : Area3D() {
	time_passed = 0.0;
}

Portal::~Portal(){

}

void Portal::_enter_tree ( ){
	if(DEBUG) UtilityFunctions::print("Enter Tree - Portal."); 
	
    set_monitoring(true);  // Enable monitoring of overlapping bodies

	create_or_add_child<MeshInstance3D>(Portal_mesh, "Portal Mesh");
	create_or_add_child<CollisionShape3D>(Portal_body, "Portal Body");
}

void Portal::_ready ( ){
	if(DEBUG) UtilityFunctions::print("Ready - Portal."); 

	//Connects the body_entered signal from Area3D to the Function
	//of the Portal so it is always in use 
	connect("body_entered", Callable(this, "body_entered"));

	init_body();
}

void Portal::_process(double delta){
	if (Engine::get_singleton()->is_editor_hint()) return; // Early return if we are in editor

	//Make a Statement that switches the Portal on when there is 3 collectables collected 

}
void Portal::body_entered(Node3D *body) {
    if (body == player && player->getCollectable() == 3) {
        UtilityFunctions::print("Game Over");
    }
}

void Portal::init_body(){
	//Create Sphere and Mesh
	SphereMesh* sphereMesh = memnew(SphereMesh);
    sphereMesh->set_height(2.0f);
	sphereMesh->set_radius(1.0f);

	StandardMaterial3D* material = memnew(StandardMaterial3D);
	material->set_albedo(Color(0, 0, 0, 1));
	sphereMesh->surface_set_material(0, material);
	Portal_mesh->set_mesh(sphereMesh);

	//Create Sphere Colider 
	SphereShape3D* sphereColider = memnew(SphereShape3D);
	sphereColider->set_radius(1.0);
	Portal_body->set_shape(sphereColider);	
}