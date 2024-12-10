#include "portal.h"
#include <godot_cpp/classes/box_mesh.hpp>
#include <godot_cpp/classes/standard_material3d.hpp>
#include <godot_cpp/variant/color.hpp>
#include <godot_cpp/classes/sphere_mesh.hpp>
#include <godot_cpp/variant/quaternion.hpp>
#include <godot_cpp/variant/vector3.hpp>
#include <godot_cpp/variant/transform3d.hpp>

using namespace godot;

Portal::Portal() {
    // Constructor can remain empty or be used for non-scene related initialization
}

Portal::~Portal() {}

void Portal::_enter_tree() {
    SphereMesh* portal_mesh = memnew(SphereMesh);
    Ref<Shader> shader = ResourceLoader::get_singleton()->load("res://shaders/spiralScreenEffect.gdshader");

    portal_mesh->set_radius(1); // Set the radius
    portal_mesh->set_height(2);

    set_mesh(portal_mesh);

    Ref<ShaderMaterial> shader_material = memnew(ShaderMaterial);
    shader_material->set_shader(shader);
    portal_mesh->surface_set_material(0, shader_material);

    // Apply a 180-degree rotation along the X-axis
    Transform3D transform = get_transform();
    transform.basis = Basis(Vector3(1, 0, 0), Math_PI); // Rotate 180 degrees
    set_transform(transform);

}


//This function still needs to be properly tested to ensure it works properly
void Portal::configure(const Vector3 &scale, const Vector3 &position) {
    BoxMesh* box_mesh = memnew(BoxMesh);
    if (box_mesh) {
        box_mesh->set_size(scale);
    }

    // Update the position of the skybox
    set_position(position);
}


void Portal::follow_player(const Vector3 &player_position) {
    // Adjust the skybox position to follow the player
    set_position(player_position + offset);
}

void Portal::_bind_methods() {
}
