#include "skybox.h"
#include <godot_cpp/classes/box_mesh.hpp>
#include <godot_cpp/classes/standard_material3d.hpp>
#include <godot_cpp/variant/color.hpp>
#include <godot_cpp/classes/sphere_mesh.hpp>

using namespace godot;

Skybox::Skybox() {
    // Constructor can remain empty or be used for non-scene related initialization
}

Skybox::~Skybox() {}

void Skybox::_enter_tree() {

    SphereMesh* box_mesh = memnew(SphereMesh);
    ShaderMaterial* shader_material = memnew(ShaderMaterial);
    Ref<Shader> shader = ResourceLoader::get_singleton()->load("res://shaders/skybox.gdshader");
    Ref<Texture2D> texture = ResourceLoader::get_singleton()->load("res://textures/blue_sky.png");

    box_mesh->set_radius(1000); // Large enough for the skybox
    box_mesh->set_height(1000);
    box_mesh->set_radial_segments(64); // rings for horizontal smoothness
    box_mesh->set_rings(32); // rings for vertical smoothness
    box_mesh->set_flip_faces(true); // Flip faces to make normals point inward
    set_mesh(box_mesh);

    // Create a Shader Material
    shader_material->set_shader(shader); 
    shader_material->set_shader_parameter("texture_albedo",texture);//Remove this line if not working

    // Apply the material to the BoxMesh
	box_mesh->surface_set_material(0, shader_material);
}

//This function still needs to be properly tested to ensure it works properly
void Skybox::configure(const Vector3 &scale, const Vector3 &position) {
    BoxMesh* box_mesh = memnew(BoxMesh);
    if (box_mesh) {
        box_mesh->set_size(scale);
    }

    // Update the position of the skybox
    set_position(position);
}


void Skybox::follow_player(const Vector3 &player_position) {
    // Adjust the skybox position to follow the player
    set_position(player_position + offset);
}

void Skybox::_bind_methods() {
    ClassDB::bind_method(D_METHOD("configure", "scale", "position"), &Skybox::configure);
    ClassDB::bind_method(D_METHOD("follow_player", "player_position"), &Skybox::follow_player);
}
