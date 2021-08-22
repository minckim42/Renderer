#version 430 core
layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;


out vec3	vs_normal;
out vec3	vs_position;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
	gl_Position = projection * (view * (model * vec4(position, 1)));

	vs_normal = mat3(model) * vec3(normal);
	vs_position = mat3(model) * vec3(position);
}