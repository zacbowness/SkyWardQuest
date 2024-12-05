#ifndef FLOWER_H
#define FLOWER_H

#include <godot_cpp/classes/node3d.hpp>
#include <godot_cpp/classes/sphere_mesh.hpp>
#include <godot_cpp/classes/box_mesh.hpp>
#include <godot_cpp/classes/box_shape3d.hpp>

#include <godot_cpp/classes/character_body3d.hpp>


#include <godot_cpp/variant/utility_functions.hpp>

#include <godot_cpp/classes/mesh_instance3d.hpp>
#include <godot_cpp/godot.hpp>
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/classes/engine.hpp>

namespace godot {

class Flower : public  CharacterBody3D{
	GDCLASS(Flower, CharacterBody3D);

protected:
	static void _bind_methods();
	


private:
	void init_body();
	

public:
	Flower();
	~Flower();

	void _enter_tree() override;
    void _ready() override;
	void _process(double delta) override;

};

}

#endif