#include "Mesh.hpp"
#include <iostream>
using namespace std;
using namespace glm;

/*=========================================
	Constructor
=========================================*/

Mesh::Mesh(
	vector_vec3& 	positions, 
	vector_vec3& 	normals, 
	vector_vec2& 	tex_coords,
	vector<uint>&	indices, 
	Material*		material
):
	indices(indices),
	material(material),
	vao(0), vbo(0), ebo(0)
{
	set_vertices(positions, normals, tex_coords);
	set_buffer();
}

//------------------------------------------------------------------------------

Mesh::Mesh(
	vector_vec3& 	positions, 
	vector_vec3& 	normals, 
	vector_vec2& 	tex_coords, 
	vector_vec3& 	tangents, 
	vector_vec3& 	bi_tangents,
	vector<uint>&	indices, 
	Material*		material
):
	indices(indices),
	material(material),
	vao(0), vbo(0), ebo(0)
{
	set_vertices(positions, normals, tex_coords, tangents, bi_tangents);
	set_buffer();
}

//------------------------------------------------------------------------------

Mesh::Mesh(Mesh& x)
{
	vertices = x.vertices;
	indices = x.indices;
	material = x.material;
	vao = x.vao;
	vbo = x.vbo;
	ebo = x.ebo;
	set_buffer();
}

//------------------------------------------------------------------------------

Mesh::Mesh(Mesh&& x):
	vao(x.vao),
	vbo(x.vbo),
	ebo(x.ebo)
{
	vertices.swap(x.vertices);
	indices.swap(x.indices);
	material = x.material;
	x.vao = 0;
	x.vbo = 0;
	x.ebo = 0;
}

//------------------------------------------------------------------------------

Mesh::~Mesh()
{
	if (vao)
		glDeleteVertexArrays(1, &vao);
	if (vbo)
		glDeleteBuffers(1, &vbo);
	if (ebo)
		glDeleteBuffers(1, &ebo);
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

//------------------------------------------------------------------------------

Mesh&		Mesh::operator=(Mesh&& x)
{
	if (&x == this)
		return *this;
	vertices.swap(x.vertices);
	indices.swap(x.indices);
	material = x.material;
	swap(vao, x.vao);
	swap(vbo, x.vbo);
	swap(ebo, x.ebo);
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
	set_tangents();
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

void		Mesh::set_tangents()
{
	for (int i = 0 ; i < indices.size() ; i += 3)
	{
		set_vertex_tangent(indices[i], indices[i + 1], indices[i + 2]);
		set_vertex_tangent(indices[i + 1], indices[i + 2], indices[i]);
		set_vertex_tangent(indices[i + 2], indices[i], indices[i + 1]);
	}
}

void		Mesh::set_vertex_tangent(uint a, uint b, uint c)
{
	// vec3	u = vertices[b].position - vertices[a].position;
	// vec3	v = vertices[c].position - vertices[a].position;
	// vec3	n = normalize(vertices[a].normal);

	// vertices[a].tangent = (cross(n, u), n);
	// vertices[a].bi_tangent = (cross(n, v), n);


	vec3	t_u = normalize(vertices[b].position - vertices[a].position);
	vec3	t_v = normalize(vertices[c].position - vertices[a].position);
	vec3	t_n = normalize(vertices[a].normal);

	vec3	m_u = normalize(vec3(vertices[b].tex_coord - vertices[a].tex_coord, 0));
	vec3	m_v = normalize(vec3(vertices[c].tex_coord - vertices[a].tex_coord, 0));
	vec3	m_n = vec3(0, 0, 1);

	mat3	T(cross(cross(t_n, t_u), t_n), cross(cross(t_n, t_v), t_n), t_n);
	mat3	M(m_u, m_v, m_n);
	mat3	N = T * inverse(M);
	vertices[a].tangent = (N[0]);
	vertices[a].bi_tangent = (N[1]);
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
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(offsetof(Vertex, position)));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(offsetof(Vertex, normal)));
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(offsetof(Vertex, tex_coord)));
	glEnableVertexAttribArray(3);
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(offsetof(Vertex, tangent)));
	glEnableVertexAttribArray(4);
	glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(offsetof(Vertex, bi_tangent)));

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(uint) * indices.size(), indices.data(), GL_STATIC_DRAW);

	glBindVertexArray(0);
}
#include <iostream>
void		Mesh::draw(ShaderOpengl& shader, mat4& world)
{
	glBindVertexArray(vao);
	shader.set_uniform("model", world * matrix);
	if (material != nullptr)
	{
		shader.set_uniform("tex_ambient", 0);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, material->map_kd);	// diffuse

		shader.set_uniform("tex_diffuse", 1);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, material->map_kd);

		shader.set_uniform("tex_specular", 2);
		glActiveTexture(GL_TEXTURE2);
		glBindTexture(GL_TEXTURE_2D, material->map_ks);

		shader.set_uniform("tex_normal", 3);
		glActiveTexture(GL_TEXTURE3);
		glBindTexture(GL_TEXTURE_2D, material->map_bump);

		shader.set_uniform("ka", material->param.ka);
		shader.set_uniform("ks", material->param.ks);
		shader.set_uniform("kd", material->param.kd);
	}
	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
}

pair<vec3, vec3>	Mesh::get_bounding_box()
{
	pair<vec3, vec3>	result(vertices.front().position, vertices.front().position);
	vec3&				vec_min = result.first;
	vec3&				vec_max = result.second;
	for (Vertex& vertex : vertices)
	{
		vec3&	position = vertex.position;
		for (int i = 0 ; i < 3 ; i++)
		{
			vec_min[i] = position[i] < vec_min[i] ? position[i] : vec_min[i];
			vec_max[i] = position[i] > vec_max[i] ? position[i] : vec_max[i];
		}
	}
	return result;
}