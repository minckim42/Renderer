#pragma once
#include <memory>
#include <vector>
#include <string>

#include "Mesh.hpp"
#include "Material.hpp"
#include "Shader.hpp"

/*##############################################################################

	Model

##############################################################################*/

class Model
{
	/*=========================================
		Types
	=========================================*/

	public:
	typedef std::shared_ptr<Model>	ptr;

	/*=========================================
		Members
	=========================================*/
	public:
	std::vector<Mesh::ptr>	meshes;
	std::vector<ptr>		children;
	glm::mat4				offset;

	/*=========================================
		Constructor
	=========================================*/
	public:
	Model() = default;
	Model(const Model& x);
	Model(const Mesh& mesh);

	/*=========================================
		Methods
	=========================================*/
	public:
	void		draw(Shader& shader, glm::mat4 world, double time);
	void		add_mesh(Mesh::ptr mesh);
	void		add_child(ptr x);

	private:
};