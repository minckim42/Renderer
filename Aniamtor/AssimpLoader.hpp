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
	typedef unsigned int			uint;

	/*=========================================
		Members
	=========================================*/
	public:
	const aiScene*					scene;
	std::string						directory;
	Model::ptr						model;
	std::vector<Mesh>				meshes;


	/*=========================================
		Constructor
	=========================================*/
	public:
	AssimpLoader(const aiScene* scene, const std::string& directory);

	/*=========================================
		Methods
	=========================================*/
	public:
	Model::ptr	process_node(aiNode* node);
	Mesh::ptr	process_mesh(aiMesh* assimp_mesh);
	void		set_vertex(aiMesh* assimp_mesh, Mesh& mesh);
	void		set_face(aiMesh* assimp_mesh, Mesh& mesh);
	void		set_bone(aiMesh* assimp_mesh, Mesh& mesh);
	void		set_material(aiMesh* assimp_mesh, Mesh& mesh);
	Bone::ptr	create_bone(
					aiNode*							node,
					std::map<std::string, aiBone*>	bone_map,
					Mesh&							mesh,
					glm::mat4&						prev_inverse);
	void		load_texture_type(
					aiMaterial* 		assimp_material,
					aiTextureType 		type,
					const std::string& 	directory,
					Material&			material);

	std::map<std::string, aiBone*>	init_bone_map(aiMesh* mesh);
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