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

void	Animation::create_first_key()
{
	// first_key = translate(position_keys[0]) * toMat4(rotation_keys[0]);
	first_key = translate(position_keys[0]) * toMat4(rotation_keys[0]) * scale(mat4(1), scale_keys[0]);
	// first_key = scale(mat4(1), scale_keys[0]) * toMat4(rotation_keys[0]) * translate(position_keys[0]);
	first_key = inverse(first_key);
}

//------------------------------------------------------------------------------

mat4	Animation::interpolate(double time)
{
	// return mat4(1);

	quat	rotation = interpolate_quat_key(rotation_keys, rotation_time, time);
	vec3	position = interpolate_vector_key(position_keys, position_time, time);
	vec3	scaling = interpolate_vector_key(scale_keys, scale_time, time);

	// mat4	scale_mat = scale(mat4(1), scaling / scale_keys[0]);
	// mat4	rotate_mat = inverse(toMat4(rotation_keys[0])) * toMat4(rotation);
	// mat4	position_mat = translate(position - position_keys[0]);
	// return position_mat  * rotate_mat * scale_mat;
	// return position_mat * scale_mat * rotate_mat;
	// return rotate_mat * position_mat * scale_mat;
	// return rotate_mat * scale_mat * position_mat;
	// return scale_mat * rotate_mat * position_mat;
	// return scale_mat * position_mat * rotate_mat;



	// mat4	scale_mat = scale(mat4(1), scaling / scale_keys[0]);
	// mat4	rotate_mat = toMat4(rotation) * inverse(toMat4(rotation_keys[0]));
	// mat4	position_mat = translate(position - position_keys[0]);
	// return position_mat  * rotate_mat * scale_mat;
	// return position_mat * scale_mat * rotate_mat;
	// return rotate_mat * position_mat * scale_mat;
	// return rotate_mat * scale_mat * position_mat;
	// return scale_mat * rotate_mat * position_mat;
	// return scale_mat * position_mat * rotate_mat;


	mat4	transform = translate(position) * scale(scaling) * toMat4(rotation);
	// mat4	transform = translate(position) * scale(scaling);
	// return transform * first_key;
	// mat4	transform = toMat4(rotation) * scale(scaling) *  translate(position);
	return first_key * transform;
	return transform;

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
	return normalize(slerp(a, b, factor));
}

