#include "npc.h"
#include <godot_cpp/classes/resource_loader.hpp>
#include <godot_cpp/classes/mesh_instance3d.hpp>


#include "quat_camera.h"

using namespace godot;

void Npc::_bind_methods() {}

Npc::Npc() {GameOver = false;}

Npc::~Npc() {}

//pass a pointer to the player object to this enemy
void Npc::setPlayerPointer(CharacterBody3D* player){this->player = player;}

void Npc::_process(double delta){
	if (Engine::get_singleton()->is_editor_hint()||GameOver) return;
}

void Npc::approachDirection(Vector3 direction, double delta){}

bool Npc::playerInRadius(){
	//Checks if the Distance to the player is within the radius 
	return distanceFromPlayer() <= detectionRadius;
}

//Takes in Direction, Velocity
Vector3 Npc::moveInDirection(Vector3 dir, Vector3 velocity, double delta){
	velocity.x += dir.x;
	velocity.z += dir.z;

	return velocity;
}

Vector3 Npc::getRandomPointInRadius(float radius){
	float theta = static_cast<float>(rand()) / static_cast<float>(RAND_MAX) * 2.0f * Math_PI; //Insures its constrained to [0, 2Pi] 
    float r = sqrt(static_cast<float>(rand()) / static_cast<float>(RAND_MAX)) * radius; 
	return Vector3(r*cos(theta), get_position().y, r*sin(theta));
}

Mesh* Npc::init_mesh(){
    Ref<ArrayMesh> mesh;
	
	//Import mesh from file
	if(obj_mesh.is_null()){
		mesh = import_tool->import_mesh(mesh_filepath, texture_filepaths);
		obj_mesh = mesh;//Copy mesh to format collider later (we could use the mesh pointer this func returns but the conversions would be messy)
	}
	npc_mesh->set_mesh(obj_mesh);//apply the mesh
	return(*obj_mesh);//return mesh once initialized to be stored in WorldObject::_enter_tree()
}

void Npc::init_collider(){
	create_or_add_child<CollisionShape3D>(npc_body, "Collision Body");
	npc_body->set_shape(import_tool->shape_from_Arraymesh(obj_mesh));
}