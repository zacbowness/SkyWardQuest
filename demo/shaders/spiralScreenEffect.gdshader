shader_type spatial;

// Enable rendering on both sides
render_mode cull_disabled;

// Parameters to control the spiral effect
uniform vec3 base_color = vec3(0.0, 1.0, 0.0);
uniform vec3 secondary_color = vec3(0.0, 0.0, 0.0);
uniform float spiral_speed = 1.0;
uniform float spiral_density = 16.0;
uniform float distortion_strength = 0.5;
uniform float fade_radius = 1.0;
uniform vec2 polar_origin = vec2(0.0, 0.0);

void fragment() {

    vec2 uv = UV * 2.0 - vec2(1.0);

    // Shift the polar origin
    uv -= polar_origin; 
    float radius = length(uv);
    float angle = atan(uv.y, uv.x);

    // Time-based rotation to the spiral
    angle += TIME * spiral_speed;

    // This creates the swirling effect
    float distortion = sin(angle * spiral_density + radius * 10.0) * distortion_strength;
    float spiral = sin(angle * spiral_density + distortion) * 0.5 + 0.5;

    float fade = smoothstep(fade_radius, 0.0, radius);

    vec3 color = mix(secondary_color, base_color, spiral * fade);

    ALBEDO = color;
}