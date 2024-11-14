#include "enemy.h"
#include <godot_cpp/classes/resource_loader.hpp>

#include "quat_camera.h"


using namespace godot;

void Enemy::_bind_methods() {}

Enemy::Enemy() {GameOver = false;}

Enemy::~Enemy() {}

//pass a pointer to the player object to this enemy
void Enemy::setPlayerPointer(QuatCamera* player){this->player = player;}

void Enemy::_process(double delta){
	//UtilityFunctions::print(player);
	if (Engine::get_singleton()->is_editor_hint()||GameOver) return;
	approachPlayer();
	
}

void Enemy::approachPlayer(){
	Vector3 toPlayer = (get_position() - player->get_position()).normalized();
	set_position(get_position() - toPlayer * delta * speed);
}