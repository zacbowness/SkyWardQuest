#include <godot_cpp/classes/resource_loader.hpp>
#include <godot_cpp/classes/font.hpp>
#include <godot_cpp/classes/packed_scene.hpp>
#include <godot_cpp/classes/input.hpp>

#include "2dScene.h"


using namespace godot;

void Scene2D::_bind_methods() {}

Scene2D::Scene2D() {}

Scene2D::~Scene2D() {}

void Scene2D::_enter_tree(){

}

void Scene2D::_process(double delta){
	
}

void Scene2D::setFont(Label* label, int size){
	label->add_theme_font_size_override("font_size", size); // Set the font size
}
void Scene2D::setColour(Label* label, const Color &color) {
    // Set the color of the label's text
    label->add_theme_color_override("font_color", color);
}

void Scene2D::createTitle(){
	create_and_add_as_child(title, "Title");
	title->set_text("Welcome to Skyward Quest");
	title->set_position(Vector2(350, 50)); 
	setFont(title, 50);
}

void Scene2D::createInfo(){
	create_and_add_as_child(info, "Info");
	info->set_text("Press Enter to Begin \nBy Sam, Zac, Ellie ");
	info->set_position(Vector2(500, 250));
	setFont(title, 30);
}

void Scene2D::swapScene(String new_scene_path) {
	get_tree()->change_scene_to_file(new_scene_path);
}




