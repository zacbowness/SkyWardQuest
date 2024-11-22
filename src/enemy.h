#ifndef ENEMY_H
#define ENEMY_H

#include <godot_cpp/classes/node3d.hpp>
#include <godot_cpp/classes/sphere_mesh.hpp>

#include <godot_cpp/variant/utility_functions.hpp>

#include <godot_cpp/classes/mesh_instance3d.hpp>
#include <godot_cpp/godot.hpp>
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/classes/engine.hpp>
#include "npc.h"

namespace godot {

enum EnemyType{
	SLIME,
	WOLF
};

class QuatCamera;
class Enemy : public  Npc{
	GDCLASS(Enemy, Npc);

protected:
	static void _bind_methods();
	enum EnemyType enemyType;
	float aggroRadius;

private:	
	
public:
	Enemy();
	~Enemy();

	void _process(double delta) override;	

	
};

}

#endif