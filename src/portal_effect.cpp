#include "portal_effect.h"
#include <godot_cpp/classes/box_mesh.hpp>
#include <godot_cpp/classes/standard_material3d.hpp>
#include <godot_cpp/variant/color.hpp>
#include <godot_cpp/classes/sphere_mesh.hpp>
#include <godot_cpp/variant/quaternion.hpp>
#include <godot_cpp/variant/vector3.hpp>
#include <godot_cpp/variant/transform3d.hpp>

using namespace godot;

PortalEffect::PortalEffect() {
    // Constructor can remain empty or be used for non-scene related initialization
}

PortalEffect::~PortalEffect() {}

void PortalEffect::_enter_tree() {
    SphereMesh* PortalEffect_mesh = memnew(SphereMesh);
    Ref<Shader> shader = ResourceLoader::get_singleton()->load("res://shaders/spiralScreenEffect.gdshader");

    PortalEffect_mesh->set_radius(1); // Set the radius
    PortalEffect_mesh->set_height(2);

    set_mesh(PortalEffect_mesh);

    Ref<ShaderMaterial> shader_material = memnew(ShaderMaterial);
    shader_material->set_shader(shader);
    PortalEffect_mesh->surface_set_material(0, shader_material);

    // Apply a 180-degree rotation along the X-axis
    Transform3D transform = get_transform();
    transform.basis = Basis(Vector3(1, 0, 0), Math_PI); // Rotate 180 degrees
    set_transform(transform);

}


//This function still needs to be properly tested to ensure it works properly
void PortalEffect::update(const Vector3 position){
    // Update the position of the skybox
    set_position(position);
}

void PortalEffect::_bind_methods() {
}
