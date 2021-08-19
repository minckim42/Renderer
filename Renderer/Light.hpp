#pragma once
#include "Object.hpp"
#include "ShaderOpengl.hpp"

/*##############################################################################

	Object

##############################################################################*/

class Light: public Object
{
	/*=========================================
		Members
	=========================================*/

	public:
	float		strength;
	glm::vec3	color;

	/*=========================================
		Constructor & Destructor
	=========================================*/

	public:
				Light();
				Light(glm::vec3 position, float strength);
	virtual		~Light()=default;

	/*=========================================
		Methods
	=========================================*/

	public:
	void		draw(ShaderOpengl& shader);
};
