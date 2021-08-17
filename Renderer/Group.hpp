#pragma once
#include <vector>
#include <map>
#include <string>
#include "Mesh.hpp"
#include "Object.hpp"

/*##############################################################################

	Group

##############################################################################*/

class Group: public Object
{
	/*=========================================
		Types
	=========================================*/	

	public:
	typedef std::shared_ptr<Mesh>	ptr_mesh;
	typedef std::shared_ptr<Group>	ptr_group;

	/*=========================================
		Members
	=========================================*/	

	public:
	std::vector<std::shared_ptr<Mesh>>	meshes;
	std::vector<std::shared_ptr<Group>>	children;
	std::string							name;

	/*=========================================
		Constructor & Destructor
	=========================================*/

	public:
	Group()=default;
	Group(const std::string& name);
	Group(const Group& x)=default;
	
	virtual			~Group()=default;
	Group&			operator=(const Group&)=default;

	/*=========================================
		Methods
	=========================================*/

	public:
	void			draw(ShaderOpengl& shader, glm::mat4& world);
	void			add(Mesh& mesh);
	void			add(Group& group);
	void			add(ptr_mesh mesh);
	void			add(ptr_group group);
	ptr_group		copy();	// deep copy
};