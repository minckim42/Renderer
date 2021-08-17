#include "Group.hpp"

using namespace std;
using namespace glm;

/*=========================================
	Constructor & Destructor
=========================================*/

Group::Group(const string& name):
	name(name)
{}

/*=========================================
	Methods
=========================================*/

void				Group::draw(ShaderOpengl& shader, glm::mat4& world)
{
	mat4	current = matrix * world;
	for (shared_ptr<Mesh> mesh : meshes)
	{
		mesh->draw(shader, current);
	}
	for (shared_ptr<Group> child : children)
	{
		child->draw(shader, current);
	}
}

//------------------------------------------------------------------------------

void				Group::add(Mesh& mesh)
{
	meshes.push_back(mesh.copy());
}

//------------------------------------------------------------------------------

void				Group::add(Group& group)
{
	children.push_back(group.copy());
}

//------------------------------------------------------------------------------

void				Group::add(shared_ptr<Mesh> mesh)
{
	meshes.push_back(mesh);
}

//------------------------------------------------------------------------------

void				Group::add(shared_ptr<Group> group)
{
	children.push_back(group);
}

//------------------------------------------------------------------------------

shared_ptr<Group>	Group::copy()
{
	return make_shared<Group>(*this);
}

//------------------------------------------------------------------------------