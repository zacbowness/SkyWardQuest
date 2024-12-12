shader_type spatial;

render_mode unshaded; 
render_mode cull_disabled;

uniform sampler2D texture_albedo; 
uniform float scroll_speed_x : hint_range(-1.0, 1.0) = 0.05;

void fragment() {
    // Generates UV coordinates
    vec3 normalized_pos = normalize(VERTEX);
    vec2 uv;
    uv.x = 0.5 + atan(normalized_pos.z, normalized_pos.x) / (2.0 * 3.14159); // X: Longitude
    uv.y = 0.5 - asin(normalized_pos.y) / 3.14159; // Y: Latitude

    // Scrolling effect
    uv.x += TIME * scroll_speed_x;
    uv.x = mod(uv.x, 1.0);

    vec3 color = texture(texture_albedo, uv).rgb;
    ALBEDO = color;
}