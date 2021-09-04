#pragma once
#include <glm/glm.hpp>
#include "Object.hpp"

/*##############################################################################

	Camera

##############################################################################*/

class Camera : public Object
{
	/*=========================================
		Members
	=========================================*/

	public:
	float				fovy;
	float				aspect;
	float				z_far;
	float				z_near;
	glm::mat4			projection;
	glm::mat4			view;

	/*=======================================
		Constructor
	=======================================*/

	public:
	Camera();
	Camera(
		glm::vec3	position,
		glm::vec3	direction,
		glm::vec3	up = glm::vec3(0, 0, 1),
		float		fovy = glm::pi<float>() / 3,
		float		aspect = 16.f / 9,
		float		z_far = 10000,
		float		z_near = 1
	);

	/*=======================================
		Methods
	=======================================*/

	public:
	void				update_projection();
	void				update_view();
};