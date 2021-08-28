#include "Bone.hpp"

typedef unsigned int		uint;

using namespace std;
using namespace glm;

//------------------------------------------------------------------------------

static
uint	binary_search(vector<double> times, double value)
{
	uint	left = 0;
	uint	right = times.size();
	double*	data = times.data();

	while (right - left != 1)
	{
		uint	mid = (left + right) / 2;
		if (data[mid] < value)
		{
			left = mid;
		}
		else
		{
			right = mid;
		}
	}
	return left;
}

//------------------------------------------------------------------------------

void	Bone::set_matrix(
			const vec3&	parent_position,
			const quat&	parent_rotation,
			const vec3&	parent_scale,
			double 		time)
{
	quat	rotation = parent_rotation 
					* interpolate_quat_key(rotation_keys, rotation_time, time);
	vec3	position = parent_position 
					+ interpolate_vector_key(position_keys, position_time, time);
	vec3	scale = parent_scale 
					+ interpolate_vector_key(scale_keys, scale_time, time);
	// matrices[idx_mat] = rotate(rotation)
	
}

//------------------------------------------------------------------------------

vec3	Bone::interpolate_vector_key(vector<vec3>& keys, vector<double>& times, double time)
{
	if (time >= times.back())
	{
		return keys.back();
	}
	uint	idx = binary_search(times, time);
	vec3&	a = keys[idx];
	vec3&	b = keys[idx + 1];
	double	factor = (time - times[idx]) / (times[idx + 1] - times[idx]);
	return mix(a, b, factor);
}

//------------------------------------------------------------------------------

quat	Bone::interpolate_quat_key(vector<quat>& keys, vector<double>& times, double time)
{
	if (time >= times.back())
	{
		return keys.back();
	}
	uint	idx = binary_search(times, time);
	quat&	a = keys[idx];
	quat&	b = keys[idx + 1];
	double	factor = (time - times[idx]) / (times[idx + 1] - times[idx]);
	return mix(a, b, factor);
}

//------------------------------------------------------------------------------