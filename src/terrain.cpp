#include "terrain.h"
#include <godot_cpp/core/math.hpp>

using namespace godot;


void Terrain::_bind_methods() {
    ClassDB::bind_method(D_METHOD("generate_terrain", "width", "height", "scale", "max_height"), &Terrain::generate_terrain);
}

Terrain::Terrain() : width(0), height(0), scale(1.0f), max_height(1.0f) {}

Terrain::~Terrain() {}

float Terrain::perlin_noise(float x, float y) const {
    int n = static_cast<int>(x) + static_cast<int>(y) * 57;
    n = (n << 13) ^ n;
    return (1.0f - ((n * (n * n * 15731 + 789221) + 1376312589) & 0x7fffffff) / 1073741824.0f);
}

float Terrain::interpolated_noise(float x, float y) const {
    int ix = static_cast<int>(x);
    int iy = static_cast<int>(y);
    float fx = x - ix;
    float fy = y - iy;

    // Generate noise for the four corners of the grid cell
    float v1 = perlin_noise(ix, iy);
    float v2 = perlin_noise(ix + 1, iy);
    float v3 = perlin_noise(ix, iy + 1);
    float v4 = perlin_noise(ix + 1, iy + 1);

    // Interpolate along x-axis
    float i1 = v1 + fx * (v2 - v1);
    float i2 = v3 + fx * (v4 - v3);

    // Interpolate along y-axis
    return i1 + fy * (i2 - i1);
}

void Terrain::generate_heightfield() {
    heightfield.resize(height);
    for (int y = 0; y < height; ++y) {
        heightfield.write[y].resize(width);
        for (int x = 0; x < width; ++x) {
            heightfield.write[y].write[x] = interpolated_noise(x * scale, y * scale) * max_height;
        }
    }
}

Ref<ArrayMesh> Terrain::generate_mesh() {
    Ref<SurfaceTool> surface_tool;
    surface_tool.instantiate();

    surface_tool->begin(Mesh::PRIMITIVE_TRIANGLES);

    int vertex_count = 0;

    for (int y = 0; y < height - 1; ++y) {
        for (int x = 0; x < width - 1; ++x) {
            Vector3 v0(x * scale, heightfield[y][x], y * scale);
            Vector3 v1((x + 1) * scale, heightfield[y][x + 1], y * scale);
            Vector3 v2(x * scale, heightfield[y + 1][x], (y + 1) * scale);
            Vector3 v3((x + 1) * scale, heightfield[y + 1][x + 1], (y + 1) * scale);

            // Compute normals
            Vector3 normal1 = (v1 - v0).cross(v2 - v0).normalized();
            Vector3 normal2 = (v3 - v1).cross(v2 - v1).normalized();

            // Triangle 1
            surface_tool->set_normal(normal1);
            surface_tool->add_vertex(v0);
            surface_tool->add_vertex(v1);
            surface_tool->add_vertex(v2);
            vertex_count += 3;

            // Triangle 2
            surface_tool->set_normal(normal2);
            surface_tool->add_vertex(v1);
            surface_tool->add_vertex(v3);
            surface_tool->add_vertex(v2);
            vertex_count += 3;
        }
    }
    UtilityFunctions::print("Mesh generated with {0} vertices", vertex_count);

    Ref<ArrayMesh> mesh = surface_tool->commit();

    // Assign a default material to make the mesh visible
    StandardMaterial3D* material = memnew(StandardMaterial3D());
    material->set_albedo(Color(0.5, 0.8, 0.5)); // Greenish terrain color
    mesh->surface_set_material(0, material);    

    return mesh;
}

void Terrain::generate_terrain(int p_width, int p_height, float p_scale, float p_max_height) {
    width = p_width;
    height = p_height;
    scale = p_scale;
    max_height = p_max_height;

    generate_heightfield();
    Ref<ArrayMesh> mesh = generate_mesh();
    set_mesh(mesh);

    // Set the position of the terrain at the origin
    set_position(Vector3(0, 0, 0));
}