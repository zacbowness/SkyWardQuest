#include "map.h"
#include <godot_cpp/classes/array_mesh.hpp>
#include <godot_cpp/classes/surface_tool.hpp>
#include <godot_cpp/classes/array_mesh.hpp>
#include <godot_cpp/classes/surface_tool.hpp>
#include <godot_cpp/classes/standard_material3d.hpp>

using namespace godot;

Map::Map()
    : width(256), height(256), octaves(4), persistence(0.5), scale(1.0), max_height(10.0), mountain_scale(50.0) {}

Map::~Map() {}

float Map::perlin_noise(float x, float y) const {
    int n = static_cast<int>(x) + static_cast<int>(y) * 57;
    n = (n << 13) ^ n;
    return (1.0f - ((n * (n * n * 15731 + 789221) + 1376312589) & 0x7fffffff) / 1073741824.0f);
}

float Map::interpolated_noise(float x, float y) const {
    int ix = static_cast<int>(x);
    int iy = static_cast<int>(y);
    float fx = x - ix;
    float fy = y - iy;

    float v1 = perlin_noise(ix, iy);
    float v2 = perlin_noise(ix + 1, iy);
    float v3 = perlin_noise(ix, iy + 1);
    float v4 = perlin_noise(ix + 1, iy + 1);

    float i1 = v1 + fx * (v2 - v1);
    float i2 = v3 + fx * (v4 - v3);
    return i1 + fy * (i2 - i1);
}

float Map::multiscale_noise(float x, float y) const {
    float total = 0.0f;
    float frequency = 0.5f;
    float amplitude = 1.0f;
    float max_value = 0.0f;

    for (int i = 0; i < octaves; ++i) {
        total += interpolated_noise(x * frequency, y * frequency) * amplitude;
        max_value += amplitude;

        amplitude *= persistence;
        frequency *= 1.5f;
    }

    return total / max_value;//normalize the values
}

float Map::mountain_noise(float x, float y) const {
    float base_noise = perlin_noise(x * 0.05f, y * 0.05f);
    float detail_noise = multiscale_noise(x, y);

    if (base_noise > 0.2f) {
        return (base_noise + detail_noise) * mountain_scale;
    }

    return detail_noise * max_height;
}

void Map::generate_heightfield() {
    heightfield.resize(height);
    for (int y = 0; y < height; ++y) {
        heightfield.write[y].resize(width);
        for (int x = 0; x < width; ++x) {
            heightfield.write[y].write[x] = mountain_noise(x * scale, y * scale);
        }
    }

    advanced_smooth_heightfield();
}

void Map::smooth_heightfield() {
    Vector<Vector<float>> smoothed = heightfield;

    for (int y = 1; y < height - 1; ++y) {
        for (int x = 1; x < width - 1; ++x) {
            Vector<float> current_row = smoothed.write[y];

            float smoothed_value = (
                heightfield[y][x] +
                heightfield[y - 1][x] +
                heightfield[y + 1][x] +
                heightfield[y][x - 1] +
                heightfield[y][x + 1]
            ) / 5.0f;

            current_row.write[x] = smoothed_value;
        }
    }

    heightfield = smoothed;
}

void Map::advanced_smooth_heightfield() {
    Vector<Vector<float>> smoothed = heightfield;
    const float kernel[3][3] = {
        { 0.077847, 0.123317, 0.077847 },
        { 0.123317, 0.195346, 0.123317 },
        { 0.077847, 0.123317, 0.077847 }
    };

    for (int y = 1; y < height - 1; ++y) {
        for (int x = 1; x < width - 1; ++x) {
            float smoothed_value = 0.0f;
            for (int ky = -1; ky <= 1; ++ky) {
                for (int kx = -1; kx <= 1; ++kx) {
                    smoothed_value += heightfield[y + ky][x + kx] * kernel[ky + 1][kx + 1];
                }
            }
            smoothed.write[y].write[x] = smoothed_value;
        }
    }

    heightfield = smoothed;
}

Ref<ArrayMesh> Map::generate_3d_mesh() {
    Ref<SurfaceTool> surface_tool;
    surface_tool.instantiate();
    surface_tool->begin(Mesh::PRIMITIVE_TRIANGLES);

    for (int y = 0; y < height - 1; ++y) {
        for (int x = 0; x < width - 1; ++x) {
            Vector3 v0(x * scale, heightfield[y][x], y * scale);
            Vector3 v1((x + 1) * scale, heightfield[y][x + 1], y * scale);
            Vector3 v2(x * scale, heightfield[y + 1][x], (y + 1) * scale);
            Vector3 v3((x + 1) * scale, heightfield[y + 1][x + 1], (y + 1) * scale);

            Vector3 normal1 = (v1 - v0).cross(v2 - v0).normalized();
            Vector3 normal2 = (v3 - v1).cross(v2 - v1).normalized();

            surface_tool->set_normal(normal1);
            surface_tool->add_vertex(v0);
            surface_tool->add_vertex(v1);
            surface_tool->add_vertex(v2);

            surface_tool->set_normal(normal2);
            surface_tool->add_vertex(v1);
            surface_tool->add_vertex(v3);
            surface_tool->add_vertex(v2);
        }
    }

    Ref<ArrayMesh> mesh = surface_tool->commit();

    Ref<StandardMaterial3D> material;
    material.instantiate();
    material->set_albedo(Color(0.1, 0.9, 0.1));
    mesh->surface_set_material(0, material);

    return mesh;
}

void Map::generate_terrain(int p_width, int p_height, int p_octaves, float p_persistence, float p_scale, float p_max_height, float p_mountain_scale) {
    width = p_width;
    height = p_height;
    octaves = p_octaves;
    persistence = p_persistence;
    scale = p_scale;
    max_height = p_max_height;
    mountain_scale = p_mountain_scale;

    generate_heightfield();
    Ref<ArrayMesh> mesh = generate_3d_mesh();

    if (!mesh.is_null()) {
        set_mesh(mesh);  // Directly set the mesh for MeshInstance3D

        // Add StaticBody3D
        StaticBody3D* static_body = memnew(StaticBody3D);
        create_and_add_as_child(static_body, "static_body");

        // Create collision shape
        CollisionShape3D* collision_shape = memnew(CollisionShape3D);
        Ref<Shape3D> collision_shape_mesh = mesh->create_trimesh_shape();

        collision_shape->set_shape(collision_shape_mesh);
        create_and_add_as_child_of_Node(collision_shape, "Collider_Shape", static_body);
    }
    set_position(Vector3(0, 0, 0));
}

template <class T>
// returns true if pointer is brand-new; false if retrieved from SceneTree
bool Map::create_and_add_as_child(T* &pointer, String name){

	Node* child = find_child(name);
	
	if(child == nullptr){
		pointer = memnew(T);
		pointer->set_name(name);
		add_child(pointer);
		pointer->set_owner(get_tree()->get_edited_scene_root());
		return true;
	}
	else{
		pointer = dynamic_cast<T*>(child);
		return false;
	}
}

template <class T>
// returns true if pointer is brand-new; false if retrieved from SceneTree
bool Map::create_and_add_as_child_of_Node(T* &pointer, String name, Node* parent){
	
	Node* child = find_child(name);//find node with the given name

	if(child == nullptr){//if child node was not found, create it
		pointer = memnew(T);
		pointer->set_name(name);
		parent->add_child(pointer);
		pointer->set_owner(get_tree()->get_edited_scene_root());
		return true;
	} else {
		pointer = dynamic_cast<T*>(child);//if node with name already exists, assign it to pointer
		return false;
	}
}

void Map::_bind_methods() {
    ClassDB::bind_method(D_METHOD("generate_terrain", "width", "height", "octaves", "persistence", "scale", "max_height", "mountain_scale"), &Map::generate_terrain);
}

/*
void Map::generate_terrain(int p_width, int p_height, int p_octaves, float p_persistence, float p_scale, float p_max_height, float p_mountain_scale) {
    width = p_width;
    height = p_height;
    octaves = p_octaves;
    persistence = p_persistence;
    scale = p_scale;
    max_height = p_max_height;
    mountain_scale = p_mountain_scale;

    generate_heightfield();
    mesh = generate_3d_mesh();

    if (!mesh.is_null()){
        set_mesh(mesh);

        // Add StaticBody3D
        StaticBody3D* static_body = memnew(StaticBody3D);
        add_child(static_body);

        // Create collision shape
        CollisionShape3D* collision_shape = memnew(CollisionShape3D);
        Ref<Shape3D> collision_shape_mesh = mesh->create_trimesh_shape();

        if (!collision_shape_mesh.is_null()) {
            collision_shape->set_shape(collision_shape_mesh);
            static_body->add_child(collision_shape);
            collision_shape->set_owner(get_owner());
            UtilityFunctions::print("CollisionShape3D added successfully.");

    set_position(Vector3(0, 0, 0));       
}

*/

/*
void Map::generate_terrain(int p_width, int p_height, int p_octaves, float p_persistence, float p_scale, float p_max_height, float p_mountain_scale) {
    width = p_width;
    height = p_height;
    octaves = p_octaves;
    persistence = p_persistence;
    scale = p_scale;
    max_height = p_max_height;
    mountain_scale = p_mountain_scale;

    generate_heightfield();
    Ref<ArrayMesh> mesh = generate_3d_mesh();

    if (!mesh.is_null()) {
        set_mesh(mesh);  // Directly set the mesh for MeshInstance3D
        UtilityFunctions::print("3D terrain mesh successfully generated.");
    } else {
        UtilityFunctions::print("Error: Mesh generation failed.");
    }

    set_position(Vector3(0, 0, 0));
}

Ref<ArrayMesh> Map::generate_3d_mesh() {
    Ref<SurfaceTool> surface_tool;
    surface_tool.instantiate();
    surface_tool->begin(Mesh::PRIMITIVE_TRIANGLES);

    for (int y = 0; y < height - 1; ++y) {
        for (int x = 0; x < width - 1; ++x) {
            Vector3 v0(x * scale, heightfield[y][x], y * scale);
            Vector3 v1((x + 1) * scale, heightfield[y][x + 1], y * scale);
            Vector3 v2(x * scale, heightfield[y + 1][x], (y + 1) * scale);
            Vector3 v3((x + 1) * scale, heightfield[y + 1][x + 1], (y + 1) * scale);

            Vector3 normal1 = (v1 - v0).cross(v2 - v0).normalized();
            Vector3 normal2 = (v3 - v1).cross(v2 - v1).normalized();

            surface_tool->set_normal(normal1);
            surface_tool->add_vertex(v0);
            surface_tool->add_vertex(v1);
            surface_tool->add_vertex(v2);

            surface_tool->set_normal(normal2);
            surface_tool->add_vertex(v1);
            surface_tool->add_vertex(v3);
            surface_tool->add_vertex(v2);
        }
    }

    Ref<ArrayMesh> mesh = surface_tool->commit();

    Ref<StandardMaterial3D> material;
    material.instantiate();
    material->set_albedo(Color(0.1, 0.9, 0.1));
    mesh->surface_set_material(0, material);

    return mesh;
}

void Map::generate_terrain(int p_width, int p_height, int p_octaves, float p_persistence, float p_scale, float p_max_height, float p_mountain_scale) {
    width = p_width;
    height = p_height;
    octaves = p_octaves;
    persistence = p_persistence;
    scale = p_scale;
    max_height = p_max_height;
    mountain_scale = p_mountain_scale;

    generate_heightfield();
    Ref<ArrayMesh> mesh = generate_3d_mesh();

    if (!mesh.is_null()) {
        set_mesh(mesh);  // Directly set the mesh for MeshInstance3D

        // Add StaticBody3D
        StaticBody3D* static_body = memnew(StaticBody3D);
        create_and_add_as_child(static_body, "static_body");

        // Create collision shape
        CollisionShape3D* collision_shape = memnew(CollisionShape3D);
        Ref<Shape3D> collision_shape_mesh = mesh->create_trimesh_shape();

        collision_shape->set_shape(collision_shape_mesh);
        create_and_add_as_child_of_Node(collision_shape, "Collider_Shape", static_body);
    }
    set_position(Vector3(0, 0, 0));
}


*/

/*
//Currently this does not work but plan to implement later
void Map::apply_grassy_material() {
    Ref<StandardMaterial3D> grassy_material;
    grassy_material.instantiate();

    // Set the material's properties to resemble grass
    grassy_material->set_albedo(Color(0.2, 0.8, 0.2)); // Green color for grass
    grassy_material->set_roughness(1.0);               // Grass is not shiny
    grassy_material->set_metallic(0.0);                // Grass is not metallic

    // Apply texture (optional)
    // If you have a grassy texture, load it and apply it as albedo
    // Ref<Texture2D> grass_texture = ResourceLoader::get_singleton()->load("res://path_to_grass_texture.png");
    // if (grass_texture.is_valid()) {
    //     grassy_material->set_texture(StandardMaterial3D::TEXTURE_ALBEDO, grass_texture);
    // }

    // Apply the material to the mesh
    Ref<ArrayMesh> mesh = get_mesh();
    if (!mesh.is_null()) {
        mesh->surface_set_material(0, grassy_material);
        UtilityFunctions::print("Grassy material applied to the mesh.");
    } else {
        UtilityFunctions::print("Error: Mesh is null. Cannot apply material.");
    }
}
*/