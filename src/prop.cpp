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
	
	import_tool = memnew(AssetImporter);
	CollisionObject::_enter_tree();//Call Parent Enter_tree() !!IMPORTANT!!
}

void Prop::_ready(){

}

Mesh* Prop::init_mesh(){
    Ref<ArrayMesh> mesh;
	
	//Import mesh from file
	if(obj_mesh.is_null()){
		mesh = import_tool->import_mesh(mesh_filepath, texture_filepaths);
		obj_mesh = mesh;//Copy mesh to format collider later (we could use the mesh pointer this func returns but the conversions would be messy)
	}
	
	set_mesh(obj_mesh);//apply the mesh
	return(*obj_mesh);//return mesh once initialized to be stored in WorldObject::_enter_tree()
}

StaticBody3D* Prop::init_collider(){
	StaticBody3D* collider;

	create_or_add_child<StaticBody3D>(collider, "Collision Body");
	create_or_add_child<CollisionShape3D>(collision_shape, "Collision Shape", collider);
	collision_shape->set_shape(import_tool->shape_from_Arraymesh(obj_mesh));

	return collider;
}

//Import base values to memeber variables
void Prop::setup_prop(Vector3 position, Vector3 rotation, Vector3 scale, String mesh_filepath, String texture_filepaths[], int num_textures, String name){
	//copy filepaths into member variables so that they can be used in init_mesh()
	this->mesh_filepath = mesh_filepath;
	for(int i=0; i<num_textures;i++)this->texture_filepaths.push_back(texture_filepaths[i]);

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
	set_mesh(object_mesh);
	//Vector3 local_rotation = get_global_rotation_degrees();
}

void Prop::new_position(Vector3 pos) {position = pos;}