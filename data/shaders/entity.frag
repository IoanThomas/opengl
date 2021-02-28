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
uniform sampler2D detail_texture;
uniform float shininess;

void main()
{
    vec4 diffuse_sample = texture(diffuse_texture, vertex_texture_coord);
    vec4 detail_sample = texture(detail_texture, vertex_texture_coord);
    
	vec3 ambient = sun.ambient;
	
	vec3 normal = normalize(vertex_normal);
	vec3 sun_direction = normalize(sun.position - fragment_position);
	float diffuse_strength = max(dot(normal, sun_direction), 0.0);
	vec3 diffuse = diffuse_strength * sun.diffuse;
	
	vec3 viewer_direction = normalize(viewer_position - fragment_position);
	vec3 reflection_direction = reflect(-sun_direction, normal);
	float specular_strength = pow(max(dot(viewer_direction, reflection_direction), 0.0), shininess);
	vec3 specular = specular_strength * sun.specular * detail_sample.r;
    
    if (detail_sample.g > 0.5)
    {
        diffuse = vec3(1.0);
    }
	
	colour = (diffuse_sample * vec4(ambient + diffuse, 1.0)) + vec4(specular, 1.0);
}
