#include "prop.h"
#include <godot_cpp/classes/resource_loader.hpp>


using namespace godot;

void Prop::_bind_methods() {}

Prop::Prop() {
	scale = Vector3(1,1,1);
	position = Vector3(0,0,0);
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
	StaticBody3D* collider = memnew(StaticBody3D);
	collision_shape = memnew(CollisionShape3D);

	/*
	//Create Concave Shape From Mesh
	Ref<ConvexPolygonShape3D> convex_shape;
	convex_shape.instantiate();

	//Collect all faces of the mesh into a Vector
	PackedVector3Array collision_faces;
	for(int i=0;i<obj_mesh->get_surface_count();i++){
		//get array of surface at index i
		Array surface_array = object_mesh->surface_get_arrays(i);

		//Extract vertices and indices from surface array
		PackedVector3Array vertices = surface_array[ArrayMesh::ARRAY_VERTEX];
		PackedInt32Array indices = surface_array[ArrayMesh::ARRAY_INDEX];

		if(indices.is_empty())continue; //if no indices, skip next step

		//Iterate through faces and add them to the collision face vector
		for(int j=0;j<indices.size();j+=3){//Iterate by 3 because of each face having 3 vertices
			collision_faces.push_back(vertices[indices[j]]);
            collision_faces.push_back(vertices[indices[j + 1]]);
            collision_faces.push_back(vertices[indices[j + 2]]);
		}
	}
	
	convex_shape->set_points(collision_faces);

	collision_shape->set_shape(convex_shape);
	*/
	//create_or_add_child<StaticBody3D>(collider, "Collision Body");
	create_or_add_child<CollisionShape3D>(collision_shape, "Collision Shape");
	

	return collider;
}

//Import base values to memeber variables
void Prop::setup_prop(Vector3 position, Vector3 scale, String mesh_filepath, String texture_filepaths[], int num_textures, String name){
	//copy filepaths into member variables so that they can be used in init_mesh()
	this->mesh_filepath = mesh_filepath;
	for(int i=0; i<num_textures;i++)this->texture_filepaths.push_back(texture_filepaths[i]);

	//Apply other values to member variables
	prop_name = name;
	this->position = position;
	this->scale = scale;
}

void Prop::update_prop(){
	set_position(position);
	set_scale(scale);
	set_mesh(object_mesh);
}