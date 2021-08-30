#pragma once
#include <glm/glm.hpp>
#include "Material.hpp"
#include "Shader.hpp"

#include "Bone.hpp"
#include "Vertex.hpp"
#include <map>

/*##############################################################################

	Mesh

##############################################################################*/

class Mesh
{
	/*=========================================
		Types
	=========================================*/
	public:
	typedef unsigned int			uint;
	typedef std::shared_ptr<Mesh>	ptr;

	/*=========================================
		Members
	=========================================*/
	public:
	uint						vao;
	Material*					material;
	std::vector<glm::mat4>		matrices;
	Bone::ptr					bone;
	std::map<std::string, Bone::ptr>	bone_map;
	std::vector<std::string>	animation_names;
	std::vector<Vertex>			vertices;
	std::vector<uint>			indices;

	/*=========================================
		Constructor
	=========================================*/
	public:
	Mesh()=default;
	Mesh(Mesh& x);
	Mesh(Mesh&& x);

	/*=========================================
		Methods
	=========================================*/
	public:
	Mesh			copy() const;
	void			draw(Shader& shader, double time);
	bool			is_static_model();

	private:
	void			update_bone(double time);
	void			init_bone(double time);
};