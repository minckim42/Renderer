#include "Object.hpp"

using namespace glm;

/*##############################################################################

	Object

##############################################################################*/

/*=======================================
	Canonical form
=======================================*/

/* constructor */	Object::Object():
matrix(1.0f)
{}

//------------------------------------------------------------------------------

/* constructor */	Object::Object(const mat4& mat):
matrix(mat)
{}

//------------------------------------------------------------------------------

/* constructor */	Object::Object(vec3 position, vec3 x, vec3 z)
{
	// direction = normalize(direction);
	z = normalize(z);
	vec3	y = normalize(cross(z, x));
	x = cross(y, z);
	matrix = mat4(vec4(x, 0), vec4(y, 0), vec4(z, 0), vec4(position, 1));
}

/*=======================================
	Methods
=======================================*/

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
	rotate(matrix, -rad, get_left());
	return *this;
}

//------------------------------------------------------------------------------

Object&			Object::yaw(float rad, vec3 up)
{
	matrix = rotate(matrix, rad, up);
	return *this;
}

//------------------------------------------------------------------------------

vec3			Object::get_position() const
{
	return vec3(matrix[3]);
}

//------------------------------------------------------------------------------

vec3			Object::get_direction() const
{
	return vec3(matrix[0]);
}

//------------------------------------------------------------------------------

vec3			Object::get_left() const
{
	return vec3(matrix[1]);
}

//------------------------------------------------------------------------------

vec3			Object::get_up() const
{
	return vec3(matrix[2]);
}