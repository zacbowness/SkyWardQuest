#include "mountain.h"
#include <godot_cpp/core/memory.hpp> // for memnew
#include <godot_cpp/classes/random_number_generator.hpp>


using namespace godot;

void  Mountain::_bind_methods() { }

 Mountain:: Mountain() : Node3D() {
	time_passed = 0.0;
}

 Mountain::~ Mountain() {}

void  Mountain::_enter_tree (){
	if(DEBUG) UtilityFunctions::print("Enter Tree - CustomScene3501.");

	create_and_add_as_child<Map>(map,"Mountain");

}

void  Mountain::_ready ( ){
	if(DEBUG) UtilityFunctions::print("Ready - CustomScene3501.");

    Vector3 start = Vector3(5.0f, 0.0f, 5.0f);
	Vector3 stop= Vector3(25.0f, 0.0f, 100.0f);
	float path_width = 15.0f;

    map->generate_terrain(
        70,    // Terrain width
        70,    // Terrain height
        1,      // Octaves (not used here)
        0.0f,   // Persistence
        1.0f,   // Scale
        20.0f,  // Maximum height
        10.0f,    // Mountain scale
        0.8
    );

    Vector<Vector<float>> heightfield = map->get_heightfield();

    map->add_mesh(heightfield,Vector3(5, -18, 70),Color(0.4,0.2,0.7));

}

// called every frame (as often as possible)
void Mountain::_process(double delta) {
	if (Engine::get_singleton()->is_editor_hint()) return; // Early return if we are in editor

	time_passed += delta;
}