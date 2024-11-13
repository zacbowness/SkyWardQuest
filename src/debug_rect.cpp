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

void DebugRect::_enter_tree() {
    //if(DEBUG) UtilityFunctions::print("Enter Tree - CustomScene3501."); 
    BoxMesh* box = memnew(BoxMesh);
	box->set_size(scale);
		
	StandardMaterial3D* box_material = memnew(StandardMaterial3D);

	box_material->set_albedo(color);
	box->surface_set_material(0, box_material);

    material = box_material;
		
	set_mesh(box);
    set_position(position);
}

void DebugRect::setup_rect(Vector3 scale_in, Vector3 pos){
    scale = scale_in;
    position = pos;
    set_global_position(position);
    set_scale(scale);
}

void DebugRect::set_color(Vector3 color_in){
    color = Color(color_in);
    material->set_albedo(Color(color));
}

DebugRect::~DebugRect() {}