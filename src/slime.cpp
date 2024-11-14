#include "slime.h"
#include <godot_cpp/classes/resource_loader.hpp>


using namespace godot;

void Slime::_bind_methods() {}

Slime::Slime() {
	//Inherited From Enemy
	speed = 10.0f;
	radius = 10.0f;
}

Slime::~Slime() {}

void Slime::_ready (){
	//Initalize Slime to be a Sphere Mesh Based Maybe (Softbody)
	
}

void Slime::_process(double delta){

}