#pragma once
#include <glm/glm.hpp>
#include "Material.hpp"
#include "Shader.hpp"
#include <glad/glad.h>

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
	typedef std::pair<glm::vec3, glm::vec3>		box;

	/*=========================================
		Members
	=========================================*/
	public:
	uint						vao;
	uint						vbo;
	uint						ebo;
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
	Mesh();
	virtual		~Mesh();
	/*=========================================
		Methods
	=========================================*/
	public:
	Mesh			copy() const;
	void			draw(Shader& shader, const glm::mat4& world);
	void			draw(Shader& shader, const glm::mat4& world, double time, uint animation);
	bool			is_static_model();
	void			set_buffer();
	void			set_tangents();
	void			set_vertex_tangent(uint a, uint b, uint c);
	box				get_bounding_box();

	private:
	void			update_bone(Shader& shader, glm::mat4 world, double time, uint animation_id);
	void			init_bone(double time);
};