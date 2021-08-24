#include <memory>
#include <string>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "Model.hpp"
#include "Material.hpp"
#include "stb_image.h"

std::shared_ptr<Model>		assimp_loader(const std::string& path, MaterialContainer& materials);

std::shared_ptr<Model>	process_node(aiNode* node, const aiScene* scene, const std::string& directory, MaterialContainer& materials);
Mesh				process_mesh(aiMesh* assimp_mesh, const aiScene* scene, const std::string& directory, MaterialContainer& materials);
void			load_texture_type(aiMaterial* assimp_material, aiTextureType type, const std::string& directory, Material& material);
