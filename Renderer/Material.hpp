#pragma once
#include <string>
#include <glm/glm.hpp>


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

	/*=========================================
		Constructor & Destructor
	=========================================*/
	
	public:
						Material() = default;
						Material(const std::string& name);
						Material(const Material& x) = default;
	virtual				~Material() = default;
	Material&			operator=(const Material& x) = default;
};