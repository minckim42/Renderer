#include "Vertex.hpp"
#include <iostream>
using namespace std;
using namespace glm;

Vertex::Vertex()
{
	for (uint i = 0 ; i < ANIMATOR_N_BONE_MAX ; i++)
	{
		bones[i] = -1;
		weights[i] = 1;
	}
}

Vertex::Vertex(const Vertex& x):
	position(x.position),
	normal(x.normal),
	tex_coord(x.tex_coord),
	tangent(x.tangent),
	bi_tangent(x.bi_tangent)
{
	for (uint i = 0 ; i < ANIMATOR_N_BONE_MAX ; i++)
	{
		bones[i] = x.bones[i];
		weights[i] = x.weights[i];
	}
}

void		Vertex::add_weight(unsigned int idx, float weight)
{
	if (bones[ANIMATOR_N_BONE_MAX - 1] != -1)
		return;
	uint	i = 0;
	while (bones[i] != -1)
		++i;
	bones[i] = idx;
	weights[i] = weight;
}

uint		Vertex::get_num_weight()
{
	uint	i = 0;
	while (i < ANIMATOR_N_BONE_MAX)
	{
		if (bones[i] == -1)
			return i;
		i++;
	}
	return i;
}