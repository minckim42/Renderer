#version 430 core
layout (location = 0) in vec3	position;
layout (location = 1) in vec3	normal;
layout (location = 2) in vec2	tex_coord;
layout (location = 3) in vec3	tan_x;	// tangent
layout (location = 4) in vec3	tan_y;	// bi_tangent
layout (location = 5) in ivec4	bones0;
layout (location = 6) in ivec4	bones1;
layout (location = 7) in ivec4	bones2;
layout (location = 8) in vec4	weights0;
layout (location = 9) in vec4	weights1;
layout (location = 10) in vec4	weights2;


out vec2	vs_tex_coords;
out vec3	vs_position;
out vec3	vs_normal;
out mat3	mat_face;

uniform mat4	model;
uniform mat4	view;
uniform mat4	projection;
uniform mat4	weight_matrix[200];

mat4	set_transform()
{
	mat4	final_transform = mat4(0.0);
	float	w = 0;
	for (int i = 0 ; i < 4 ; i++)
	{
		if (bones0[i] == -1)
			break;
		if (bones0[i] >= 200)
			break;
		// final_transform += weight_matrix[bones0[i]];
		// final_transform *= weights0[i] * weight_matrix[bones0[i]];
		final_transform += weights0[i] * weight_matrix[bones0[i]];
		w += weights0[i];
	}
	for (int i = 0 ; i < 4 ; i++)
	{
		if (bones1[i] == -1)
			break;
		if (bones1[i] >= 200)
			break;
		// final_transform += weight_matrix[bones1[i]];
		// final_transform *= weights1[i] * weight_matrix[bones1[i]];
		final_transform += weights1[i] * weight_matrix[bones1[i]];
		w += weights1[i];
	}
	for (int i = 0 ; i < 4 ; i++)
	{
		if (bones2[i] == -1)
			break;
		if (bones2[i] >= 200)
			break;
		// final_transform += weight_matrix[bones2[i]];
		// final_transform *= weights2[i] * weight_matrix[bones2[i]];
		final_transform += weights2[i] * weight_matrix[bones2[i]];
		w += weights2[i];
	}
	// final_transform[3][3] = 1;
	return final_transform;
	// return final_transform / w;
}

void main()
{
	vs_tex_coords = tex_coord;


	// mat4	model_final = model;
	// mat4	model_final = model * weight_matrix[5];
	// mat4	model_final = model * weight_matrix[bones0[0]];
	mat4	model_final;
	if (bones0[0] != -1)
		model_final = model * set_transform();
	else
		model_final = model;
	// mat4	model_final = set_transform();
	gl_Position = projection * (view * (model_final * vec4(position, 1)));

	vs_position = mat3(model_final) * vec3(position);

	mat_face = mat3(model_final) * mat3(tan_x, tan_y, normal);
	
	// vs_normal = normalize( mat3(model_final) * normal);
	
	// gl_Position = vec4(normalize(gl_Position.xyz), 1);
	// gl_Position = vec4(normalize(position), 1);
}