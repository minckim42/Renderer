#pragma once
#include <vector>
#include <memory>
#include <glad/glad.h>
#include "Vertex.hpp"
#include "Material.hpp"
#include "Object.hpp"
#include "Shader.hpp"

/*##############################################################################

	Mesh

##############################################################################*/

class Mesh: public Object
{
	/*=========================================
		Types
	=========================================*/
	
	public:
	typedef unsigned int				uint;
	typedef std::vector<glm::vec3>		vector_vec3;
	typedef std::vector<glm::vec2>		vector_vec2;
	typedef std::vector<uint>			vector_uint;
	// typedef std::shared_ptr<Material>	PtrMaterial;

	/*=========================================
		Members
	=========================================*/

	public:
	std::vector<Vertex>		vertices;
	std::vector<uint>		indices;
	Material*				material;
	uint					vao;
	uint					vbo;
	uint					ebo;

	/*=========================================
		Constructor
	=========================================*/

	public:
	Mesh()=default;
	Mesh(
		vector_vec3& 		positions, 
		vector_vec3& 		normals, 
		vector_vec2& 		tex_coords,
		std::vector<uint>&	indices,
		Material*			material

	);
	Mesh(
		vector_vec3& 		positions, 
		vector_vec3& 		normals, 
		vector_vec2& 		tex_coords, 
		vector_vec3& 		tangents, 
		vector_vec3& 		bi_tangents,
		std::vector<uint>&	indices,
		Material*			material

	);
	Mesh(Mesh& x);
	Mesh(Mesh&& x);
	
	virtual		~Mesh();
	Mesh&		operator=(const Mesh& x);
	Mesh&		operator=(Mesh&& x);

	/*=========================================
		Methods
	=========================================*/

	void		set_vertices(
					vector_vec3& 		positions, 
					vector_vec3& 		normals, 
					vector_vec2& 		tex_coords
				);
	void		set_vertices(		
					vector_vec3& 		positions, 
					vector_vec3& 		normals, 
					vector_vec2& 		tex_coords,
					vector_vec3& 		tangents, 
					vector_vec3& 		bi_tangents
				);
	void		set_tangents();
	void		set_vertex_tangent(uint a, uint b, uint c);
	void		set_buffer();
	void		draw(Shader& shader, glm::mat4& world);
	
	std::pair<glm::vec3, glm::vec3>		get_bounding_box();
};

