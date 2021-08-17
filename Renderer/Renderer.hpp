#pragma once
#include "Group.hpp"
#include "Light.hpp"
#include "Camera.hpp"
#include <unordered_map>


/*##############################################################################

	Renderer

##############################################################################*/

/*=========================================
	Enum
=========================================*/

enum class model_format
{
	obj
};


class Renderer
{
	/*=========================================
		Types
	=========================================*/

	public:
	typedef std::shared_ptr<Group>						ptr_group;
	typedef std::unordered_map<std::string, Material>	container_material;
	typedef unsigned int								uint;

	/*=========================================
		Members
	=========================================*/

	public:
	Group						model;
	// std::vector<Light>			lights;
	Light						light;
	Camera						camera;
	ShaderOpengl				shader;
	container_material			materials;

	/*=======================================
		Constructor
	=======================================*/
	public:
	Renderer()=default;

	virtual			~Renderer()=default;

	/*=======================================
		Methods
	=======================================*/

	public:
	void			draw();
	void			add_file(const std::string& path, model_format format);
	void			add_group(ptr_group group);
	void			add_material(const std::string& path);
	void			add_material(Material material);
	uint			load_image(const std::string& path);

	private:
	uint			mapper(std::string& key);
};