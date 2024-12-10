#ifndef Tower_H
#define Tower_H

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
#include <godot_cpp/classes/scene_tree.hpp>

#include "asset_importer.h"
#include "prop.h"

namespace godot {
class Tower : public  Node3D{
	GDCLASS(Tower, Node3D);

protected:
	static void _bind_methods();
	
	Vector<Prop*> obj_vector;
	AssetImporter* import_tool;
	Node3D* Prop_Group;

	Dictionary mesh_filepaths;
	Dictionary texture_filepaths;
	
public:
	Tower();
	~Tower();

	void _enter_tree()override;
	void _ready()override;

private:
	void load_filepaths();
	void build_tower();
	void make_prop(Vector3 pos, Vector3 scale, Vector3 rotation, String model_filepath, Vector<String> texture_filepaths, String name);

	Vector<String> make_vector(String arr[], int numStrings);

	//Function to add nodes as children to this one
	//Used to add objects like colliders & paraticle systems or any sub-objects under the one that calls this function
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