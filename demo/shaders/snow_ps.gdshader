shader_type particles;

// Attribution: Burning torus particle effect adapted from the provided code in the OpenGL version of COMP3501.

uniform float num_particles;

const float loop_radius = 5.0;
const float circle_radius = 1.0;
const float maxspray = 0.5;

const vec3 base_color = vec3(0.8, 0.15, 0.01);

#include "res://shaders/helpers.gdshaderinc"

// TRANSFORM[3].xyz is starting position/orientation in this function
// VELOCITY
// COLOR
void start(){
	// calculate color; check in spatial shader to see how the alpha is used!
	float u, v, w;
	u = pseudo_random_from_inputs(float(INDEX), 0.23678);
	v = pseudo_random_from_inputs(float(INDEX), 0.6321);
	w = pseudo_random_from_inputs(float(INDEX), 0.7654);
	//COLOR = vec4(u, v, w, 1.0) * 0.1; 
	COLOR = vec4(base_color, 0.4);
	
	// calculate starting position
	u = pseudo_random_from_inputs(float(INDEX), 0.4532);
	v = pseudo_random_from_inputs(float(INDEX), 1.2942);
	w = pseudo_random_from_inputs(float(INDEX), 0.2942);

    // Make a square out of the starting posistions 
    float square_size = 5.0; 
    float x = (u * 2.0 - 1.0) * square_size; 
    float y = v * square_size; 
    float z = (w * 2.0 - 1.0) * square_size; 

    // Assign particle position within the square
    vec3 position = vec3(x, y, z);
	COLOR = vec4(float(INDEX)/num_particles, 0.0, 1.0 - (float(INDEX)/num_particles), 0.3); // The red channel of the color stores the particle id
		
	VELOCITY = vec3(0.0, 0.0, 0.0); // We are going to simulate the motion in the vertex shader!
	
	// calculated above to position the particles at their 'birth' location!
	TRANSFORM[3].xyz = position;
	
	// EMISSION_TRANSFORM is the transformation for the GPUParticles3D Node
	TRANSFORM = EMISSION_TRANSFORM * TRANSFORM; // if you want the transform to be in local space rather than working in world space
	
	float speed = pseudo_random_from_inputs(float(INDEX), 0.23141);
	float dir = pseudo_random_from_inputs(float(INDEX), 0.45534);
	CUSTOM.x = speed;
	CUSTOM.y = dir;
	CUSTOM.w = LIFETIME;
}

void process(){
}