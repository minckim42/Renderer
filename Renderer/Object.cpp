#include "Object.hpp"

using namespace glm;

/* constructor */	Object::Object():
matrix(1.0f)
{}

Object&			Object::move(const vec3& v)
{
	matrix[3] += vec4(v, 0);
	return *this;
}

//------------------------------------------------------------------------------

Object&			Object::move_forward(float len)
{
	move(vec3(matrix[0]) * len);
	return *this;
}

//------------------------------------------------------------------------------

Object&			Object::move_left(float len)
{
	move(vec3(matrix[1]) * len);
	return *this;
}

//------------------------------------------------------------------------------

Object&			Object::move_up(float len)
{
	move(vec3(matrix[2]) * len);
	return *this;
}

//------------------------------------------------------------------------------

Object&			Object::pitch(float rad)
{
	rotate(matrix, rad, vec3(matrix[2]));
	return *this;
}

//------------------------------------------------------------------------------

Object&			Object::yaw(float rad, vec3 up)
{
	matrix = rotate(matrix, rad, up);
	return *this;
}

vec3			Object::get_position() const
{
	return vec3(matrix[3]);
}

vec3			Object::get_direction() const
{
	return vec3(matrix[0]);
}

vec3			Object::get_right() const
{
	return vec3(matrix[1]);
}

vec3			Object::get_up() const
{
	return vec3(matrix[2]);
}