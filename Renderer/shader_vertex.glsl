#version 430 core
layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 tex_coord;
layout (location = 3) in vec3 tan_x;	// tangent
layout (location = 4) in vec3 tan_y;	// bi_tangent
// layout (location = 5) in vec3 tan_z;


out vec2	vs_tex_coords;
out vec3	vs_position;
out mat3	mat_face;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
	vs_tex_coords = tex_coord;    
	gl_Position = projection * (view * (model * vec4(position, 1)));

	vs_position = mat3(model) * vec3(position);

	mat_face = mat3(model) * mat3(tan_x, tan_y, normal);
	
	
	// gl_Position = (vec4(position, 1));
}