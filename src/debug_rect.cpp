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
	
	//if(DEBUG) UtilityFunctions::print("Enter Tree - CustomScene3501.");
    BoxMesh* box = memnew(BoxMesh);
	
	material = memnew(StandardMaterial3D);

	material->set_albedo(color);
	box->surface_set_material(0, material);
	box->set_size(scale);
	
	set_mesh(box);
    set_position(position);
}

void DebugRect::setup_rect(Vector3 scale_in, Vector3 pos){
    scale = scale_in;
    position = pos;
	
	/*
	//create shape of the rectangle
	collider = memnew(StaticBody3D);
	Ref<BoxShape3D> shape;
	shape.instantiate();
	shape->set_size(scale);
	
	//set the shape to the CollisionShape3D
	collision_shape = memnew(CollisionShape3D);
	collision_shape->set_shape(shape);

	collider->add_child(collision_shape);
	//collision_shape->set_owner(get_tree()->get_edited_scene_root());
	collider->set_transform(get_transform());
	add_child(collider);
	//Apply positioning
	*/
}

void DebugRect::update_rect(){
    set_position(position);
    set_scale(scale);
}

void DebugRect::set_color(Vector3 color_in){
    color = Color(color_in);
    material->set_albedo(Color(color));
}

DebugRect::~DebugRect() {}