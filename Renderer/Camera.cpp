#include "Camera.hpp"

using namespace glm;

/*##############################################################################

	Camera

##############################################################################*/

/*=======================================
	Canonical form
=======================================*/

Camera::Camera():
Object(
	vec3(1000, 0, 0), 
	vec3(-1, 0, 0), 
	vec3(0, 0, 1)
),
fovy(pi<float>() / 3), 
aspect(16.f/9), 
z_far(10000), 
z_near(1),
up(0, 0, 1)
{

}

//------------------------------------------------------------------------------

Camera::Camera(
	glm::vec3	position, 
	glm::vec3	direction, 
	glm::vec3	up = vec3(0,0,1), 
	float		z_far = 10000, 
	float		z_near = 1,
	float		fovy = pi<float>() / 3, 
	float		aspect = 16.f/9
):
Object(position, direction, up),
fovy(fovy), 
aspect(aspect), 
z_far(z_far), 
z_near(z_near),
up(up)
{}

//------------------------------------------------------------------------------

void			Camera::update_perspective()
{
	perspective = ::perspective(fovy, aspect, z_near, z_far);
}

//------------------------------------------------------------------------------

void			Camera::update_view()
{
	view = lookAt(get_position(), get_position() + get_direction(), up);
}

//------------------------------------------------------------------------------
