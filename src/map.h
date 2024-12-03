#ifndef MAP_H
#define MAP_H

#include <godot_cpp/classes/mesh_instance3d.hpp>
#include <godot_cpp/classes/array_mesh.hpp>
#include <godot_cpp/classes/surface_tool.hpp>
#include <godot_cpp/templates/vector.hpp>
#include <godot_cpp/classes/standard_material3d.hpp>
#include <godot_cpp/variant/utility_functions.hpp>
#include <godot_cpp/classes/image_texture.hpp>
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/classes/static_body3d.hpp>
#include <godot_cpp/classes/collision_shape3d.hpp>
#include <godot_cpp/classes/concave_polygon_shape3d.hpp>
#include <godot_cpp/classes/scene_tree.hpp>
#include <godot_cpp/classes/random_number_generator.hpp> // Random number generator
#include <godot_cpp/classes/sphere_mesh.hpp> //Mesh for circles, can be removed for final implementation
#include <godot_cpp/classes/resource_loader.hpp> //resource loader for textures

namespace godot {

class Map : public MeshInstance3D {  // Inherit from MeshInstance3D
    GDCLASS(Map, MeshInstance3D);

private:
    int width, height;
    int octaves;
    float persistence;
    float scale;
    float max_height;
    float mountain_scale;
    Vector<Vector<float>> heightfield;

	CollisionShape3D* collision_shape;
	StaticBody3D* static_body;

    ArrayMesh* mesh;

    // Noise generation methods
    float perlin_noise(float x, float y) const;
    float interpolated_noise(float x, float y) const;
    float multiscale_noise(float x, float y) const;
    float mountain_noise(float x, float y) const;

    // Terrain generation methods
    void generate_heightfield();
    void smooth_heightfield();
    void advanced_smooth_heightfield();  // Advanced smoothing function (Gaussian blur)
    void apply_grassy_material();

protected:
    static void _bind_methods();

public:
    Map();
    ~Map();

	void _ready();
	void _enter_tree();


    // Terrain generation method with customizable parameters
    void generate_terrain(int p_width, int p_height, int p_octaves, float p_persistence, float p_scale, float p_max_height, float p_mountain_scale);
     void scatter_circles_on_mesh(int circle_count, float circle_radius);// function scatters circles across the mesh and can be replaced later

    // Add the function declaration for generating the 3D mesh
    Ref<ArrayMesh> generate_3d_mesh();

    template <class T>
	bool create_and_add_as_child(T* &pointer, String name);

    template <class T>
	bool create_and_add_as_child_of_Node(T* &pointer, String name, Node* parent);
};

} // namespace godot

#endif // MAP_H

/*
Explanation of Parameters:
p_width (int): The width of the terrain grid (number of horizontal tiles or vertices).
p_height (int): The height of the terrain grid (number of vertical tiles or vertices).
p_octaves (int): The number of layers of noise to generate for the terrain. More octaves generally result in more detailed terrain (higher values add more fine-grained features).
p_persistence (float): A value between 0 and 1 that controls how much each successive octave (layer of noise) contributes to the final result. Lower values result in smoother terrain, and higher values create more detail.
p_scale (float): A scaling factor that controls how stretched or compressed the terrain is. Larger values result in broader terrain features (e.g., mountains, valleys).
p_max_height (float): The maximum height for the terrain's features. This will control how tall the mountains can be.
p_mountain_scale (float): A scaling factor specifically for the height of the mountains. Higher values will result in taller mountains, and lower values will make the mountains shorter.
*/