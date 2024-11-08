#ifndef CUSTOM_SCENE_H
#define CUSTOM_SCENE_H

#include <godot_cpp/classes/node3d.hpp>

#include <godot_cpp/classes/engine.hpp>
#include <godot_cpp/classes/input.hpp>
#include <godot_cpp/classes/input_event.hpp>
#include <godot_cpp/classes/resource_loader.hpp>
#include <godot_cpp/classes/scene_tree.hpp>
#include <godot_cpp/variant/utility_functions.hpp>

#include <godot_cpp/variant/quaternion.hpp>
#include <godot_cpp/variant/vector3.hpp>
#include <godot_cpp/variant/color.hpp>
#include <godot_cpp/variant/transform3d.hpp>

#include <godot_cpp/templates/vector.hpp> // GODOT EQUIVALENT TO std::vector !!!! 

#include <godot_cpp/classes/sphere_mesh.hpp>
#include <godot_cpp/classes/cylinder_mesh.hpp>
#include <godot_cpp/classes/box_mesh.hpp>
#include <godot_cpp/classes/standard_material3d.hpp>

#include <godot_cpp/variant/rect2.hpp> // for viewport size
#include <godot_cpp/classes/canvas_item.hpp> // for viewport size
#include <godot_cpp/classes/control.hpp> // for the anchors preset
#include <godot_cpp/classes/color_rect.hpp>

#include "defs.h"
#include "quat_camera.h"
#include "race_beacon.h"
#include "enemy.h"
#include "powerup.h"


// everything in gdextension is defined in this namespace
namespace godot {
class CustomScene3501 : public Node3D {
    // this macro sets up a few internal things
	GDCLASS(CustomScene3501, Node3D);

private:
	double time_passed;

	QuatCamera* main_camera;
	Vector<RaceBeacon*> beacon_instances;
	Vector<Enemy*> enemy_instances;
	Vector<Powerup*> powerup_instances;

	Vector3 beaconPositions[10] = { //define positions of beacons
		Vector3(-10, 10, -34),
		Vector3(18, 27, -116),
		Vector3(2, 44, -199),
		Vector3(61, 33, -253),
		Vector3(126, 70, -298),
		Vector3(232, 21, -277),
		Vector3(309, 85, -233),
		Vector3(374, 101, -136),
		Vector3(412, 82, -47),
		Vector3(423, 151, 58)
	};

	const float beaconRadius = 2.5;
	const float playerRadius = 1;
	const float enemyRadius = 1;

	bool GameOver;
	
	//Setup Functions
	void setup_beacons();
	void setup_enemy();
	void set_enemy_pos();
	void setup_powerups();
	void set_powerup_pos();

	//Collision Functions
	bool detect_collision(float rad_a, float rad_b, Vector3 pos_a, Vector3 pos_b);
	void check_beacon_collisions();
	void check_enemy_collisions();
	void check_powerup_collisions();

	//other beacon functions
	void highlight_next_beacon();

	//other
	void end_game(bool win);

protected:
    // a static function that Godot will call to find out which methods can be called and which properties it exposes
	static void _bind_methods();

public:
	CustomScene3501();
	~CustomScene3501();

	void _process(double delta) override;
	void _enter_tree ( ) override;
	void _ready ( ) override;


	// the return type represents whether it existed already; true if it is brand-new; false if it was retrieved from the SceneTree
	// search defines whether the scenetree should be checked for an instance
	template <class T>
	bool create_and_add_as_child(T* &pointer, String name);
	
	template <class T>
	bool create_and_add_as_child_of_Node(T* &pointer, String name, Node* parent);

};

}

#endif