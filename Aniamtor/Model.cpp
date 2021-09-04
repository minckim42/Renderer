#include <string>
#include <glm/glm.hpp>
#include "Model.hpp"
#include "Material.hpp"
using namespace std;
using namespace glm;

/*##############################################################################

	Model

##############################################################################*/

/*=========================================
	Constructor
=========================================*/

void		Model::draw(Shader& shader, const glm::mat4& world)
{
	for (Mesh::ptr mesh : meshes)
	{
		mesh->draw(shader, world * offset);
	}
	for (Model::ptr model : children)
	{
		model->draw(shader, world * offset);
	}
}

void		Model::draw(Shader& shader, const glm::mat4& world, double time, uint animation)
{
	for (Mesh::ptr mesh : meshes)
	{
		// mesh->draw(shader, world, time);
		mesh->draw(shader, world * offset, time, animation);
	}
	for (Model::ptr model : children)
	{
		model->draw(shader, world * offset, time, animation);
	}
}

void		Model::add_mesh(Mesh::ptr mesh)
{
	meshes.push_back(mesh);
}

void		Model::add_child(ptr x)
{
	children.push_back(x);
}

//------------------------------------------------------------------------------

void		compare_box(Mesh::box& a, Mesh::box b)
{
	for (uint i = 0 ; i < 3 ; i++)
	{
		if (a.first[i] > b.first[i])
			a.first[i] = b.first[i];
		if (a.second[i] < b.second[i])
			a.second[i] = b.second[i];
	}
}
//------------------------------------------------------------------------------

std::pair<glm::vec3, glm::vec3>		Model::get_bounding_box()
{
	Mesh::box	bound = Mesh::box(vec3(INFINITY), vec3(-INFINITY));
	for (Mesh::ptr mesh : meshes)
	{
		compare_box(bound, mesh->get_bounding_box());
	}
	for (Model::ptr child : children)
	{
		compare_box(bound, child->get_bounding_box());
	}
	bound.first = vec3(offset * vec4(bound.first, 1));
	bound.second = vec3(offset * vec4(bound.second, 1));
	return bound;
}