#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec2 texture_coord;
layout (location = 2) in vec3 normal;

out vec2 vertex_texture_coord;
out vec3 vertex_normal;
out vec3 fragment_position;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
	gl_Position = projection * view * model * vec4(position, 1.0);
	
	vertex_texture_coord = texture_coord;
	//vertex_normal = normal;
	vertex_normal = mat3(transpose(inverse(model))) * normal; // Costly - only use if object is scaled non-uniformly
	fragment_position = vec3(model * vec4(position, 1.0));
}
