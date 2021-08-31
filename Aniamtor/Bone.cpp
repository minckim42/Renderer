#include "Bone.hpp"
#include <iostream>
typedef unsigned int		uint;

using namespace std;
using namespace glm;

//------------------------------------------------------------------------------

Bone::Bone(vector<glm::mat4>& matrices, const glm::mat4& offset):
	matrices(matrices), offset(offset)
{
	idx_mat = matrices.size();
	matrices.emplace_back();
}


//------------------------------------------------------------------------------

void	Bone::set_matrix(uint animation_id, const mat4& prev, double time)
{
	matrix() = prev * animations[animation_id].interpolate(time) * offset;
	for (Bone::ptr  child : children)
	{
		child->set_matrix(animation_id, matrix(), time);
	}
	matrix() = matrix() * world_inverse;
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