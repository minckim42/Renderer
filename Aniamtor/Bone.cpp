#include "Bone.hpp"
#include <iostream>
typedef unsigned int		uint;

using namespace std;
using namespace glm;

//------------------------------------------------------------------------------

// Bone::Bone(vector<mat4>& matrices, const mat4& offset):
// 	matrices(matrices), offset(offset)
// {
// 	idx_mat = matrices.size();
// 	matrices.emplace_back();
// }

//------------------------------------------------------------------------------

Bone::Bone(vector<mat4>& matrices, const mat4& offset, const mat4& world_transform, const string& name):
	matrices(matrices), 
	offset(offset), 
	world_transform(world_transform),
	// world_inverse(inverse(offset) * prev_inverse),
	name(name)
{
	idx_mat = matrices.size();
	matrices.emplace_back();
}


//------------------------------------------------------------------------------

void	Bone::set_matrix(uint animation_id, const mat4& prev, double time)
{
	if (animations.empty())
	{
		// matrix() = mat4(1);
		matrix() = prev * offset;
		// matrix() = prev;
	}
	else
	{
		// matrix() = prev * animations[animation_id].interpolate(time);
		// matrix() = prev * offset * animations[animation_id].interpolate(time);
		matrix() = prev * animations[animation_id].interpolate(time) * offset;
	}
	for (Bone::ptr  child : children)
	{
		child->set_matrix(animation_id, matrix(), time);
		// child->set_matrix(animation_id, matrix() * offset, time);
	}
	matrix() = matrix() * world_transform;
}

//------------------------------------------------------------------------------

// mat4	Bone::local_transform(vec3& position, quat& rotation, vec3& scale)
// {
// 	mat4	result(1.0);
	
// }

//------------------------------------------------------------------------------



//------------------------------------------------------------------------------

mat4&	Bone::matrix()
{
	return (matrices)[idx_mat];
}