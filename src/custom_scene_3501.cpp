#include "custom_scene_3501.h"
#include <godot_cpp/core/memory.hpp> // for memnew
#include <godot_cpp/classes/random_number_generator.hpp> 
#include "powerup.h"


using namespace godot;

void CustomScene3501::_bind_methods() { }

CustomScene3501::CustomScene3501() : Node3D() {
	time_passed = 0.0;
	GameOver = false;
}

CustomScene3501::~CustomScene3501() {}

void CustomScene3501::_enter_tree (){
	if(DEBUG) UtilityFunctions::print("Enter Tree - CustomScene3501."); 

	create_and_add_as_child<QuatCamera>(main_camera, "QuatCamera");

	// The vectors are brand new every time you run the simulation or reload the project. 

	setup_beacons();
	setup_enemy();
	setup_powerups();
}

void CustomScene3501::_ready ( ){
	if(DEBUG) UtilityFunctions::print("Ready - CustomScene3501."); 

	// set the player's position (the camera) 
	main_camera->set_global_position(Vector3(5.0, 5.0, 25.0f));
	main_camera->look_at(Vector3(0, 0, 0)); // there are some bugs with this function if the up vector is parallel to the look-at position; check the manual for a link to more info

	// now that we have set the camera's starting state, let's reinitialize its variables
	main_camera->_ready();

	//set beacon positions
	for(int i=0;i<beacon_instances.size();i++){
		beacon_instances[i]->set_global_position(beaconPositions[i]);
	}

	//set first beacon as goal beacon
	highlight_next_beacon();
	
	//set enemy positions
	set_enemy_pos();

	//set powerup positions
	set_powerup_pos();
}

// called every frame (as often as possible)
void CustomScene3501::_process(double delta) {
	if (Engine::get_singleton()->is_editor_hint()||GameOver) return; // Early return if we are in editor

	time_passed += delta;

	check_beacon_collisions();
	check_enemy_collisions();
	check_powerup_collisions();

	//check for win state
	if(beacon_instances.size()==0) end_game(true);
}

void CustomScene3501::setup_beacons(){
	Node* beaconGroup;
	create_and_add_as_child<Node>(beaconGroup, "Beacon Group");
	
	int numBeacons = 10;

	for(int i=0;i<numBeacons;i++){
		RaceBeacon* obj_instance;
		
		bool isNew = create_and_add_as_child_of_Node<RaceBeacon>(obj_instance, vformat("Beacon_%d", i), beaconGroup);
		
		if(isNew){
			//set up mesh
			SphereMesh* sphere = memnew(SphereMesh);
			sphere->set_radius(beaconRadius);
			sphere->set_height(beaconRadius*2);
		
			StandardMaterial3D* sphere_material = memnew(StandardMaterial3D);

			sphere_material->set_albedo(Color(0.5f, 0.5f, 0.8f, 1.0f));//set sphere color
			sphere->surface_set_material(0, sphere_material);
		
			obj_instance->set_mesh(sphere);//apply mesh
		}

		beacon_instances.push_back(obj_instance);//add beacon to vector of beacon object references
	}
}

//create enemy objects
void CustomScene3501::setup_enemy(){
	Node* enemyGroup;
	create_and_add_as_child<Node>(enemyGroup, "Enemy Group");//create grouping node
	
	int numEnemies = 10;
	
	for(int i=0;i<numEnemies;i++){
		Enemy* obj_instance;
		
		bool isNew = create_and_add_as_child_of_Node<Enemy>(obj_instance, vformat("Enemy_%d", i), enemyGroup);
		
		if(isNew){
			//set up mesh
			CylinderMesh* cylinder = memnew(CylinderMesh);
			cylinder->set_top_radius(1);
			cylinder->set_bottom_radius(1);
			cylinder->set_height(2);
		
			StandardMaterial3D* cylinder_material = memnew(StandardMaterial3D);

			cylinder_material->set_albedo(Color(0.9f, 0.1f, 0.1f, 1.0f));
			cylinder->surface_set_material(0, cylinder_material);
		
			obj_instance->set_mesh(cylinder);
			
		}

		obj_instance->setPlayerPointer(main_camera);
		enemy_instances.push_back(obj_instance);
	}
}

void CustomScene3501::set_enemy_pos(){
	//set enemy locations with one around each beacon
	RandomNumberGenerator* rng = memnew(RandomNumberGenerator);
	for(int i=0;i<enemy_instances.size();i++){
		float x = rng->randf_range(6.0f, -6.0f);
		float y = rng->randf_range(6.0f, -6.0f);
		float z = rng->randf_range(6.0f, -6.0f);

		Vector3 randomOffset = Vector3(x,y,z);
		enemy_instances[i]->set_global_position(beaconPositions[i]+randomOffset);
	}

	memdelete(rng);
}

void CustomScene3501::setup_powerups(){
	Node* powerGroup;
	create_and_add_as_child<Node>(powerGroup, "Powerup Group");//create grouping node
	
	int numPowerups = 21;

	Powerup* obj_instance;
	
	for(int i=0;i<numPowerups;i++){
		
		bool isNew = create_and_add_as_child_of_Node<Powerup>(obj_instance, vformat("Powerup_%d", i), powerGroup);
		
		if(isNew){
			//set up mesh
			BoxMesh* box = memnew(BoxMesh);
			box->set_size(Vector3(1,1,1));
		
			StandardMaterial3D* box_material = memnew(StandardMaterial3D);

			box_material->set_albedo(Color(0.1f, 0.9f, 0.1f, 1.0f));
			box->surface_set_material(0, box_material);
		
			obj_instance->set_mesh(box);
			
		}

		powerup_instances.push_back(obj_instance);
	}
}

void CustomScene3501::set_powerup_pos(){
	RandomNumberGenerator* rng = memnew(RandomNumberGenerator);
	for(int i=0;i<10;i++){//for each beacon, place 2 powerups randomly around it
		float x = rng->randf_range(8.0f, -8.0f);
		float y = rng->randf_range(8.0f, -8.0f);
		float z = rng->randf_range(8.0f, -8.0f);
		powerup_instances[i]->set_global_position(beaconPositions[i]+Vector3(x,y,z));

		float x2 = rng->randf_range(8.0f, -8.0f);
		float y2 = rng->randf_range(8.0f, -8.0f);
		float z2 = rng->randf_range(8.0f, -8.0f);
		powerup_instances[i+10]->set_global_position(beaconPositions[i]+Vector3(x2,y2,z2));
	}

	powerup_instances[20]->set_global_position(Vector3(0,5,13));//place one powerup in front of the player
}


template <class T>
// returns true if pointer is brand-new; false if retrieved from SceneTree
bool CustomScene3501::create_and_add_as_child(T* &pointer, String name){

	Node* child = find_child(name);
	
	if(child == nullptr){
		pointer = memnew(T);
		pointer->set_name(name);
		add_child(pointer);
		pointer->set_owner(get_tree()->get_edited_scene_root());
		return true;
	}
	else{
		pointer = dynamic_cast<T*>(child);
		return false;
	}
}


template <class T>
// returns true if pointer is brand-new; false if retrieved from SceneTree
bool CustomScene3501::create_and_add_as_child_of_Node(T* &pointer, String name, Node* parent){
	
	Node* child = find_child(name);//find node with the given name

	if(child == nullptr){//if child node was not found, create it
		pointer = memnew(T);
		pointer->set_name(name);
		parent->add_child(pointer);
		pointer->set_owner(get_tree()->get_edited_scene_root());
		return true;
	} else {
		pointer = dynamic_cast<T*>(child);//if node with name already exists, assign it to pointer
		return false;
	}
}

bool CustomScene3501::detect_collision(float rad_a, float rad_b, Vector3 pos_a, Vector3 pos_b){
	float distance = pos_a.distance_to(pos_b);
	if(distance < rad_a + rad_b) return true;
	else return false;
}

void CustomScene3501::check_beacon_collisions(){
	Vector3 player_pos = main_camera->get_position();//get vector of player's position
	for(RaceBeacon* beacon: beacon_instances){ //iterate through beacons

		//if player is coliding with beacon AND beacon is the current goal beacon -> clear from memory and highlight next
		if(detect_collision(playerRadius, beaconRadius, player_pos, beacon->get_position())&&beacon->isNext()){
			beacon_instances.erase(beacon);
			memdelete(beacon);
			UtilityFunctions::print("BEACON REACHED");
			if(!beacon_instances.is_empty()) highlight_next_beacon();
		}
	}
}

void CustomScene3501::check_enemy_collisions(){
	Vector3 player_pos = main_camera->get_position();
	for(Enemy* enemy: enemy_instances){
		if(detect_collision(playerRadius, enemyRadius, player_pos, enemy->get_position())){
			UtilityFunctions::print("CAUGHT BY ENEMY: GAME OVER");
			
			//end the game
			end_game(false);
		}
	}
}

void CustomScene3501::check_powerup_collisions(){
	Vector3 player_pos = main_camera->get_position();
	for(Powerup* powerup: powerup_instances){
		if(detect_collision(playerRadius, 0.5f, player_pos, powerup->get_position())){
			UtilityFunctions::print("POWERUP COLLECTED");
			powerup_instances.erase(powerup);
			memdelete(powerup);
			main_camera->powerup();// apply movement boost to player
		}
	}
}

void CustomScene3501::highlight_next_beacon(){
	SphereMesh* sphere = memnew(SphereMesh);
	sphere->set_radius(beaconRadius+2);
	sphere->set_height(beaconRadius*2+4);
	StandardMaterial3D* sphere_material = memnew(StandardMaterial3D);
	sphere_material->set_albedo(Color(0.7f, 0.7f, 0.1f, 1.0f));
	sphere->surface_set_material(0, sphere_material);
	
	beacon_instances[0]->set_mesh(sphere);
	beacon_instances[0]->set_as_next();//set next beacon as the only one the player can collide with
}

void CustomScene3501::end_game(bool win){
	//end the processes for enemies, player, and game
	GameOver = true;
	for(Enemy* enemy: enemy_instances) enemy->game_over();
	main_camera->game_over();

	ColorRect* screen = memnew(ColorRect);
	if(win)screen->set_color(Color(0.0,1.0,0.0,0.5));
	else screen->set_color(Color(1.0,0.0,0.0,0.5));

	screen->set_size(Vector2(2000,2000));

	add_child(screen);

}


/*
*
* The usual container class added to the demos. This one should be used to create a racetrack.
*
* Copyright (c) 2024 Samantha Beilman (samanthabeilman@cmail.carleton.ca)
*
*/