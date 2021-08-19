#pragma once
#include <unordered_map>
#include "Model.hpp"
#include "Light.hpp"
#include "Camera.hpp"
#include "RendererBase.hpp"
#include "ObjLoader.hpp"

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


class Renderer: public RendererBase
{
	/*=========================================
		Types
	=========================================*/

	public:
	typedef std::shared_ptr<Model>						ptr_group;
	typedef std::unordered_map<std::string, Material>	container_material;
	typedef unsigned int								uint;

	/*=========================================
		Members
	=========================================*/

	// std::vector<Light>			lights;
	public:
	Model						model;
	Light						light;
	Camera						camera;
	ShaderOpengl				shader;
	container_material			materials;
	GLFWwindow*					window;
	float						model_size;

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
	void			load_obj(const std::string& path, Model& model, container_material& materials);

	void			add_group(ptr_group group);
	void			add_material(const std::string& path);
	void			add_material(Material material);
	uint			load_image(const std::string& path);
	void			key_process();
	void			set_model_size();

	/*=======================================
		Overriding
	=======================================*/

	void			prepare();
	bool			loop();
	void			terminate();
};