#ifndef PORTALEFFECT_H
#define PORTALEFFECT_H

#include <godot_cpp/classes/mesh_instance3d.hpp>
#include <godot_cpp/classes/box_mesh.hpp>
#include <godot_cpp/classes/standard_material3d.hpp>
#include <godot_cpp/classes/resource_loader.hpp>
#include <godot_cpp/variant/vector3.hpp>
#include <godot_cpp/variant/vector2.hpp>
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/variant/utility_functions.hpp>
#include <godot_cpp/classes/shader_material.hpp>
#include <godot_cpp/classes/standard_material3d.hpp>
#include <godot_cpp/classes/scene_tree.hpp>
#include <godot_cpp/classes/texture2d.hpp>

//This class will create a sphere and apply a shader so that the sphere has a moving spiral pattern
namespace godot {

class PortalEffect : public MeshInstance3D {
    GDCLASS(PortalEffect, MeshInstance3D);

protected:
    static void _bind_methods();

public:
    // Default Constructor and Destructor
    PortalEffect();
    ~PortalEffect();

    void update(const Vector3 position);

    void _enter_tree() override;
};

}

#endif // SKYBOX_H
