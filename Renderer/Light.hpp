#pragma once
#include "Object.hpp"
#include "ShaderOpengl.hpp"

/*##############################################################################

	Light

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
		Constructor
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
