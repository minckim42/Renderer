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

void		Model::draw(Shader& shader, glm::mat4 world, double time)
{
	for (Mesh::ptr mesh : meshes)
	{
		// mesh->draw(shader, world, time);
		mesh->draw(shader, world * offset, time);
	}
	for (Model::ptr model : children)
	{
		model->draw(shader, world * offset, time);
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