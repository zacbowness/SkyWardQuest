#include "gameOverScene.h"
#include <godot_cpp/classes/resource_loader.hpp>
#include <godot_cpp/classes/font.hpp>
#include <godot_cpp/classes/packed_scene.hpp>
#include <godot_cpp/classes/input.hpp>


using namespace godot;

void gameOverScene::_bind_methods() {}

gameOverScene::gameOverScene() {}

gameOverScene::~gameOverScene() {}

void gameOverScene::_enter_tree(){
	createText();
}

void gameOverScene::_process(double delta){

}

void gameOverScene::createText(){
	create_and_add_as_child(gameOver, "Info");
	gameOver->set_text("You Win!");
	gameOver->set_position(Vector2(300, 150)); // Position the text
	setFont(gameOver, 100);
	setColour(gameOver, Color(0.0, 1, 0));
}







