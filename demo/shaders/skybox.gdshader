shader_type spatial;

render_mode unshaded; // Ensures no lighting is applied to the material
render_mode cull_disabled;

uniform sampler2D texture_albedo; // The texture for the skybox
uniform float scroll_speed : hint_range(-1.0, 1.0) = 0.05; // Speed of horizontal scrolling

void fragment() {
    // Animate the UV coordinates to scroll the texture horizontally
    vec2 animated_uv = UV;
    animated_uv.x += TIME * scroll_speed; // Scroll horizontally over time

    // Sample the texture using the animated UVs
    ALBEDO = texture(texture_albedo, animated_uv).rgb;
}