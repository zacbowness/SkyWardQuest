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

    // Variables used to manipulate the generated heightfield and are passed in from an outside class
    int width, height;
    int octaves;
    float persistence;
    float scale;
    float max_height;
    float mountain_scale;
    int random_seed;



    Vector<Vector<float>> heightfield;

	CollisionShape3D* collision_shape;
	StaticBody3D* static_body;

    ArrayMesh* mesh;

    // Noise generation methods
    float perlin_noise(float x, float y) const;
    float interpolated_noise(float x, float y) const;
    float multiscale_noise(float x, float y) const;
    float terrain_noise(float x, float y) const;

    void smooth_heightfield();
    void advanced_smooth_heightfield();


protected:
    static void _bind_methods();

public:
    Map();
    ~Map();

	void _ready();
	void _enter_tree();


    // Terrain generation method with customizable parameters
    void generate_terrain(int p_width, int p_height, int p_octaves, float p_persistence, float p_scale, float p_max_height, float p_mountain_scale);
    void generate_mountain(int p_width, int p_height, int p_octaves, float p_persistence, float p_scale, float p_max_height, float p_mountain_scale, Vector3 start, Vector3 stop, float path_width, bool path);

    Vector<Vector3> scatter_props(const Vector<Vector<float>> &heightfield, int width, int height, float scale, int prop_count);
    void create_flat_path(Vector3 start, Vector3 stop, float path_width); 

    void add_mesh(const Vector<Vector<float>> &heightfield, Vector3 position, Color colour);
    Ref<ArrayMesh> generate_3d_mesh(const Vector<Vector<float>> &heightfield, Color colour);
    void generate_mountain(int p_width, int p_height, int p_octaves, float p_persistence, float p_scale, float p_max_height, float p_mountain_scale, float offset);
    void generate_mountain_heightfield(float offset);
    void generate_terrain(int p_width, int p_height, int p_octaves, float p_persistence, float p_scale, float p_max_height, float p_mountain_scale, float offset);
    void generate_heightfield(float offset);
    
    //Heightfield getter function
    const Vector<Vector<float>>& get_heightfield() const;

    template <class T>
	bool create_and_add_as_child(T* &pointer, String name);
    
    template <class T>
	bool create_and_add_as_child_of_Node(T* &pointer, String name, Node* parent);
};

} // namespace godot

#endif // MAP_H