#version 330 core

#define MAX_LIGHTS 4

struct point_light
{
	vec3 position;
	vec3 colour;
	vec3 attenuation;
};

out vec4 colour;

in vec2 vertex_texture_coord;
in vec3 vertex_normal;
in vec3 fragment_position;

uniform int num_lights;
uniform point_light sun;
uniform point_light lights[MAX_LIGHTS];

uniform vec3 viewer_position;

uniform sampler2D diffuse_texture;
uniform sampler2D detail_texture;
uniform float shininess;

void main()
{
    vec3 total_diffuse = vec3(0.0);
    vec3 total_specular = vec3(0.0);
    
    vec3 normal = normalize(vertex_normal);
    vec3 to_camera = normalize(viewer_position);
    
    for (int i = 0; i < num_lights; ++i)
    {
        point_light light = lights[i];
        
        vec3 light_position_norm = normalize(light.position - fragment_position);
        float distance = length(light.position);
        float attenuation_factor = light.attenuation.x + (light.attenuation.y * distance) + (light.attenuation.z * distance * distance);
        
        float brightness = max(dot(normal, light_position_norm), 0.0);
        
        vec3 reflection_direction = reflect(-light_position_norm, normal);
        float specular_strength = pow(max(dot(reflection_direction, to_camera), 0.0), shininess);
        
        total_diffuse += (brightness * light.colour) / attenuation_factor;
        total_specular += (specular_strength * light.colour) / attenuation_factor;
    }
    
    total_diffuse = max(total_diffuse, 0.1);
    
    vec4 diffuse_sample = texture(diffuse_texture, vertex_texture_coord);
    vec4 detail_sample = texture(detail_texture, vertex_texture_coord);
    
    if (detail_sample.g > 0.5)
    {
        total_diffuse = vec3(1.0);
    }
    
    colour = (vec4(total_diffuse, 1.0) * diffuse_sample) + vec4(total_specular * detail_sample.r, 1.0);
}
