#include "Object.hpp"
#include <iostream>
using namespace glm;
using namespace std;

/*##############################################################################

	Object

##############################################################################*/

/*=======================================
	Constructor
=======================================*/

Object::Object():
matrix(1.0f), up(0, 0, 1)
{}

//------------------------------------------------------------------------------

Object::Object(const mat4& mat):
matrix(mat), up(mat[2])
{}

//------------------------------------------------------------------------------

Object::Object(vec3 position, vec3 x, vec3 z):
up(normalize(z))
{
	// direction = normalize(direction);
	vec3	front = normalize(x);
	vec3	left = normalize(cross(up, front));
	front = cross(left, up);
	matrix = mat4(vec4(front, 0), vec4(left, 0), vec4(up, 0), vec4(position, 1));
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
	vec3	position = get_position();
	set_position(vec3(0, 0, 0));
	matrix = rotate(-rad, get_left()) * matrix;
	set_position(position);
	return *this;
}

//------------------------------------------------------------------------------

Object&			Object::yaw(float rad)
{
	vec3	position = get_position();
	set_position(vec3(0, 0, 0));
	matrix = rotate(rad, get_up()) * matrix;
	set_position(position);
	return *this;
}

//------------------------------------------------------------------------------

Object&			Object::yaw(float rad, vec3 up)
{
	vec3	position = get_position();
	set_position(vec3(0, 0, 0));
	matrix = rotate(rad, up) * matrix;
	set_position(position);
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

//------------------------------------------------------------------------------

void			Object::set_identity()
{
	matrix = mat4(1.0f);
}

//------------------------------------------------------------------------------

void			Object::set_position(const vec3& v)
{
	matrix[3] = vec4(v, 1);
}




