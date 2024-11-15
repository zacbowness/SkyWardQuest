#ifndef NPC_H
#define NPC_H

#include <godot_cpp/classes/node3d.hpp>
#include <godot_cpp/classes/sphere_mesh.hpp>

#include <godot_cpp/variant/utility_functions.hpp>

#include <godot_cpp/classes/mesh_instance3d.hpp>
#include <godot_cpp/godot.hpp>
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/classes/engine.hpp>
#include <godot_cpp/classes/standard_material3d.hpp>
#include <godot_cpp/classes/shader_material.hpp>

namespace godot {

enum NpcType{
	ENEMY,
	FRIENDLY
};

class QuatCamera;
class Npc : public  MeshInstance3D{
	GDCLASS(Npc, MeshInstance3D);

protected:
	static void _bind_methods();
	float speed;	
	float radius;
	void approachPlayer(double);
	QuatCamera* player;
	enum NpcType type;

private:	
	bool GameOver;
	
public:
	Npc();
	~Npc();

	void _process(double delta) override;	
	void setPlayerPointer(QuatCamera* player);
	void game_over() {GameOver = true;}
	bool playerInRadius();
	
};

}

#endif