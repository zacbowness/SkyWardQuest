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

    //creates a smoothing effect for the heightfield
    void advanced_smooth_heightfield();


protected:
    static void _bind_methods();

public:
    //Default Constructor and Destructor
    Map();
    ~Map();

	void _ready();

    // Add's children to the Node
	void _enter_tree();


    // Terrain generation method with customizable parameters
    void generate_terrain(int p_width, int p_height, int p_octaves, float p_persistence, float p_scale, float p_max_height, float p_mountain_scale);
    void generate_mountain(int p_width, int p_height, int p_octaves, float p_persistence, float p_scale, float p_max_height, float p_mountain_scale, Vector3 start, Vector3 stop, float path_width, bool path);

    // Returns a collection of vectors that represent points on the heightfield
    // Uses a set seed to calculate the positions on the heightfield
    Vector<Vector3> scatter_props(const Vector<Vector<float>> &heightfield, int width, int height, float scale, int prop_count);

    // sets the mesh for heightfield
    void add_mesh(const Vector<Vector<float>> &heightfield, Vector3 position, Color colour);

    // Creates mesh for a heightfield
    Ref<ArrayMesh> generate_3d_mesh(const Vector<Vector<float>> &heightfield, Color colour);

    // Both create heightfields
    void generate_mountain_heightfield(float offset);
    void generate_heightfield(float offset);

    // Function called to initialiase values and determines generated heightfield based on the offset value
    void generate_terrain(int p_width, int p_height, int p_octaves, float p_persistence, float p_scale, float p_max_height, float p_mountain_scale, float offset);
    
    // Heightfield getter function
    const Vector<Vector<float>>& get_heightfield() const;

    // Template class used to add a node as a child of given parent node, returns bool if node was added
    template <class T>
	bool create_and_add_as_child(T* &pointer, String name);

    // Template class used to add a node as a child of the map class, returns bool if node was added
    template <class T>
	bool create_and_add_as_child_of_Node(T* &pointer, String name, Node* parent);
};

} // namespace godot

#endif // MAP_H