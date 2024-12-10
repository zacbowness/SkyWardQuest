shader_type spatial;

// Enable rendering on both sides
render_mode cull_disabled;

// Parameters to control the spiral effect
uniform vec3 base_color = vec3(0.0, 1.0, 0.0); // Main color of the spiral
uniform vec3 secondary_color = vec3(0.0, 0.0, 0.0); // Background color
uniform float spiral_speed = 1.0; // Speed of rotation
uniform float spiral_density = 16.0; // Number of spiral arms
uniform float distortion_strength = 0.5; // Strength of distortion
uniform float fade_radius = 1.0; // Radius where the effect fades out
uniform vec2 polar_origin = vec2(0.0, 0.0); // Offset for polar coordinates

void fragment() {
    // Map UV to [-1, 1] range
    vec2 uv = UV * 2.0 - vec2(1.0);

    // Apply polar origin offset
    uv -= polar_origin; // Shift the polar origin

    // Calculate polar coordinates
    float radius = length(uv);
    float angle = atan(uv.y, uv.x);

    // Add a time-based rotation to the spiral
    angle += TIME * spiral_speed;

    // Create a swirling spiral effect
    float distortion = sin(angle * spiral_density + radius * 10.0) * distortion_strength;
    float spiral = sin(angle * spiral_density + distortion) * 0.5 + 0.5;

    // Fade the spiral based on distance from the center
    float fade = smoothstep(fade_radius, 0.0, radius);

    // Combine colors based on the spiral and fade values
    vec3 color = mix(secondary_color, base_color, spiral * fade);

    // Output the final color
    ALBEDO = color;
}