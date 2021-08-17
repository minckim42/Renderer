#include "Vertex.hpp"

Vertex::Vertex(
	const glm::vec3&	position,
	const glm::vec3&	normal,
	const glm::vec2&	tex_coord
):
	position(position),
	normal(normal),
	tex_coord(tex_coord),
	tangent(),
	bi_tangent()
{

}

Vertex::Vertex(
	const glm::vec3&	position,
	const glm::vec3&	normal,
	const glm::vec2&	tex_coord,
	const glm::vec3&	tangent,
	const glm::vec3&	bi_tangent
):
	position(position),
	normal(normal),
	tex_coord(tex_coord),
	tangent(tangent),
	bi_tangent(bi_tangent)
{

}