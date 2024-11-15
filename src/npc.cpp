#include "npc.h"
#include <godot_cpp/classes/resource_loader.hpp>

#include "quat_camera.h"


using namespace godot;

void Npc::_bind_methods() {}

Npc::Npc() {GameOver = false;}

Npc::~Npc() {}

//pass a pointer to the player object to this enemy
void Npc::setPlayerPointer(QuatCamera* player){this->player = player;}

void Npc::_process(double delta){
	if (Engine::get_singleton()->is_editor_hint()||GameOver) return;
	approachPlayer(delta);
	
}

void Npc::approachPlayer(double delta){
	Vector3 toPlayer = (get_position() - player->get_position()).normalized();
	set_position(get_position() - toPlayer * delta * speed);
}

bool Npc::playerInRadius(){
	//Checks if the Distance to the player is within the radius 
	return get_position().distance_to(player->get_position()) <= radius;
}