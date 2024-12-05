#ifndef POPULATE_MESH_H
#define POPULATE_MESH_H

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

#include "prop.h"


// everything in gdextension is defined in this namespace
namespace godot {
class Populatemesh : public Node3D {
    // this macro sets up a few internal things
	GDCLASS(Populatemesh, Node3D);

private:
	double time_passed;

	void init_props();

	Dictionary mesh_filepaths;//Hash Map for mesh filepaths
	Dictionary texture_filepaths;//Hash Map for texture filepaths
	void load_filepaths();
    Vector<Prop*> prop_instances;

protected:
    // a static function that Godot will call to find out which methods can be called and which properties it exposes
	static void _bind_methods();
    Prop* create_prop(Vector3 size, Vector3 pos, Node* parentNode, String obj_name, String mesh_filepath, String texture_filepaths[], int num_textures);

public:
	Populatemesh();
	~Populatemesh();

	void _process(double delta) override;
	void _enter_tree ( ) override;
	void _ready ( ) override;

    void scatter_props(Node *parent, const Vector<Vector<float>> &heightfield, int width, int height, float scale, int prop_count);

	template <class T>
	bool create_and_add_as_child(T* &pointer, String name);
	
	template <class T>
	bool create_and_add_as_child_of_Node(T* &pointer, String name, Node* parent);

};

}

#endif