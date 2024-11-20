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
#include "enemy.h"
#include "debug_rect.h"
#include "player_scene.h"


// everything in gdextension is defined in this namespace
namespace godot {
class CustomScene3501 : public Node3D {
    // this macro sets up a few internal things
	GDCLASS(CustomScene3501, Node3D);

private:
	double time_passed;

	Player* player;
	
	Vector<DebugRect*> rect_instances;
	
	//Setup Functions (NEW - IMPLEMENT LIKE THIS)
	void init_debug_rects();
	void create_rect(Vector3 size, Vector3 pos, Node* parentNode, String name);
	void create_rect(Vector3 size, Vector3 pos, Node* parentNode, String name, Vector3 color);

	void init_player(Vector3 start_pos);

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