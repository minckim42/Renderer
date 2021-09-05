#version 430 core
out vec4	FragColor;
in vec2		vs_tex_coords;
in vec3		vs_position;
in mat3		mat_face;
in vec3		vs_normal;

uniform vec3		eye;
uniform vec3		light_position;
uniform vec3		light_color;
uniform float		light_strength;
uniform mat4		model;
uniform sampler2D	tex_ambient;
uniform sampler2D	tex_diffuse;
uniform sampler2D	tex_specular;
uniform sampler2D	tex_normal;
uniform vec3		ka;
uniform vec3		kd;
uniform vec3		ks;



void main()
{
	vec3	normal_tr = normalize(mat_face * ((texture(tex_normal, vs_tex_coords).xyz * 2 - 1)));
	// vec3	normal_tr = normalize(mat_face * vec3(0, 0, 1));
	// vec3	normal_tr = mat_face * vec3(0, 1, 0);
	// vec3	normal_tr = mat_face * vec3(0, 1, 0);

	vec3	light_dir = light_position - vs_position;
	vec3	light_dir_norm = normalize(light_dir);

	float	strength = light_strength * light_strength / dot(light_dir, light_dir);

	vec3	eye_dir_norm = normalize(eye - vs_position);
	vec3	flec_dir_norm = normalize(reflect(-light_dir, normal_tr));

	vec3	ambient = (texture(tex_ambient, vs_tex_coords).xyz * ka)
						 * light_color;
	vec3	diffuse = (texture(tex_diffuse, vs_tex_coords).xyz * kd)
						 * light_color * max(0, dot(light_dir_norm, normal_tr)) ;
	vec3	specular = (texture(tex_specular, vs_tex_coords).xyz * ks)
						 * light_color * max(0, dot(eye_dir_norm, flec_dir_norm));

	FragColor = vec4((ambient + diffuse + specular) * strength, 1);
	
	// FragColor = vec4(normal_tr, 1);
	// FragColor = texture(tex_diffuse, vs_tex_coords);
	// FragColor = vec4(1, 1, 1, 1);
}