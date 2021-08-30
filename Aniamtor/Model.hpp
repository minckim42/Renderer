#pragma once
#include <memory>
#include <vector>
#include <string>

#include "Mesh.hpp"
#include "Material.hpp"

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

	/*=========================================
		Constructor
	=========================================*/
	public:
	Model() = default;
	// Model(const Model& x);
	// Model(const Mesh& mesh);

	/*=========================================
		Methods
	=========================================*/
	public:
	ptr			copy() const;
	void		add_mesh(const Mesh& mesh);
	void		add_mesh_emplace(Mesh&& mesh);
	void		add_child(ptr x);

	private:
};