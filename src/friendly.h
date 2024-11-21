#ifndef FRIENDLY_H
#define FRIENDLY_H

#include <godot_cpp/classes/node3d.hpp>
#include <godot_cpp/classes/sphere_mesh.hpp>

#include <godot_cpp/variant/utility_functions.hpp>

#include <godot_cpp/classes/mesh_instance3d.hpp>
#include <godot_cpp/godot.hpp>
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/classes/engine.hpp>
#include "npc.h"

namespace godot {

enum FriendType{
	BEE
};

class QuatCamera;
class Friend : public  Npc{
	GDCLASS(Friend, Npc);

protected:
	static void _bind_methods();
	enum FriendType enemyType;

private:	
	
public:
	Friend();
	~Friend();

	void _process(double delta) override;	

	
};

}

#endif