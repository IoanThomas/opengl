#version 330 core

struct light
{
	vec3 position;
	
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

out vec4 colour;

in vec2 vertex_texture_coord;
in vec3 vertex_normal;
in vec3 fragment_position;

uniform light sun;
uniform vec3 viewer_position;
uniform sampler2D diffuse_texture;
uniform sampler2D specular_texture;
uniform float shininess;

void main()
{
	vec3 ambient = sun.ambient * vec3(texture(diffuse_texture, vertex_texture_coord));
	
	vec3 normal = normalize(vertex_normal);
	vec3 sun_direction = normalize(sun.position - fragment_position);
	float diffuse_strength = max(dot(normal, sun_direction), 0.0);
	vec3 diffuse = diffuse_strength * sun.diffuse * vec3(texture(diffuse_texture, vertex_texture_coord));
	
	vec3 viewer_direction = normalize(viewer_position - fragment_position);
	vec3 reflection_direction = reflect(-sun_direction, normal);
	float specular_strength = pow(max(dot(viewer_direction, reflection_direction), 0.0), shininess);
	vec3 specular = specular_strength * sun.specular * vec3(texture(specular_texture, vertex_texture_coord));
	
	colour = vec4(ambient + diffuse + specular, 1.0);
	//colour = texture(diffuse_texture, vertex_texture_coord);
}
