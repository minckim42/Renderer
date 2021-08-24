#include "AssimpLoader.hpp"

using namespace std;
using namespace glm;

//------------------------------------------------------------------------------

shared_ptr<Model>	assimp_loader(const string& path, MaterialContainer& materials)
{
	Assimp::Importer	importer;

	const aiScene*		scene = importer.ReadFile(
									path
									, aiProcess_Triangulate 
									| aiProcess_GenSmoothNormals 
									| aiProcess_FlipUVs 
									| aiProcess_CalcTangentSpace
								);
	const string		directory = path.substr(0, path.find_last_of('/'));
	return process_node(scene->mRootNode, scene, directory, materials);
}

//------------------------------------------------------------------------------

shared_ptr<Model>	process_node(aiNode* node, const aiScene* scene, const string& directory, MaterialContainer& materials)
{
	shared_ptr<Model>	model = make_shared<Model>();
	for (unsigned int i = 0 ; i < node->mNumMeshes ; i++)
	{
		aiMesh*		assimp_mesh = scene->mMeshes[node->mMeshes[i]];
		model->meshes.emplace_back(process_mesh(assimp_mesh, scene, directory, materials));
		model->meshes.back().set_buffer();
	}
	for (unsigned int i = 0 ; i < node->mNumChildren ; i++)
	{
		model->add_child(process_node(node->mChildren[i], scene, directory, materials));
	}
	return model;
}

//------------------------------------------------------------------------------

static void	put_color(aiColor3D& ai_color, vec3& color)
{
	color.r = ai_color.r;
	color.g = ai_color.g;
	color.b = ai_color.b;
}

//------------------------------------------------------------------------------

Mesh				process_mesh(aiMesh* assimp_mesh, const aiScene* scene, const string& directory, MaterialContainer& materials)
{
	Mesh	mesh;

	mesh.vertices.reserve(assimp_mesh->mNumVertices);
	mesh.indices.reserve(assimp_mesh->mNumFaces);

	// vertex
	for (unsigned int i = 0 ; i < assimp_mesh->mNumVertices; i++)
	{
		mesh.vertices.emplace_back();
		Vertex&		vertex = mesh.vertices.back();

		vertex.position.x = assimp_mesh->mVertices[i].x;
		vertex.position.y = assimp_mesh->mVertices[i].y;
		vertex.position.z = assimp_mesh->mVertices[i].z;

		if (assimp_mesh->HasNormals())
		{
			vertex.normal.x = assimp_mesh->mNormals[i].x;
			vertex.normal.y = assimp_mesh->mNormals[i].y;
			vertex.normal.z = assimp_mesh->mNormals[i].z;
		}

		if (assimp_mesh->mTextureCoords[0])
		{
			vertex.tex_coord.x = assimp_mesh->mTextureCoords[0][i].x;
			vertex.tex_coord.y = assimp_mesh->mTextureCoords[0][i].y;

			vertex.tangent.x = assimp_mesh->mTangents[i].x;
			vertex.tangent.y = assimp_mesh->mTangents[i].y;
			vertex.tangent.z = assimp_mesh->mTangents[i].z;
			
			vertex.bi_tangent.x = assimp_mesh->mBitangents[i].x;
			vertex.bi_tangent.y = assimp_mesh->mBitangents[i].y;
			vertex.bi_tangent.z = assimp_mesh->mBitangents[i].z;
		}
	}

	// index
	for (unsigned int i = 0 ; i < assimp_mesh->mNumFaces ; i++)
	{
		aiFace	face = assimp_mesh->mFaces[i];
		for (unsigned int j = 0 ; j < face.mNumIndices ; j++)
		{
			mesh.indices.push_back(face.mIndices[j]);
		}
	}

	// material
	string		texture_name = scene->mMaterials[assimp_mesh->mMaterialIndex]->GetName().C_Str();
	if (materials.find(texture_name) != materials.end())
	{
		mesh.material = &materials[texture_name];
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
		put_color(color, material.param.ka);
		scene->mMaterials[assimp_mesh->mMaterialIndex]->Get(AI_MATKEY_COLOR_DIFFUSE, color);
		put_color(color, material.param.kd);
		scene->mMaterials[assimp_mesh->mMaterialIndex]->Get(AI_MATKEY_COLOR_SPECULAR, color);
		put_color(color, material.param.ks);
	
		materials[texture_name] = material;
		mesh.material = &materials[texture_name];

	}
	return mesh;
}

//------------------------------------------------------------------------------

void			load_texture_type(aiMaterial* assimp_material, aiTextureType type, const string& directory, Material& material)
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