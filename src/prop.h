#ifndef PROP_H
#define PROP_H

#include <godot_cpp/classes/node3d.hpp>
#include <godot_cpp/variant/utility_functions.hpp>

#include <godot_cpp/classes/standard_material3d.hpp>
#include <godot_cpp/classes/mesh_instance3d.hpp>
#include <godot_cpp/classes/static_body3d.hpp>
#include <godot_cpp/classes/collision_shape3d.hpp>
#include <godot_cpp/classes/array_mesh.hpp>
#include <godot_cpp/templates/vector.hpp>
#include <godot_cpp/classes/convex_polygon_shape3d.hpp>
#include <godot_cpp/classes/global_constants.hpp>

#include <godot_cpp/classes/static_body3d.hpp>
#include <godot_cpp/classes/collision_shape3d.hpp>
#include <godot_cpp/classes/concave_polygon_shape3d.hpp>

#include "collision_obj.h"
#include "asset_importer.h"

namespace godot {
class Prop : public  MeshInstance3D{
	GDCLASS(Prop, MeshInstance3D);

protected:
	static void _bind_methods();
	Ref<ArrayMesh> obj_mesh;
	
	StandardMaterial3D* material;
	CollisionShape3D* collision_shape;
	
	Vector3 scale;
	Vector3 position;
	Vector3 rotation_offset;
	String prop_name;
	
	String mesh_filepath;
	Vector<String> texture_filepaths;

	AssetImporter* import_tool2;

public:
	Prop();
	~Prop();

	void _enter_tree()override;
	void _ready()override;

	

	void setup_prop(Vector3 position, Vector3 rotation, Vector3 scale, String mesh_filepath, Vector<String> texture_filepaths, String name);
	void update_prop();

	void new_position(Vector3 pos);

private:

	void init_mesh();
	void init_collider();

	Ref<ArrayMesh> object_mesh;


	template <class T>
	bool create_or_add_child(T* &pointer, String name){
		Node* child = find_child(name);//find node with the given name (NAME MUST BE UNIQUE)

		if(child == nullptr){//if child node was not found, create it
			pointer = memnew(T);
			pointer->set_name(name);
			this->add_child(pointer);
			pointer->set_owner(get_tree()->get_edited_scene_root());
			return true;
		} else {
			pointer = dynamic_cast<T*>(child);//if node with name already exists, assign it to pointer
			return false;
		}
	}

	//A Polymorph of the above function where a parent node is given
	//Use this if you want a node to be added underneath the given parent node in the scene tree
	template <class T>
	bool create_or_add_child(T* &pointer, String name, Node3D* parent){
		
		Node* child = find_child(name);//find node with the given name (NAME MUST BE UNIQUE)
		if(child == nullptr){//if child node was not found, create it
			pointer = memnew(T);
			pointer->set_name(name);
			parent->add_child(pointer);//Add node as child of given node
			pointer->set_owner(get_tree()->get_edited_scene_root());
			return true;
		} else {
			pointer = dynamic_cast<T*>(child);//if node with name already exists, assign it to pointer
			return false;
		}
	}
};

}

#endif