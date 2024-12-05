#ifndef TERRAIN_H
#define TERRAIN_H

#include <godot_cpp/classes/mesh_instance3d.hpp>
#include <godot_cpp/classes/array_mesh.hpp>
#include <godot_cpp/classes/surface_tool.hpp>
#include <godot_cpp/templates/vector.hpp>
#include <godot_cpp/classes/standard_material3d.hpp>
#include <godot_cpp/variant/utility_functions.hpp>


namespace godot {

class Terrain : public MeshInstance3D {
    GDCLASS(Terrain, MeshInstance3D);

private:
    // Terrain properties
    int width;                  // Width of the terrain grid
    int height;                 // Height of the terrain grid
    float scale;                // Scale for noise generation
    float max_height;           // Maximum height of the terrain
    Vector<Vector<float>> heightfield; // 2D height values for the terrain

    // Private methods for noise generation and mesh construction
    float perlin_noise(float x, float y) const;  // Perlin noise generator
    float interpolated_noise(float x, float y) const;  // Smoothed and interpolated noise
    void generate_heightfield();  // Generate the heightfield from noise
    Ref<ArrayMesh> generate_mesh();  // Create a mesh from the heightfield

public:
    // Constructor and Destructor
    Terrain();
    ~Terrain();

    // Public method to generate the terrain
    void generate_terrain(int p_width, int p_height, float p_scale, float p_max_height);

    // Method to register functions with Godot
    static void _bind_methods();
};

} // namespace godot

#endif // TERRAIN_H