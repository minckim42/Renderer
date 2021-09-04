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
	typedef std::shared_ptr<Model>			ptr;
	typedef std::pair<glm::vec3, glm::vec3>	box;
	typedef unsigned int					uint;

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
	void		draw(Shader& shader, const glm::mat4& world);
	void		draw(Shader& shader, const glm::mat4& world, double time, uint animation);
	void		add_mesh(Mesh::ptr mesh);
	void		add_child(ptr x);
	box			get_bounding_box();
	private:
};