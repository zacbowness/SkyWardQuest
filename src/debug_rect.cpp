#include "debug_rect.h"
#include <godot_cpp/classes/resource_loader.hpp>


using namespace godot;

void DebugRect::_bind_methods() {}

DebugRect::DebugRect() {
    //default values
    scale = Vector3(1,1,1);//1x1x1 cube
    color = Color(1,1,1);//white
    position = Vector3(0,0,0);//origin
}

void DebugRect::_ready(){
	
}

void DebugRect::_enter_tree() {
	if(DEBUG) UtilityFunctions::print("Enter Tree - DebugRect");
	
	CollisionObject::_enter_tree(); //Call Parent _enter_tree() function !!IMPORTANT!!
	
	//Set Object Starting Position
	set_position(position);	
}

//Initialize and return mesh for the object
Mesh* DebugRect::init_mesh(){
    BoxMesh* box = memnew(BoxMesh);
	material = memnew(StandardMaterial3D);

	material->set_albedo(color);
	box->surface_set_material(0, material);
	box->set_size(scale);
	set_mesh(box);//apply the mesh
	
	return(box);//return mesh once initialized to be stored in WorldObject::_enter_tree()
}

StaticBody3D* DebugRect::init_collider(){
	StaticBody3D* collider = memnew(StaticBody3D);
	Ref<BoxShape3D> shape = memnew(BoxShape3D);
	collision_shape = memnew(CollisionShape3D);
	
	shape->set_size(scale);

	create_or_add_child<StaticBody3D>(collider, "ColliderBody");
	create_or_add_child<CollisionShape3D>(collision_shape, String("Collider_Shape"), collider);//add collision shape as child of collider node

	//Apply shape to collision shape (this needs to be done after its been added to the scene for some reason)
	collision_shape->set_shape(shape);

	return collider;//Return collider so that CollisionObject can keep the pointer
}



void DebugRect::setup_rect(Vector3 scale_in, Vector3 pos){
    scale = scale_in;
    position = pos;
}

void DebugRect::setup_rect(Vector3 scale_in, Vector3 pos, Vector3 color_in){
    scale = scale_in;
    position = pos;
	color = Color(color_in.x, color_in.y, color_in.z);
}

void DebugRect::update_rect(){
    set_position(position);
    set_scale(scale);
	material->set_albedo(color);
	object_mesh->surface_set_material(0,material);
	set_mesh(object_mesh);
}

void DebugRect::set_color(Vector3 color_in){
    color = Color(color_in.x, color_in.y, color_in.z);
}

DebugRect::~DebugRect() {}