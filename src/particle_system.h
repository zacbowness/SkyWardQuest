#ifndef PARTICLESYSTEM_H_
#define PARTICLESYSTEM_H_

// parent class
#include <godot_cpp/classes/gpu_particles3d.hpp>
#include <godot_cpp/classes/node3d.hpp>

#include <godot_cpp/classes/input.hpp>

#include <godot_cpp/variant/utility_functions.hpp>
#include <godot_cpp/variant/vector3.hpp>
#include <godot_cpp/variant/array.hpp>
#include <godot_cpp/variant/string.hpp>
#include <godot_cpp/variant/packed_vector3_array.hpp>

// you can adjust these if you want. 
#define MIN_SPEED 0.0f
#define ACCELERATION 2.0f


// everything in gdextension is defined in this namespace
namespace godot {
class ParticleSystem : public GPUParticles3D {
    // this macro sets up a few internal things
	GDCLASS(ParticleSystem, GPUParticles3D);

private:
	int something; 

	//Set up Inital Values 
	String shader_name = "default_value";  
	String texture_name = "default_value";  
	Vector2 size = Vector2(1.0,1.0);
	int32_t amount = 20000;
	double lifetime = 2.0;

	void initalizeSystem();
	

protected:
    // a static function that Godot will call to find out which methods can be called and which properties it exposes
	static void _bind_methods();

public:
	ParticleSystem();
	ParticleSystem(String shader_name, String texture_name, Vector2 size);
	~ParticleSystem();

	void _enter_tree() override;
	void _ready() override;
	void _process(double delta) override;

	inline void set_shader_name(String name) {shader_name = name;}
	inline String get_shader_name() {return shader_name;}

};

}

#endif

/*
*
* A class which assists in addition of particle systems to the scene. 
*
* Copyright (c) 2024 Samantha Beilman (samanthabeilman@cmail.carleton.ca)
*
*/