#ifndef PORTAL_H
#define PORTAL_H

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

namespace godot {

class Portal : public MeshInstance3D {
    GDCLASS(Portal, MeshInstance3D);

protected:
    // Bind methods for exposing to GDScript
    static void _bind_methods();

    // Offset to follow the player (if needed)
    Vector3 offset;

public:
    // Constructor and Destructor
    Portal();
    ~Portal();

    // Configures the scale and position of the skybox
    void configure(const Vector3 &scale, const Vector3 &position);

    // Updates the skybox's position to follow the player
    void follow_player(const Vector3 &player_position);

    // Override the _enter_tree method
    void _enter_tree() override;
};

} // namespace godot

#endif // SKYBOX_H