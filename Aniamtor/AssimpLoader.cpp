#include "AssimpLoader.hpp"


using namespace std;
using namespace glm;

//------------------------------------------------------------------------------

AssimpLoader::AssimpLoader(const aiScene* scene, const std::string& directory):
	scene(scene), directory(directory)
{

}

//------------------------------------------------------------------------------

Model::ptr	AssimpLoader::process_node(aiNode* node)
{
	Model::ptr		model = make_shared<Model>();

	model->meshes.reserve(node->mNumMeshes);
	for (uint i = 0 ; i < node->mNumMeshes ; i++)
	{
		model->meshes.emplace_back(
			process_mesh(scene->mMeshes[node->mMeshes[i]])
			
			);
	}
	for (uint i = 0 ; i < node->mNumChildren ; i++)
	{
		model->children.emplace_back(process_node(node->mChildren[i]));
	}
}

//------------------------------------------------------------------------------

Mesh::ptr	AssimpLoader::process_mesh(aiMesh* assimp_mesh)
{
	Mesh::ptr	mesh = make_shared<Mesh>();

	set_vertex(assimp_mesh, *mesh);
	set_face(assimp_mesh, *mesh);
	set_material(assimp_mesh, *mesh);
	if (assimp_mesh->HasBones())
	{
		set_bone(assimp_mesh, *mesh);
	}
}

//------------------------------------------------------------------------------

void		AssimpLoader::set_vertex(aiMesh* assimp_mesh, Mesh& mesh)
{
	mesh.vertices.reserve(assimp_mesh->mNumVertices);
	for (uint i = 0 ; i < assimp_mesh->mNumVertices ; i++)
	{
		mesh.vertices.emplace_back();
		Vertex&	vertex = mesh.vertices.back();
		vertex.position = ai_to_glm(assimp_mesh->mVertices[i]);
		if (assimp_mesh->HasNormals())
		{
			vertex.normal = ai_to_glm(assimp_mesh->mNormals[i]);
		}
		if (assimp_mesh->mTextureCoords[0])
		{
			vertex.tex_coord = vec2(
				assimp_mesh->mTextureCoords[0][i].x,
				assimp_mesh->mTextureCoords[0][i].y);
		}
	}
}

//------------------------------------------------------------------------------

void		AssimpLoader::set_face(aiMesh* assimp_mesh, Mesh& mesh)
{
	mesh.indices.reserve(assimp_mesh->mNumFaces);
	for (uint i = 0 ; i < assimp_mesh->mNumFaces ; i++)
	{
		mesh.indices.push_back(assimp_mesh->mFaces[i].mIndices[0]);
		mesh.indices.push_back(assimp_mesh->mFaces[i].mIndices[1]);
		mesh.indices.push_back(assimp_mesh->mFaces[i].mIndices[2]);
	}
}

//------------------------------------------------------------------------------

void		AssimpLoader::set_bone(aiMesh* assimp_mesh, Mesh& mesh)
{
	map<std::string, aiBone*>	bone_map = init_bone_map(assimp_mesh);
	mat4	ident(1.0f);
	mesh.bone = create_bone(scene->mRootNode, bone_map, mesh, ident);
	// for each animation
	for (uint i = 0 ; i < scene->mNumAnimations ; i++)
	{
		aiAnimation*	animation = scene->mAnimations[i];
		mesh.animation_names.emplace_back(animation->mName.C_Str());
		// for each bone
		for (uint j = 0 ; j < animation->mNumChannels ; j++)
		{
			aiNodeAnim*	animation_bone = animation->mChannels[j];
			Bone::ptr bone = mesh.bone_map[animation_bone->mNodeName.C_Str()];
			bone->animations.emplace_back();
			// for each key frame
			for (uint k = 0 ; k < animation_bone->mNumPositionKeys ; k++)
			{
				bone->animations.back().position_keys.emplace_back(
					ai_to_glm(animation_bone->mPositionKeys[k].mValue));
				bone->animations.back().position_time.push_back(
					animation_bone->mPositionKeys[k].mTime);
			}
			for (uint k = 0 ; k < animation_bone->mNumRotationKeys ; k++)
			{
				bone->animations.back().rotation_keys.emplace_back(
					ai_to_glm(animation_bone->mRotationKeys[k].mValue));
				bone->animations.back().rotation_time.push_back(
					animation_bone->mRotationKeys[k].mTime);
			}
			for (uint k = 0 ; k < animation_bone->mNumScalingKeys ; k++)
			{
				bone->animations.back().scale_keys.emplace_back(
					ai_to_glm(animation_bone->mScalingKeys[k].mValue));
				bone->animations.back().scale_time.push_back(
					animation_bone->mScalingKeys[k].mTime);
			}
		}
	}
}

//------------------------------------------------------------------------------

Bone::ptr	AssimpLoader::create_bone(
				aiNode* 				node,
				map<string, aiBone*> 	bone_map,
				Mesh& 					mesh,
				mat4& 					prev_inverse)
{
	aiBone*		assimp_bone = bone_map[node->mName.C_Str()];
	mat4		offset = ai_to_glm(assimp_bone->mOffsetMatrix);
	Bone::ptr	bone = make_shared<Bone>(mesh.matrices, offset);

	bone->world_inverse = inverse(offset) * prev_inverse;

	bone->children.reserve(node->mNumChildren);
	for (uint i = 0 ; i < assimp_bone->mNumWeights ; i++)
	{
		mesh.vertices[assimp_bone->mWeights[i].mVertexId].add_weight(
			bone->idx_mat, assimp_bone->mWeights[i].mWeight);
	}

	for (uint i = 0 ; i < node->mNumChildren ; i++)
	{
		if (bone_map.find(node->mChildren[i]->mName.C_Str()) == bone_map.end())
			continue ;
		bone->children.emplace_back(
			create_bone(node->mChildren[i], bone_map, mesh, bone->world_inverse));
	}
	mesh.bone_map[node->mName.C_Str()] = bone;
	return bone;
}

//------------------------------------------------------------------------------

void	AssimpLoader::set_material(aiMesh* assimp_mesh, Mesh& mesh)
{
	string		texture_name = scene->mMaterials[assimp_mesh->mMaterialIndex]->GetName().C_Str();
	if (Material::container.find(texture_name) != Material::container.end())
	{
		mesh.material = &Material::container[texture_name];
	}
	else
	{
		aiMaterial*		assimp_material = scene->mMaterials[assimp_mesh->mMaterialIndex];
		Material		material;
		load_texture_type(assimp_material, aiTextureType_AMBIENT, directory, material);
		load_texture_type(assimp_material, aiTextureType_DIFFUSE, directory, material);
		load_texture_type(assimp_material, aiTextureType_SPECULAR, directory, material);
		load_texture_type(assimp_material, aiTextureType_HEIGHT, directory, material);
	
		aiColor3D		color;
		scene->mMaterials[assimp_mesh->mMaterialIndex]->Get(AI_MATKEY_COLOR_AMBIENT, color);
		material.param.ka = ai_to_glm(color);
		scene->mMaterials[assimp_mesh->mMaterialIndex]->Get(AI_MATKEY_COLOR_DIFFUSE, color);
		material.param.kd = ai_to_glm(color);
		scene->mMaterials[assimp_mesh->mMaterialIndex]->Get(AI_MATKEY_COLOR_SPECULAR, color);
		material.param.ks = ai_to_glm(color);
	
		Material::container[texture_name] = material;
		mesh.material = &Material::container[texture_name];

	}
}

//------------------------------------------------------------------------------

std::map<std::string, aiBone*>		AssimpLoader::init_bone_map(aiMesh* mesh)
{
	map<string, aiBone*>	bone_map;
	for (uint i = 0 ; mesh->mNumBones ; i++)
	{
		bone_map[mesh->mBones[i]->mName.C_Str()] = mesh->mBones[i];
	}
	return bone_map;
}

//------------------------------------------------------------------------------

void	AssimpLoader::load_texture_type(
			aiMaterial* 	assimp_material,
			aiTextureType 	type,
			const string& 	directory,
			Material&		material
		)
{
	unsigned int	num = assimp_material->GetTextureCount(type);
	unsigned int*	id;

	switch (type)
	{
		case aiTextureType_AMBIENT:
			id = &material.map_ka;
			break;
		case aiTextureType_DIFFUSE:
			id = &material.map_kd;
			break;
		case aiTextureType_SPECULAR:
			id = &material.map_ks;
			break;
		case aiTextureType_NORMALS:
			id = &material.map_bump;
			break;
		case aiTextureType_HEIGHT:
			id = &material.map_bump;
			break;
		default:
			id = 0;
	}
	if (!id)
		throw string("Wrong type");
	if (num)
	{
		aiString		filename;
		assimp_material->GetTexture(type, 0, &filename);
		*id = image_loader(directory + '/' + filename.C_Str());
	}
	else
	{
		if (type == aiTextureType_NORMALS || type == aiTextureType_HEIGHT)
			*id = Material::default_texture_normal;
		else
			*id = Material::default_texture;
	}
}

/*##############################################################################

	None Member

##############################################################################*/


Model::ptr	assimp_loader(const string& path)
{
	Assimp::Importer	importer;
	const aiScene*		scene = importer.ReadFile(
									path, 
									aiProcess_Triangulate | 
									aiProcess_GenSmoothNormals | 
									aiProcess_FlipUVs | 
									aiProcess_CalcTangentSpace
								);
	if (!scene)
		throw string("Failed to open model file: ") + path + "(scene == nullptr)";
	if (scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE)
		throw string("Failed to open model file: ") + path + "(AI_SCENE_FLAG_IMCOMPLETE)";
	if (!scene->mRootNode)
		throw string("Failed to open model file: ") + path + "(Root node dosen't exist)";

	AssimpLoader		loader(scene, path.substr(0, path.find_last_of('/')));
	
	
	
}

//------------------------------------------------------------------------------

mat3		ai_to_glm(const aiMatrix3x3& ai_mat4)
{
	return mat3(
		ai_mat4.a1, ai_mat4.b1, ai_mat4.c1,
		ai_mat4.a2, ai_mat4.b2, ai_mat4.c2,
		ai_mat4.a3, ai_mat4.b3, ai_mat4.c3
	);
}

//------------------------------------------------------------------------------

mat4		ai_to_glm(const aiMatrix4x4& ai_mat4)
{
	return mat4(
		ai_mat4.a1, ai_mat4.b1, ai_mat4.c1, ai_mat4.d1,
		ai_mat4.a2, ai_mat4.b2, ai_mat4.c2, ai_mat4.d2,
		ai_mat4.a3, ai_mat4.b3, ai_mat4.c3, ai_mat4.d3,
		ai_mat4.a4, ai_mat4.b4, ai_mat4.c4, ai_mat4.d4
	);
}

//------------------------------------------------------------------------------

vec2		ai_to_glm(const aiVector2D& ai_vec2)
{
	return vec2(ai_vec2.x, ai_vec2.y);
}

//------------------------------------------------------------------------------

vec3		ai_to_glm(const aiVector3D& ai_vec3)
{
	return vec3(ai_vec3.x, ai_vec3.y, ai_vec3.z);
}

//------------------------------------------------------------------------------

vec3		ai_to_glm(const aiColor3D& ai_color)
{
	return vec3(ai_color.r, ai_color.g, ai_color.b);
}

//------------------------------------------------------------------------------

quat		ai_to_glm(const aiQuaternion& ai_quat)
{
	return quat(ai_quat.w, ai_quat.x, ai_quat.y, ai_quat.z);
}