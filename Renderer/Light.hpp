#pragma once
#include "Object.hpp"

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

	/*=========================================
		Constructor & Destructor
	=========================================*/

	public:
				Light()=default;
				Light(glm::vec3 position, float strength);
	virtual		~Light()=default;
};
