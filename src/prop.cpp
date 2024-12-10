#include "prop.h"
#include <godot_cpp/classes/resource_loader.hpp>


using namespace godot;

void Prop::_bind_methods() {}

Prop::Prop() {
	scale = Vector3(1,1,1);
	position = Vector3(0,0,0);
	rotation_offset = Vector3(0,0,0);
}

Prop::~Prop() {}

void Prop::_enter_tree(){
	if(DEBUG) UtilityFunctions::print("Enter Tree - Prop.");
	import_tool2 = memnew(AssetImporter);
}

void Prop::_ready(){
	init_mesh();
	init_collider();
}

void Prop::init_mesh(){
    Ref<ArrayMesh> mesh;
	
	//Import mesh from file
	if(obj_mesh.is_null()){
		mesh = import_tool2->import_mesh(mesh_filepath, texture_filepaths);
		if(!mesh.is_null()) obj_mesh = mesh;//Copy mesh to format collider later (we could use the mesh pointer this func returns but the conversions would be messy)
	}
	
	if(!obj_mesh.is_null())set_mesh(obj_mesh);//apply the mesh
	else{ERR_PRINT("ERR: Mesh From Importer Is NULL");}
}

void Prop::init_collider(){
	StaticBody3D* collider;

	create_or_add_child<StaticBody3D>(collider, "Collision Body");
	create_or_add_child<CollisionShape3D>(collision_shape, "Collision Shape", collider);
	if(!obj_mesh.is_null()){
		Ref<ConcavePolygonShape3D> collision_poly = import_tool2->shape_from_Arraymesh(obj_mesh);
		if(!collision_poly.is_null())collision_shape->set_shape(collision_poly);
		else ERR_PRINT("ERR: Collider Polygon is NULL");
	} else ERR_PRINT("ERR: Mesh Is NULL - Skipping Collider Formulation");
	
}

//Import base values to memeber variables
void Prop::setup_prop(Vector3 position, Vector3 rotation, Vector3 scale, String mesh_filepath, Vector<String> texture_filepaths, String name){
	//copy filepaths into member variables so that they can be used in init_mesh()
	this->mesh_filepath = mesh_filepath;
	this->texture_filepaths = texture_filepaths;

	//Apply other values to member variables
	prop_name = name;
	this->position = position;
	this->scale = scale;
	rotation_offset = rotation;
}

void Prop::update_prop(){
	set_global_rotation_degrees(rotation_offset);
	set_position(position);
	set_scale(scale);
	if(!obj_mesh.is_null())set_mesh(obj_mesh);
	//Vector3 local_rotation = get_global_rotation_degrees();
}

void Prop::new_position(Vector3 pos) {position = pos;}