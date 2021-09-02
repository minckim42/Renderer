#pragma once
#include <glm/glm.hpp>
#define ANIMATOR_N_BONE_MAX 12

struct Vertex
{
	typedef unsigned int	uint;

	glm::vec3	position;
	glm::vec3	normal;
	glm::vec2	tex_coord;
	glm::vec3	tangent;
	glm::vec3	bi_tangent;
	int			bones[ANIMATOR_N_BONE_MAX];
	float		weights[ANIMATOR_N_BONE_MAX];

	Vertex();
	Vertex(const Vertex& x);
	virtual	~Vertex()=default;

	void		add_weight(uint idx, float weight);
	uint		get_num_weight();
};