shader_type spatial;

render_mode unshaded; // without this line, the world will attempt to apply lighting to the quad, which will make *everything* look darker (or lighter, depending)
render_mode skip_vertex_transform;
render_mode fog_disabled; // we aren't going to use fog, but putting this here anyways so that you know it would be necessary

uniform sampler2D screen_texture : source_color, hint_screen_texture, filter_nearest_mipmap;

//Determines Shake Factor for X axis
uniform float shakeIntensityX = 40.0;
uniform float shakeDepthX = 0.015;

//Determines Shake Factor for Y Axis
uniform float shakeIntensityY = 10.0;
uniform float shakeDepthY = 0.005;

void vertex() {
	// Called for every vertex the material is visible on.
	POSITION = vec4(VERTEX, 1.0f); // which space is this? (clip space)
}

void fragment() {
    vec4 pixel = textureLod(screen_texture, SCREEN_UV, 0.0); // the third argument has to do with the mip-map level
	
    vec2 pos = SCREEN_UV;

    //Uses Sin and Cos to make a circular like motion to imitate the shaking of a earthquake 
    float offsetX  = shakeDepthX*(sin(TIME*shakeIntensityX));
    float offsetY  = shakeDepthY*(cos(TIME*shakeIntensityY));
    pos.x = pos.x + offsetX;
    pos.y = pos.y + offsetY;

    //Keeps Pos in between 0 and 1 
    pos = clamp(pos, vec2(0.0), vec2(1.0));

    pixel = texture(screen_texture, pos) ;
		
    ALBEDO = pixel.rgb;
}
