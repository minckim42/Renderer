#pragma once
#include <vector>
#include <memory>
#include <glad/glad.h>
#include "Vertex.hpp"
#include "Material.hpp"
#include "Object.hpp"
#include "ShaderOpengl.hpp"

/*##############################################################################

	Mesh

##############################################################################*/

class Mesh: public Object
{
	/*=========================================
		Types
	=========================================*/
	
	public:
	typedef unsigned int			uint;
	typedef std::vector<glm::vec3>	vector_vec3;
	typedef std::vector<glm::vec2>	vector_vec2;
	typedef std::vector<uint>		vector_uint;
	typedef std::shared_ptr<Mesh>	ptr_mesh;

	/*=========================================
		Members
	=========================================*/

	public:
	std::vector<Vertex>			vertices;
	std::vector<uint>			indices;
	std::shared_ptr<Material>	material;
	uint						vao;
	uint						vbo;
	uint						ebo;

	/*=========================================
		Constructor & Destructor
	=========================================*/

	public:
				Mesh();
				Mesh(
					vector_vec3& 		positions, 
					vector_vec3& 		normals, 
					vector_vec2& 		tex_coords,
					std::vector<uint>&	indices
				);
				Mesh(
					vector_vec3& 		positions, 
					vector_vec3& 		normals, 
					vector_vec2& 		tex_coords, 
					vector_vec3& 		tangents, 
					vector_vec3& 		bi_tangents,
					std::vector<uint>&	indices
				);
				Mesh(const Mesh& x) = default;
	virtual		~Mesh() = default;
	Mesh&		operator=(const Mesh& x);

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
	void		set_tangent();
	void		set_buffer();
	void		draw(ShaderOpengl& shader, glm::mat4& world);

	ptr_mesh	copy();	// deep copy
};

