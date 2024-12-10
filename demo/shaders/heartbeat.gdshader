shader_type spatial;

render_mode unshaded;
render_mode skip_vertex_transform;
render_mode fog_disabled;

uniform sampler2D screen_texture : source_color, hint_screen_texture, filter_nearest_mipmap;

//Higher intesity increases the distortion of the screen during the heartbeat
uniform float intensity : hint_range(0.0, 0.2) = 0.05;
//Larger pulse speed means a shorter heartbeat cycle
uniform float pulse_speed : hint_range(0.0, 10.0) = 8.0;
uniform float break_time : hint_range(0.0, 10.0) = 3.0;
uniform float blur_strength : hint_range(0.0, 1.0) = 0.2;


void vertex() {
    POSITION = vec4(VERTEX, 1.0);
}

// Apply a blur box by averaging neighboring pixels.
/*
vec3 apply_blur(vec2 uv, float strength) {
    vec3 color = vec3(0.0);
    float total = 0.0;

    for (int x = -2; x <= 2; x++) {
        for (int y = -2; y <= 2; y++) {
            vec2 offset = vec2(float(x), float(y)) * 0.003 * strength;
            color += texture(screen_texture, uv + offset).rgb;
            total += 1.0;
        }
    }
    return color / total;
}
*/
/*
float heartbeat_pattern(float time) { 
    float cycle_time = 2.0 / pulse_speed + break_time;
    float local_time = mod(time, cycle_time);

	//The two if statements determine whether it is time for first or second heartbeat
	
    if (local_time < 1.0 / pulse_speed) {
        return sin(local_time * pulse_speed * pi);
    } else if (local_time < 2.0 / pulse_speed) {
        return sin((local_time - 1.0 / pulse_speed) * pulse_speed * pi);
    }
    // The return represents a long pause
    return 0.0;
}

float heartbeat_pattern(float time) {
	// Calculate the heartbeat timing pattern
    float cycle_time = 2.0 / pulse_speed + break_time;
    float local_time = mod(time, cycle_time);
	//Gradually grows and oscillates within [0.0, 1.0] and stops when local_time > 1.0 / pulse_speed
    return max(0.0, sin(local_time * pulse_speed * pi) * step(local_time, 1.0 / pulse_speed));
}
*/
// Apply a blur box by averaging neighboring pixels.

vec3 apply_blur(vec2 uv, float strength) {
    vec3 color = vec3(0.0);
    float total = 0.0;

    for (int x = -2; x <= 2; x++) {
        for (int y = -2; y <= 2; y++) {
            vec2 offset = vec2(float(x), float(y)) * 0.003 * strength;
            color += texture(screen_texture, uv + offset).rgb;
            total += 1.0;
        }
    }
    return color / total;
}
float heartbeat_pattern(float time) { 
    float cycle_time = 2.0 / pulse_speed + break_time;
    float local_time = mod(time, cycle_time);

	//The two if statements determine whether it is time for first or second heartbeat
	
    if (local_time < 1.0 / pulse_speed) {
        return sin(local_time * pulse_speed * 3.14);
    } else if (local_time < 2.0 / pulse_speed) {
        return sin((local_time - 1.0 / pulse_speed) * pulse_speed * 3.14);
    }
    // The return represents a long pause
    return 0.0;
}

void fragment() {
    // Get the heartbeat pattern
    float heartbeat = heartbeat_pattern(TIME);

    // Calculate the scaling factor
    float scale = 1.0 + intensity * heartbeat;

    // Scale UV for heartbeat effect
    vec2 uv = (SCREEN_UV - 0.5) / scale + 0.5;

    // Blur the screen when the heartbeat is happenning
    float blur_intensity = heartbeat * blur_strength;
    vec3 color = apply_blur(uv, blur_intensity);

    ALBEDO = color;
}