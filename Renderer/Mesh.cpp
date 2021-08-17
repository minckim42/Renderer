#include "Mesh.hpp"

using namespace std;
using namespace glm;

/*=========================================
	Special members
=========================================*/

/* con */	Mesh::Mesh()
{}

//------------------------------------------------------------------------------

/* con */	Mesh::Mesh(
				vector_vec3& 		positions, 
				vector_vec3& 		normals, 
				vector_vec2& 		tex_coords,
				std::vector<uint>&	indices
			):
	indices(indices)
{
	set_vertices(positions, normals, tex_coords);
}

//------------------------------------------------------------------------------

/* con */	Mesh::Mesh(
				vector_vec3& 		positions, 
				vector_vec3& 		normals, 
				vector_vec2& 		tex_coords, 
				vector_vec3& 		tangents, 
				vector_vec3& 		bi_tangents,
				std::vector<uint>&	indices
			):
	indices(indices)
{
	set_vertices(positions, normals, tex_coords, tangents, bi_tangents);
}

//------------------------------------------------------------------------------

Mesh&		Mesh::operator=(const Mesh& x)
{
	if (&x == this)
		return *this;
	vertices = x.vertices;
	indices = x.indices;
	material = x.material;
	return *this;
}

/*=========================================
	Methods
=========================================*/


//------------------------------------------------------------------------------

void		Mesh::set_vertices(
				vector_vec3& 		positions, 
				vector_vec3& 		normals, 
				vector_vec2& 		tex_coords
			)
{
	for (int i = 0 ; i < positions.size() ; i++)
	{
		vertices.emplace_back(
			positions[i],
			normals[i],
			tex_coords[i]
		);
	}
	set_tangent();
}

void		Mesh::set_vertices(		
				vector_vec3& 		positions, 
				vector_vec3& 		normals, 
				vector_vec2& 		tex_coords,
				vector_vec3& 		tangents, 
				vector_vec3& 		bi_tangents
			)
{
	for (int i = 0 ; i < positions.size() ; i++)
	{
		vertices.emplace_back(
			positions[i],
			normals[i],
			tex_coords[i],
			tangents[i],
			bi_tangents[i]
		);
	}
}

void		Mesh::set_tangent()
{

}

void		Mesh::set_buffer()
{
	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vbo);
	glGenBuffers(1, &ebo);
	glBindVertexArray(vao);
	
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vec3), (void*)(offsetof(Vertex, position)));
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(vec3), (void*)(offsetof(Vertex, normal)));
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(vec3), (void*)(offsetof(Vertex, tex_coord)));
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(vec3), (void*)(offsetof(Vertex, tangent)));
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, sizeof(vec3), (void*)(offsetof(Vertex, bi_tangent)));

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(uint) * indices.size(), indices.data(), GL_STATIC_DRAW);

	glBindVertexArray(0);
}

void		Mesh::draw(ShaderOpengl& shader, mat4& world)
{
	glBindVertexArray(vao);
	if (material != nullptr)
	{
		shader.set_uniform("tex_ambient", 0);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, material->map_ka);

		shader.set_uniform("tex_diffuse", 1);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, material->map_kd);

		shader.set_uniform("tex_ambient", 2);
		glActiveTexture(GL_TEXTURE2);
		glBindTexture(GL_TEXTURE_2D, material->map_ks);

		shader.set_uniform("tex_ambient", 3);
		glActiveTexture(GL_TEXTURE3);
		glBindTexture(GL_TEXTURE_2D, material->map_bump);

		shader.set_uniform("ka", material->param.ka);
		shader.set_uniform("ka", material->param.ks);
		shader.set_uniform("ka", material->param.kd);
	}
	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
}


Mesh::ptr_mesh	Mesh::copy()	// deep copy
{
	return make_shared<Mesh>(Mesh(*this));
}