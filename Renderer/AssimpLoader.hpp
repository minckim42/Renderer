#include <memory>
#include <string>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "Model.hpp"
#include "Material.hpp"
#include "stb_image.h"
/*##############################################################################

	Assimp loader

##############################################################################*/

std::shared_ptr<Model>	assimp_loader(const std::string& path, MaterialContainer& materials);