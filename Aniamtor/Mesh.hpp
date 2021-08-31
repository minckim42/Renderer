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
	void			draw(Shader& shader, glm::mat4 world, double time);
	void			draw_base(Shader& shader, glm::mat4 world);
	bool			is_static_model();
	void			set_buffer();
	void			set_tangents();
	void			set_vertex_tangent(uint a, uint b, uint c);


	private:
	void			update_bone(uint animation_id, glm::mat4 world, double time);
	void			init_bone(double time);
};