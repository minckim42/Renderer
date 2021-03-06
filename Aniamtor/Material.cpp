#include "Material.hpp"
#include <vector>
using namespace std;
using namespace glm;

/*##############################################################################

	Material

##############################################################################*/

uint	Material::default_texture;
uint	Material::default_texture_normal;

std::unordered_map<std::string, Material>	Material::container;

/*=========================================
	Methods
=========================================*/	

Material::Material():
param({ 
	{1, 1, 1},	// ka
	{1, 1, 1},	// kd
	{1, 1, 1},	// ks
	{1, 1, 1},	// tf
	1.0f, 		// d
	60.0f, 		// ns
	1.0f 		// ni
}),
map_ka(default_texture),
map_ks(default_texture),
map_kd(default_texture),
map_bump(default_texture_normal),
illum(0),
name("noname")
{}

//------------------------------------------------------------------------------

Material::Material(const string& name):
param({ 
	{1, 1, 1},	// ka
	{1, 1, 1},	// kd
	{1, 1, 1},	// ks
	{1, 1, 1},	// tf
	1.0f, 		// d
	60.0f, 		// ns
	1.0f 		// ni
}),
map_ka(default_texture),
map_ks(default_texture),
map_kd(default_texture),
map_bump(default_texture_normal),
illum(0),
name(name)
{}

/*=========================================
	Methods
=========================================*/	

uint		Material::init_default_texture()
{
	uint	data[1] = {0xff808080};
	glGenTextures(1, &default_texture);

	glBindTexture(GL_TEXTURE_2D, default_texture);
	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTexImage2D(
		GL_TEXTURE_2D, 
		0, 
		GL_RGBA, 
		1, 
		1, 
		0, 
		GL_RGBA, 
		GL_UNSIGNED_BYTE, 
		data
	);
	glGenerateMipmap(GL_TEXTURE_2D);
	return default_texture;
}

//------------------------------------------------------------------------------

uint		Material::init_default_texture_normal()
{
	vector<uint>	data;
	
	for (int i = 0 ; i < 1 ; i++)
	{
		data.push_back(0xffff8080);
	}

	glGenTextures(1, &default_texture_normal);

	glBindTexture(GL_TEXTURE_2D, default_texture_normal);
	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glTexImage2D(
		GL_TEXTURE_2D, 
		0, 
		GL_RGBA, 
		1, 
		1, 
		0, 
		GL_RGBA, 
		GL_UNSIGNED_BYTE, 
		data.data()
	);
	glGenerateMipmap(GL_TEXTURE_2D);
	return default_texture_normal;
}

/*##############################################################################

	None Member

##############################################################################*/
#include <iostream>

unsigned int		image_loader(const std::string& path)
{
	unsigned int	image_id;

	glGenTextures(1, &image_id);
	glBindTexture(GL_TEXTURE_2D, image_id);
	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	
	// stbi_set_flip_vertically_on_load(true);

	int				width, height, nr_channel;
	unsigned char*	data = stbi_load(path.c_str(), &width, &height, &nr_channel, 0);

	if (!data)
	{
		// throw string("Failed to load image file: ") + path;
		cout << "Failed to load image file: " << path << endl;
		return Material::default_texture;
	}
	unsigned int	format[5] = {0, GL_RED, 0, GL_RGB, GL_RGBA};
	glTexImage2D(
		GL_TEXTURE_2D, 
		0, 
		format[nr_channel], 
		width, 
		height, 
		0, 
		format[nr_channel], 
		GL_UNSIGNED_BYTE, 
		data
	);
	glGenerateMipmap(GL_TEXTURE_2D);
	stbi_image_free(data);
	return image_id;
}