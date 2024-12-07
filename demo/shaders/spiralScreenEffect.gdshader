shader_type spatial;

render_mode unshaded;
render_mode skip_vertex_transform;
render_mode depth_draw_always;

// Declare the screen texture
uniform sampler2D SCREEN_TEXTURE : hint_screen_texture, filter_linear_mipmap;

uniform float line_density = 40.0;    // Number of radial streaks
uniform float speed_factor = 1.0;     // Speed of the streak motion
uniform float fade_power = 2.5;       // Controls fading towards the center
uniform vec3 line_color = vec3(1.0, 1.0, 1.0);       // Color of the streaks
uniform vec3 background_color = vec3(0.0, 0.0, 0.0); // Background color
uniform float effect_opacity = 0.5;  // Controls the transparency of the effect (0.0 = fully transparent, 1.0 = fully opaque)

void vertex() {
    POSITION = vec4(VERTEX, 1.0f); // Clip space position
}

void fragment() {
    vec2 uv = SCREEN_UV;

    // Calculate the distance from the center and angle
    vec2 center = vec2(0.5, 0.5);
    vec2 dir = uv - center;
    float dist = length(dir);
    float angle = atan(dir.y, dir.x); // Angle in radians

    // Generate radial streaks based on the angle
    float lines = abs(sin(angle * line_density + TIME * speed_factor));

    // Apply a fade effect towards the center
    float fade = pow(dist, fade_power);

    // Combine the streaks and fade
    float intensity = lines * fade;

    // Output the final color with transparency
    vec3 effect_color = mix(background_color, line_color, intensity);

    // Blend the effect with the background using effect_opacity
    vec4 background = texture(SCREEN_TEXTURE, uv); // Sample the background
    vec3 final_color = mix(background.rgb, effect_color, effect_opacity);

    ALBEDO = final_color;
    ALPHA = effect_opacity; // Set transparency
}