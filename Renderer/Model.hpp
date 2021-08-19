#pragma once
#include <vector>
#include <map>
#include <string>
#include "Mesh.hpp"
#include "Object.hpp"

/*##############################################################################

	Model

##############################################################################*/

class Model: public Object
{
	/*=========================================
		Types
	=========================================*/	

	public:
	typedef std::shared_ptr<Model>	PtrModel;

	/*=========================================
		Members
	=========================================*/	

	public:
	std::vector<Mesh>		meshes;
	std::vector<PtrModel>	children;

	/*=========================================
		Constructor & Destructor
	=========================================*/

	public:
	Model()=default;
	Model(Model& x)=default;
	Model(Model&& x);

	Model(Mesh& mesh);
	Model(Mesh&& mesh);

	virtual			~Model()=default;
	Model&			operator=(const Model&)=default;

	/*=========================================
		Methods
	=========================================*/

	public:
	void			draw(ShaderOpengl& shader, glm::mat4& world);
	void			add_mesh(Mesh& mesh);
	void			add_mesh(Mesh&& mesh);
	void			add_child(Mesh& mesh);
	void			add_child(Mesh&& mesh);
	void			add_child(Model& model);
	void			add_child(Model&& model);
	void			add_child(PtrModel model);
	PtrModel		copy();			// deep copy
	
	std::pair<glm::vec3, glm::vec3>	get_bounding_box();
};