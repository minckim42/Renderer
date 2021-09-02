#include "Mesh.hpp"
#include <iostream>


using namespace std;
using namespace glm;

Mesh::Mesh():
	vao(0),vbo(0),ebo(0)
{}

Mesh::~Mesh()
{
	if (vao)
		glDeleteVertexArrays(1, &vao);
	if (vbo)
		glDeleteBuffers(1, &vbo);
	if (ebo)
		glDeleteBuffers(1, &ebo);
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
	
	glEnableVertexAttribArray(5);
	glVertexAttribIPointer(5, 4, GL_INT, sizeof(Vertex), (void*)(offsetof(Vertex, bones)));
	glEnableVertexAttribArray(6);
	glVertexAttribIPointer(6, 4, GL_INT, sizeof(Vertex), (void*)(offsetof(Vertex, bones) + 16));
	glEnableVertexAttribArray(7);
	glVertexAttribIPointer(7, 4, GL_INT, sizeof(Vertex), (void*)(offsetof(Vertex, bones) + 32));
	
	glEnableVertexAttribArray(8);
	glVertexAttribPointer(8, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(offsetof(Vertex, weights)));
	glEnableVertexAttribArray(9);
	glVertexAttribPointer(9, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(offsetof(Vertex, weights) + 16));
	glEnableVertexAttribArray(10);
	glVertexAttribPointer(10, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(offsetof(Vertex, weights) + 32));

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(uint) * indices.size(), indices.data(), GL_STATIC_DRAW);

	glBindVertexArray(0);
}

void		Mesh::draw(Shader& shader, mat4 world, double time)
{
	glBindVertexArray(vao);
	update_bone(shader, 0, mat4(1), time);
	if (bone != nullptr)
		world = mat4(1);
	draw_base(shader, world);
}

void		Mesh::update_bone(Shader& shader, uint animation_id, mat4 world, double time)
{
	bone->set_matrix(animation_id, world, time);
	for (uint i = 0 ; i < matrices.size() ; i++)
	{
		shader.set_uniform("weight_matrix[" + to_string(i) + ']', matrices[i]);
		// cout << to_string(matrices[i]) << endl;
	}
}

void		Mesh::draw_base(Shader& shader, mat4 world)
{
	shader.set_uniform("model", world);
	// shader.set_uniform("model", mat4(1.0));
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

//------------------------------------------------------------------------------

void		Mesh::set_tangents()
{
	for (uint i = 0 ; i < indices.size() ; i += 3)
	{
		set_vertex_tangent(indices[i], indices[i + 1], indices[i + 2]);
		set_vertex_tangent(indices[i + 1], indices[i + 2], indices[i]);
		set_vertex_tangent(indices[i + 2], indices[i], indices[i + 1]);
	}
}

//------------------------------------------------------------------------------

void		Mesh::set_vertex_tangent(uint a, uint b, uint c)
{
	//cout << a << "   " << b << "   " << c << endl;
	vec3	t_u = normalize(vertices[b].position - vertices[a].position);
	vec3	t_v = normalize(vertices[c].position - vertices[a].position);
	vec3	t_n = normalize(vertices[a].normal);

	vec3	m_u = normalize(vec3(vertices[b].tex_coord - vertices[a].tex_coord, 0));
	vec3	m_v = normalize(vec3(vertices[c].tex_coord - vertices[a].tex_coord, 0));
	vec3	m_n = vec3(0, 0, 1);

	mat3	T(cross(cross(t_n, t_u), t_n), cross(cross(t_n, t_v), t_n), t_n);
	mat3	M(m_u, m_v, m_n);
	mat3	N = T * inverse(M);
	float	det = determinant(N);
	vertices[a].tangent = (N[0]) / det;
	vertices[a].bi_tangent = (N[1]) / det;
}


//------------------------------------------------------------------------------

void		compare_vector(Mesh::box& a, vec3& point)
{
	for (uint i = 0 ; i < 3 ; i++)
	{
		if (a.first[i] > point[i])
			a.first[i] = point[i];
		if (a.second[i] < point[i])
			a.second[i] = point[i];
	}
}

//------------------------------------------------------------------------------

Mesh::box		Mesh::get_bounding_box()
{
	Mesh::box	bound = Mesh::box(vec3(INFINITY), vec3(-INFINITY));
	if (vertices.empty())
		return bound;
	for (Vertex& vertex : vertices)
	{
		compare_vector(bound, vertex.position);
	}
	return bound;
}