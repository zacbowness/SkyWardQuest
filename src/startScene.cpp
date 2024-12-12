#include "startScene.h"
#include <godot_cpp/classes/resource_loader.hpp>
#include <godot_cpp/classes/font.hpp>
#include <godot_cpp/classes/packed_scene.hpp>
#include <godot_cpp/classes/input.hpp>


using namespace godot;

void startScene::_bind_methods() {}

startScene::startScene() {}

startScene::~startScene() {}

void startScene::_enter_tree(){
	createTitle();
	createInfo();
}

void startScene::_process(double delta){
	if (Engine::get_singleton()->is_editor_hint()) return; // Early return if we are in editor
	Input* _input = Input::get_singleton();
	if(_input->is_action_just_released("switch_main")){
		swapScene("res://main.tscn");
	}
}

void startScene::createTitle(){
	create_and_add_as_child(title, "Title");
	title->set_text("Welcome to Skyward Quest");
	title->set_position(Vector2(350, 50)); // Position the text
	setFont(title, 50);
}

void startScene::createInfo(){
	create_and_add_as_child(info, "Info");
	info->set_text("Press Enter to Begin \nCollect 3 Gems And Escape Using The Portal\nBy Sam, Zac, Ellie ");
	info->set_position(Vector2(400, 250)); // Position the text
	setFont(title, 30);
}





