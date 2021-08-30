#pragma once
#include <unordered_map>
#include <string>
#include <glm/glm.hpp>
#include <glad/glad.h>
#include <stb_image.h>


/*##############################################################################

	Material Parameter

##############################################################################*/

struct Material_param
{
	glm::vec3		ka;
	glm::vec3		kd;
	glm::vec3		ks;
	glm::vec3		tf;
	float			d;
	float			ns;
	float			ni;
};

/*##############################################################################

	Material

##############################################################################*/

enum class Material_format
{
	mtl
};

class Material
{
	typedef unsigned int	uint;
	
	/*=========================================
		Members
	=========================================*/
	
	public:
	Material_param		param;
	uint				map_ka;
	uint				map_kd;
	uint				map_ks;
	uint				map_bump;
	uint				illum;
	std::string			name;

	static std::unordered_map<std::string, Material>	container;
	static uint			default_texture;
	static uint			default_texture_normal;

	/*=========================================
		Constructor
	=========================================*/
	
	public:
	Material();
	Material(const std::string& name);
	Material(const Material& x) = default;
	virtual				~Material() = default;
	Material&			operator=(const Material& x) = default;

	/*=========================================
		Methods
	=========================================*/	

	static uint			init_default_texture();
	static uint			init_default_texture_normal();
};

/*##############################################################################

	None Member

##############################################################################*/

unsigned int		image_loader(const std::string& path);

typedef std::unordered_map<std::string, Material>	MaterialContainer;