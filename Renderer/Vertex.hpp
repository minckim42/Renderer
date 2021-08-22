#pragma once
#include <glm/glm.hpp>

/*##############################################################################

	Object

##############################################################################*/

struct Vertex
{
	/*=========================================
		Members
	=========================================*/
	
	public:
	glm::vec3	position;
	glm::vec3	normal;
	glm::vec2	tex_coord;
	glm::vec3	tangent;
	glm::vec3	bi_tangent;

	/*=========================================
		Constructor & Destructor
	=========================================*/
	
	Vertex()=default;
	Vertex(
		const glm::vec3&	position,
		const glm::vec3&	normal
	);
	Vertex(
		const glm::vec3&	position,
		const glm::vec3&	normal,
		const glm::vec2&	tex_coord
	);
	Vertex(
		const glm::vec3&	position,
		const glm::vec3&	normal,
		const glm::vec2&	tex_coord,
		const glm::vec3&	tangent,
		const glm::vec3&	bi_tangent
	);
	virtual		~Vertex()=default;
};
