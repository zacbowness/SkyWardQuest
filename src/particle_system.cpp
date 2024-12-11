#include "particle_system.h"
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/classes/mesh.hpp>
#include <godot_cpp/classes/engine.hpp>
#include <godot_cpp/classes/input_event.hpp>
#include <godot_cpp/classes/shader_material.hpp>

#include <godot_cpp/classes/resource_loader.hpp>
#include <godot_cpp/classes/quad_mesh.hpp>

using namespace godot;

void ParticleSystem::_bind_methods() {
	// IMPORTANT NOTE: in order to use a non-zero argument constructor, you need to bind the methods. 
	// Think about why that is and ask about it if you can't figure it out. It will maybe help you understand what's going on with the SceneTree a bit better. 
	ClassDB::bind_method(D_METHOD("set_shader_name", "shader_name"), &ParticleSystem::set_shader_name);
	ClassDB::bind_method(D_METHOD("get_shader_name"), &ParticleSystem::get_shader_name);

	ADD_PROPERTY(PropertyInfo(Variant::STRING, "shader_name"), "set_shader_name", "get_shader_name");
}

ParticleSystem::ParticleSystem() : GPUParticles3D() {
	
}

void ParticleSystem::_enter_tree(){

}

void ParticleSystem::_ready(){
	
}

ParticleSystem::~ParticleSystem() {
	// Add your cleanup here.
}

void ParticleSystem::_process(double delta){
	if (Engine::get_singleton()->is_editor_hint()) return; // Early return if we are in editor
}

void ParticleSystem::init_particle_system(String shader_name_in, String texture_name_in, Vector2 size_in, Vector3 pos, int32_t amount_in, double lifetime_in){
	shader_name = shader_name_in;  
	texture_name = texture_name_in;  
	size = size_in;
	position = pos;
	amount = amount_in;
	lifetime = lifetime_in;
}

void ParticleSystem::update_particle_system(){
	// Particle system properties, can be changed from the custom scene code as well
	set_amount(amount);
	set_lifetime(lifetime);
	
	// set up the material to attach to the quad
	ShaderMaterial* spatial_material = memnew(ShaderMaterial);
	Ref<Shader> shader = ResourceLoader::get_singleton()->load(vformat("shaders/%s_ss.gdshader", shader_name), "Shader");
	if(!shader.is_null()){
		spatial_material->set_shader(shader);
	} else {
		ERR_PRINT(vformat("ERROR: Particle System Shader %s.ss is NULL",shader_name));
		return;
	}
	 
	// this will be the default texture of the spatial material unless you change it 
	
	spatial_material->set_shader_parameter("texture_image", ResourceLoader::get_singleton()->load(vformat("res://textures/%s.png", texture_name)));
	//spatial_material->set_shader_parameter("texture_image", ResourceLoader::get_singleton()->load("res://textures/droplet_texture.png"));

	// Set up the quad to use for each particle
	QuadMesh* mesh = memnew(QuadMesh);
	mesh->set_size(size);
	
	// set up process material
	ShaderMaterial* process_material = memnew(ShaderMaterial);
	shader = ResourceLoader::get_singleton()->load(vformat("shaders/%s_ps.gdshader", shader_name), "Shader");
	
	if(!shader.is_null())process_material->set_shader(shader);
	else{
		ERR_PRINT("ERROR: Shader Process Material is NULL");
		return;
	}

	// attach the materials and mesh
	mesh->set_material(spatial_material);
	set_draw_pass_mesh(0, mesh);
	set_process_material(process_material);

	// can be useful
	spatial_material->set_shader_parameter("num_particles", get_amount());
	process_material->set_shader_parameter("num_particles", get_amount());

	set_position(position);
}

/*
*
* A class which assists in addition of particle systems to the scene. 
*
* Copyright (c) 2024 Samantha Beilman (samanthabeilman@cmail.carleton.ca)
*
*/
