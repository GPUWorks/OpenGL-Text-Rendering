#version 330 core

layout(location = 0) out vec4 out_color;

in vec4 color;

uniform sampler2D textura1;
uniform sampler2D textura2;
uniform sampler2D textura3;
uniform int is_text;
uniform float limit_left;
uniform float limit_right;

in vec2 out_texcoord;
in vec4 out_position;

void main(){
 
	vec3 text = texture(textura1, out_texcoord).xyz;

	if(is_text == 1) {
		if(text.x < 0.8 && text.y < 0.8 && text.z < 0.8) {
			out_color.w = 0;
		}
		else
 			out_color = vec4(texture(textura3, out_texcoord).xyz, 1);
	}
	else {
		out_color = vec4(texture(textura2, out_texcoord).xyz, 1);
	}

	if(is_text == 1) {
		if(out_position.x < limit_left)
			out_color.w = 0.0f;

		if(out_position.x > limit_right)
			out_color.w = 0.0f;
	}
}