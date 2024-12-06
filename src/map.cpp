#include "map.h"
#include <godot_cpp/classes/array_mesh.hpp>
#include <godot_cpp/classes/surface_tool.hpp>
#include <godot_cpp/classes/array_mesh.hpp>
#include <godot_cpp/classes/surface_tool.hpp>
#include <godot_cpp/classes/standard_material3d.hpp>

using namespace godot;

Map::Map()
    : width(256), height(256), octaves(4), persistence(0.5), scale(1.0), max_height(10.0), mountain_scale(50.0),random_seed(12345) {
    Vector3 start(50.0f, 0.0f, 50.0f);
    Vector3 stop(200.0f, 0.0f, 200.0f);
    float path_width = 10.0f;
    }

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
            // Force edge points to y = 0
            if (x == 0 || x == width - 1 || y == 0 || y == height - 1) {
                heightfield.write[y].write[x] = 0.0f; 
            } else {
                heightfield.write[y].write[x] = mountain_noise(x * scale, y * scale);
            }
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

void Map::scatter_circles_on_mesh(int circle_count, float circle_radius) {
    if (heightfield.is_empty() || heightfield[0].is_empty()) {
        UtilityFunctions::print("Heightfield is not generated.");
        return;
    }

    RandomNumberGenerator* rng = memnew(RandomNumberGenerator);
    rng->randomize();

    for (int i = 0; i < circle_count; ++i) {
        int x = rng->randf_range(0, width - 1);
        int y = rng->randf_range(0, height - 1);
        float terrain_height = heightfield[y][x];

        Node3D* circle_node = memnew(Node3D);
        circle_node->set_name("Circle_" + String::num_int64(i));
        circle_node->set_position(Vector3(x * scale, terrain_height + 0.5, y * scale));

        MeshInstance3D* mesh_instance = memnew(MeshInstance3D);
        Ref<SphereMesh> sphere_mesh = memnew(SphereMesh);
        sphere_mesh->set_radius(circle_radius);
        mesh_instance->set_mesh(sphere_mesh);

        Ref<StandardMaterial3D> material = memnew(StandardMaterial3D);
        material->set_albedo(Color(1.0, 0.0, 0.0)); // Bright red
        mesh_instance->set_material_override(material);

        circle_node->add_child(mesh_instance);
        add_child(circle_node);
    }

    memdelete(rng);
}

Vector<Vector3> Map::scatter_props(const Vector<Vector<float>> &heightfield, int width, int height, float scale, int prop_count) {
    Vector<Vector3> positions;

    if (heightfield.is_empty() || heightfield[0].is_empty()) {
        UtilityFunctions::print("Heightfield is not generated.");
        return positions; // Return an empty list if the heightfield is invalid
    }

    RandomNumberGenerator *rng = memnew(RandomNumberGenerator);
    rng->set_seed(random_seed); // Set a fixed seed for reproducible results
    //rng->randomize(); Use this line instead of the one above if you want seed to be randomized

    for (int i = 0; i < prop_count; ++i) {
        // Randomly select a position on the heightfield
        int x = rng->randf_range(0, width - 1);
        int y = rng->randf_range(0, height - 1);
        float terrain_height = heightfield[y][x];

        // Calculate the world position for the prop
        Vector3 position = Vector3(x * scale, terrain_height - 0.15, y * scale);
        positions.push_back(position); // Add the position to the list
    }

    memdelete(rng);
    return positions;
}
/*
void Map::create_flat_path(Vector3 start, Vector3 stop, float path_width) {
    if (heightfield.is_empty() || heightfield[0].is_empty()) {
        UtilityFunctions::print("Heightfield is not generated.");
        return;
    }

    // Convert start and stop to grid coordinates
    start /= scale;
    stop /= scale;

    // Determine the direction vector of the path
    Vector2 start_2d(start.x, start.z);
    Vector2 stop_2d(stop.x, stop.z);
    Vector2 direction = stop_2d - start_2d;
    float length = direction.length();
    direction /= length; // Normalize the direction vector

    // Loop over the points along the path
    for (float t = 0; t <= length; t += 1.0f) {
        Vector2 point_2d = start_2d + direction * t;

        int center_x = static_cast<int>(point_2d.x);
        int center_z = static_cast<int>(point_2d.y);

        // Flatten a square area around the path center
        int half_width = static_cast<int>(path_width / (2.0f * scale));
        for (int dz = -half_width; dz <= half_width; ++dz) {
            for (int dx = -half_width; dx <= half_width; ++dx) {
                int x = center_x + dx;
                int z = center_z + dz;

                // Ensure we don't go out of bounds
                if (x >= 0 && x < width && z >= 0 && z < height) {
                    heightfield.write[z].write[x] = 0.0f; // Flatten to y = 0
                }
            }
        }
    }

    UtilityFunctions::print("Flat path created from " + start + " to " + stop + ".");
}
*/
void Map::print_heightfield() const {
    if (heightfield.is_empty() || heightfield[0].is_empty()) {
        UtilityFunctions::print("Heightfield is empty.");
        return;
    }

    for (int y = 0; y < height; ++y) {
        String row = "";
        for (int x = 0; x < width; ++x) {
            row += String::num_real(heightfield[y][x]) + " ";
        }
        UtilityFunctions::print(row);
    }
}

const Vector<Vector<float>>& Map::get_heightfield() const {
    return heightfield;
}

int Map::get_width() const {
    return width;
}

int Map::get_height() const {
    return height;
}

float Map::get_scale() const {
    return scale;
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
