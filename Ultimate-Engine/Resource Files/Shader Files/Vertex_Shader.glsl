#version 330 core
layout(location = 0) in vec4 in_position;
layout(location = 1) in vec4 in_color;
layout(location = 2) in vec2 in_texcoord;
uniform mat4 model_matrix, view_matrix, projection_matrix;

out vec4 color;
out vec2 out_texcoord;
out vec4 out_position;

void main(){

	color = in_color;
	out_texcoord = in_texcoord;
	out_position = in_position;
	gl_Position = projection_matrix * view_matrix * model_matrix * in_position;
	gl_PointSize =5.5;
}