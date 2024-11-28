#include "Flower.h"
#include <godot_cpp/classes/resource_loader.hpp>


using namespace godot;

void Flower::_bind_methods() {}

Flower::Flower() {
	//Inherited From Npc

}

Flower::~Flower() {}

void Flower::_enter_tree(){
	
	//Initalizes The Children that makes up a Slime 
	
	// create_or_add_child<MeshInstance3D>(npc_mesh, "Flower Mesh");
	// create_or_add_child<CollisionShape3D>(npc_body, "Flower Body");

}

void Flower::_ready (){
	//Initalize Flower's Body
	//init_body();
}

void Flower::_process(double delta){
	if (Engine::get_singleton()->is_editor_hint()) return; // Early return if we are in editor
}

// void Flower::init_body(){
// 	//Create Sphere and Mesh
// 	BoxMesh* boxMesh = memnew(BoxMesh);
//     boxMesh->set_size(Vector3(0.5f,0.5f,0.5f));

// 	StandardMaterial3D* material = memnew(StandardMaterial3D);
// 	material->set_albedo(Color(0, 0, 1, 1));
// 	boxMesh->surface_set_material(0, material);
// 	npc_mesh->set_mesh(boxMesh);

// 	//Create Sphere Colider 
// 	BoxShape3D* boxColider = memnew(BoxShape3D);
// 	npc_body->set_shape(boxColider);	
// }