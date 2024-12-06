#include "register_types.h"



// include the headers from your classes
#include "quat_camera.h"
#include "custom_scene_3501.h"
#include "debug_rect.h"
#include "slime.h"
#include "world_obj.h"
#include "collision_obj.h"
#include "npc.h"
#include "enemy.h"
#include "friendly.h"
#include "player_scene.h"
#include "map.h"
#include "particle_system.h"
#include "collectable.h"
#include "asset_importer.h"
#include "prop.h"
#include "bee.h"
#include "bee_part.h"
#include "bee_fullBody.h"
#include "bee_yellowBody.h"
#include "bee_blackBody.h"
#include "bee_eyes.h"
#include "bee_leftwing.h"
#include "bee_rightwing.h"
#include "wolf.h"
#include "flower.h"

#include "skybox.h"
#include "populate_mesh.h"

#include <gdextension_interface.h>
#include <godot_cpp/core/defs.hpp>
#include <godot_cpp/godot.hpp>

using namespace godot;

// gets called when godot loads our plugin
void initialize_example_module(ModuleInitializationLevel p_level) {
	if (p_level != MODULE_INITIALIZATION_LEVEL_SCENE) {
		return;
	}
    // Misc Classes
	ClassDB::register_class<CustomScene3501>();
	ClassDB::register_class<AssetImporter>();

	//Player Classes
	ClassDB::register_class<Player>();
	ClassDB::register_class<QuatCamera>();
	
	//World Object Classes
	ClassDB::register_class<WorldObject>();
	ClassDB::register_class<CollisionObject>();
	ClassDB::register_class<DebugRect>();
	ClassDB::register_class<Prop>();
	ClassDB::register_class<Flower>();
	
	//Enemy Classes
	ClassDB::register_class<Npc>();
	ClassDB::register_class<Enemy>();
	ClassDB::register_class<Slime>();
	ClassDB::register_class<Wolf>();

	//Map Class
	ClassDB::register_class<Map>();

	//Particle System Class
	ClassDB::register_class<ParticleSystem>();

	//Collectable Class
	ClassDB::register_class<Collectable>();

	//Bee Classes
	ClassDB::register_class<Friend>();
	ClassDB::register_class<Bee>();
	ClassDB::register_class<BeePart>();
	ClassDB::register_class<BeeYBody>();
	ClassDB::register_class<BeeBBody>();
	ClassDB::register_class<BeeEye>();
	ClassDB::register_class<BeeLWing>();
	ClassDB::register_class<BeeRWing>();
	ClassDB::register_class<BeeBody>();
	
	
	ClassDB::register_class<Skybox>();

	ClassDB::register_class<Populatemesh>();
	
	
}

// gets called when godot unloads our plugin
void uninitialize_example_module(ModuleInitializationLevel p_level) {
	if (p_level != MODULE_INITIALIZATION_LEVEL_SCENE) {
		return;
	}
}


extern "C" {

/* --- Initialization ---
The important function is the this function called example_library_init. 
We first call a function in our bindings library that creates an initialization object. 
This object registers the initialization and termination functions of the GDExtension. 
Furthermore, it sets the level of initialization (core, servers, scene, editor, level).
*/
GDExtensionBool GDE_EXPORT example_library_init(GDExtensionInterfaceGetProcAddress p_get_proc_address, const GDExtensionClassLibraryPtr p_library, GDExtensionInitialization *r_initialization) {
	// initialization object
    godot::GDExtensionBinding::InitObject init_obj(p_get_proc_address, p_library, r_initialization);

	init_obj.register_initializer(initialize_example_module);
	init_obj.register_terminator(uninitialize_example_module);
	init_obj.set_minimum_library_initialization_level(MODULE_INITIALIZATION_LEVEL_SCENE);

	return init_obj.init();
}



}