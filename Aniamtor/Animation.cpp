#include "Animation.hpp"
#include <iostream>
using namespace glm;
using namespace std;

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

mat4	Animation::interpolate(double time)
{
	quat	rotation = interpolate_quat_key(rotation_keys, rotation_time, time);
	vec3	position = interpolate_vector_key(position_keys, position_time, time);
	vec3	scaling = interpolate_vector_key(scale_keys, scale_time, time);

	mat4	local_transform = mat4(1);
	// local_transform = local_transform * scale(mat4(1.0), scaling);
	// local_transform = local_transform * toMat4(rotation);
	local_transform[3] += vec4(position, 0);
	// cout << to_string(local_transform) << endl;

	// mat4	local_transform = scale(mat4(1.0), scaling);
	// local_transform = toMat4(rotation) * local_transform;
	// local_transform[3] += vec4(position, 0);

	// return mat4(1);
	return local_transform;
	return inverse(local_transform);
	// return mat4(
	// 	cos(time * 0.00002), -sin(time * 0.00002), 0, 0,
	// 	sin(time * 0.00002), cos(time * 0.00002), 0, 0,
	// 	0, 0, 1, 0,
	// 	0, 0, 0, 1
	// );
	// return mat4(
	// 	1, 0, 0, 0,
	// 	0, 1, 0, 0,
	// 	0, 0, 1, 0,
	// 	0, 0, time * 0.001, 1
	// );
}

//------------------------------------------------------------------------------

vec3	Animation::interpolate_vector_key(vector<vec3>& keys, vector<double>& times, double time)
{
	if (time >= times.back())
	{
		return keys.back();
	}
	uint	idx = binary_search(times, time);
	vec3&	a = keys[idx];
	vec3&	b = keys[idx + 1];
	double	factor = (time - times[idx]) / (times[idx + 1] - times[idx]);
	// return a * (1 - factor) + b * factor;
	return mix(a, b, factor);
}

//------------------------------------------------------------------------------

quat	Animation::interpolate_quat_key(vector<quat>& keys, vector<double>& times, double time)
{
	if (time >= times.back())
	{
		return keys.back();
	}
	uint	idx = binary_search(times, time);
	quat&	a = keys[idx];
	quat&	b = keys[idx + 1];
	float	factor = (time - times[idx]) / (times[idx + 1] - times[idx]);
	return slerp(a, b, factor);
	// return normalize(slerp(a, b, factor));
	// return mix(a, b, factor);
}

