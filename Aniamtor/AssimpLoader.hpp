#pragma once
#include "Mesh.hpp"
#include "Model.hpp"
#include "Material.hpp"
#include <glm/glm.hpp>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <string>
#include <vector>
#include <map>

/*##############################################################################

	Assimp Loader

##############################################################################*/

class AssimpLoader
{
	/*=========================================
		Types
	=========================================*/
	public:
	typedef unsigned int								uint;
	typedef std::map<std::string, const aiBone*>		BoneMap;

	/*=========================================
		Members
	=========================================*/
	public:
	const aiScene*					scene;
	std::string						directory;
	// Model::ptr						model;
	// std::vector<Mesh>				meshes;


	/*=========================================
		Constructor
	=========================================*/
	public:
	AssimpLoader(const aiScene* scene, const std::string& directory);

	/*=========================================
		Methods
	=========================================*/
	public:
	Model::ptr	process_node(const aiNode* node);
	Mesh::ptr	process_mesh(const aiNode* node, const aiMesh* assimp_mesh);
	void		set_vertex(const aiMesh* assimp_mesh, Mesh& mesh);
	void		set_face(const aiMesh* assimp_mesh, Mesh& mesh);
	void		set_bone(const aiNode* node, const aiMesh* assimp_mesh, Mesh& mesh);
	void		set_material(const aiMesh* assimp_mesh, Mesh& mesh);
	void		add_animation(Mesh& mesh, const aiAnimation* animation);
	Bone::ptr	create_bone(
					const aiNode*		node,
					BoneMap&			bone_map,
					Mesh&				mesh,
					const glm::mat4&	prev);
	void		load_texture_type(
					const aiMaterial* 	assimp_material,
					aiTextureType 		type,
					const std::string& 	directory,
					Material&			material);

	BoneMap		init_bone_map(const aiMesh* mesh);
};

/*##############################################################################

	None Member

##############################################################################*/

Model::ptr		assimp_loader(const std::string& path);
glm::mat3		ai_to_glm(const aiMatrix3x3& ai_mat3);
glm::mat4		ai_to_glm(const aiMatrix4x4& ai_mat4);
glm::vec2		ai_to_glm(const aiVector2D& ai_vec2);
glm::vec3		ai_to_glm(const aiVector3D& ai_vec3);
glm::vec3		ai_to_glm(const aiColor3D& ai_color);
glm::quat		ai_to_glm(const aiQuaternion& ai_quat);
std::ostream&	operator<<(std::ostream& os, const glm::mat4& x);
std::ostream&	operator<<(std::ostream& os, const glm::vec3& x);