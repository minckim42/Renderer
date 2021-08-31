#include "Camera.hpp"

using namespace glm;

/*##############################################################################

	Camera

##############################################################################*/

/*=======================================
	Constructor
=======================================*/

Camera::Camera():
Object(
	vec3(1000, 0, 0), 
	vec3(-1, 0, 0), 
	vec3(0, 0, 1)
),
fovy(pi<float>() / 3), 
aspect(16.f/9), 
z_far(2000), 
z_near(1),
up(0, 0, 1)
{
	update_projection();
	update_view();
}

//------------------------------------------------------------------------------

Camera::Camera(
	glm::vec3	position, 
	glm::vec3	direction, 
	glm::vec3	up,
	float		fovy,
	float		aspect,
	float		z_far,
	float		z_near
):
Object(position, direction, up),
up(up),
fovy(fovy), 
aspect(aspect), 
z_far(z_far), 
z_near(z_near)
{
	update_projection();
	update_view();
}

//------------------------------------------------------------------------------

void			Camera::update_projection()
{
	projection = ::perspective(fovy, aspect, z_near, z_far);
}

//------------------------------------------------------------------------------

void			Camera::update_view()
{
	view = lookAt(get_position(), get_position() + get_direction(), up);
}

//------------------------------------------------------------------------------
