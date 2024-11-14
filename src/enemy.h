#ifndef ENEMY_H
#define ENEMY_H

#include <godot_cpp/classes/node3d.hpp>
#include <godot_cpp/classes/sphere_mesh.hpp>

#include <godot_cpp/variant/utility_functions.hpp>

#include <godot_cpp/classes/mesh_instance3d.hpp>
#include <godot_cpp/godot.hpp>
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/classes/engine.hpp>

namespace godot {

class QuatCamera;
class Enemy : public  MeshInstance3D{
	GDCLASS(Enemy, MeshInstance3D);

protected:
	static void _bind_methods();
	float speed;	
	float radius;
	void approachPlayer();
	QuatCamera* player;

private:	
	bool GameOver;
	
public:
	Enemy();
	~Enemy();

	void _process(double delta) override;	
	void setPlayerPointer(QuatCamera* player);
	void game_over() {GameOver = true;}
	
};

}

#endif