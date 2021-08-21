#include "Model.hpp"

using namespace std;
using namespace glm;

/*=========================================
	Constructor & Destructor
=========================================*/

Model::Model(Model&& x)
{
	meshes.swap(x.meshes);
	children.swap(x.children);
}

//------------------------------------------------------------------------------

Model::Model(Mesh& mesh)
{
	meshes.emplace_back(mesh);
}

//------------------------------------------------------------------------------

Model::Model(Mesh&& mesh)
{
	meshes.emplace_back(mesh);
}

/*=========================================
	Methods
=========================================*/

void				Model::draw(Shader& shader, glm::mat4& world)
{
	mat4	current = matrix * world;
	for (Mesh& mesh : meshes)
	{
		mesh.draw(shader, current);
	}
	for (shared_ptr<Model> child : children)
	{
		child->draw(shader, current);
	}
}

//------------------------------------------------------------------------------

void				Model::add_mesh(Mesh& mesh)
{
	meshes.emplace_back(mesh);
}

//------------------------------------------------------------------------------

void				Model::add_mesh(Mesh&& mesh)
{
	meshes.emplace_back(mesh);
}

//------------------------------------------------------------------------------

void				Model::add_child(Mesh& mesh)
{
	children.emplace_back(make_shared<Model>(mesh));
}

//------------------------------------------------------------------------------

void				Model::add_child(Mesh&& mesh)
{
	children.emplace_back(make_shared<Model>(mesh));
}

//------------------------------------------------------------------------------

void				Model::add_child(Model& model)
{
	children.emplace_back(model.copy());
}

//------------------------------------------------------------------------------

void				Model::add_child(Model&& model)
{
	children.emplace_back();
	children.back()->meshes.swap(model.meshes);
	children.back()->children.swap(model.children);
}

//------------------------------------------------------------------------------

void				Model::add_child(shared_ptr<Model> model)
{
	children.emplace_back(model);
}

//------------------------------------------------------------------------------

shared_ptr<Model>	Model::copy()
{
	return make_shared<Model>(*this);
}

//------------------------------------------------------------------------------

pair<vec3, vec3>	Model::get_bounding_box()
{
	pair<vec3, vec3>	result(vec3(10000000, 10000000, 10000000), vec3(-10000000, -10000000, -10000000));


	vec3&				vec_min = result.first;
	vec3&				vec_max = result.second;
	for (Mesh& mesh : meshes)
	{
		pair<vec3, vec3>	tmp = mesh.get_bounding_box();
		for (int i = 0 ; i < 3 ; i++)
		{
			vec_min[i] = tmp.first[i] < vec_min[i] ? tmp.first[i] : vec_min[i];
			vec_max[i] = tmp.second[i] > vec_max[i] ? tmp.second[i] : vec_max[i];
		}
	}
	for (shared_ptr<Model> model : children)
	{
		pair<vec3, vec3>	tmp = model->get_bounding_box();
		for (int i = 0 ; i < 3 ; i++)
		{
			vec_min[i] = tmp.first[i] < vec_min[i] ? tmp.first[i] : vec_min[i];
			vec_max[i] = tmp.second[i] > vec_max[i] ? tmp.second[i] : vec_max[i];
		}
	}
	return result;
}