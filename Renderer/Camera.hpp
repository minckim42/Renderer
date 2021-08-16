#pragma once
#include "Object.hpp"

/*##############################################################################

	Camera

##############################################################################*/

class Camera: public Object
{
	/*=========================================
		Members
	=========================================*/
	
	public:
	float				z_far;
	float				z_near;
	float				fovy;
	float				aspect;
	glm::vec3			up;
	glm::mat4			perspective;
	glm::mat4			view;

	/*=======================================
		Canonical form
	=======================================*/
	
	public:
	/*consturctor*/		Camera();
	/*consturctor*/		Camera(
		glm::vec3	position, 
		glm::vec3	direction, 
		glm::vec3	up = vec3(0,0,1), 
		float		fovy = glm::pi / 3, 
		float		aspect = 16.f/9, 
		float		z_far = 10000, 
		float		z_near = 1
	);

	/*=======================================
		Methods
	=======================================*/
	
	public:
	void				update_perspective();
	void				update_view();
}