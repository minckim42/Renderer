#include "Vertex.hpp"

Vertex::Vertex()
{
	for (uint i = 0 ; i < ANIMATOR_N_BONE_MAX ; i++)
	{
		bones[i] = -1;
		weights[i] = 1;
	}
}

void		Vertex::add_weight(unsigned int idx, float weight)
{
	for (uint i = 0 ; i < ANIMATOR_N_BONE_MAX ; i++)
	{
		if (bones[i] != -1)
			continue;
		bones[i] = idx;
		weights[i] = weight;
	}
}