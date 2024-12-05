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
class Prop : public  CollisionObject{
	GDCLASS(Prop, CollisionObject);

protected:
	static void _bind_methods();
	
	Ref<ArrayMesh> import_mesh(String mesh_filepath, String texture_filepaths[]);
	Ref<ArrayMesh> obj_mesh;
	
	StandardMaterial3D* material;
	CollisionShape3D* collision_shape;
	Vector3 scale;
	Vector3 position;
	String prop_name;
	
	String mesh_filepath;
	Vector<String> texture_filepaths;

	AssetImporter* import_tool;

private:
	

public:
	Prop();
	~Prop();

	void _enter_tree()override;
	void _ready()override;

	Mesh* init_mesh() override;
	StaticBody3D* init_collider() override;

	void setup_prop(Vector3 position, Vector3 scale, String mesh_filepath, String texture_filepaths[], int num_textures, String name);
	void update_prop();
};

}

#endif