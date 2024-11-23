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

void Map::_ready(){}

void Map::_enter_tree(){
	create_and_add_as_child<StaticBody3D>(static_body, "static_body");
	create_and_add_as_child_of_Node<CollisionShape3D>(collision_shape, "Collider_Shape", static_body);
}

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
    SurfaceTool* surface_tool = memnew(SurfaceTool);
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

	Ref<ArrayMesh> newMesh = surface_tool->commit();
    mesh = *newMesh;

	StandardMaterial3D* material = memnew(StandardMaterial3D);
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
    Ref<ArrayMesh> newMesh = generate_3d_mesh();

	set_mesh(newMesh);  // Directly set the mesh for MeshInstance3D

    // Add StaticBody3D
    
    // Create collision shape
    Ref<ConcavePolygonShape3D> collision_shape_mesh = newMesh->create_trimesh_shape();
	collision_shape->set_shape(collision_shape_mesh);

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

void Map::_bind_methods() {}