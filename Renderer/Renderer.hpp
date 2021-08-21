#pragma once
#include <unordered_map>
#include "Model.hpp"
#include "Light.hpp"
#include "Camera.hpp"
#include "RendererBase.hpp"

/*##############################################################################

	Renderer

##############################################################################*/

typedef std::unordered_map<std::string, Material>	MaterialContainer;

class Renderer
{
	/*=========================================
		Members
	=========================================*/

	public:
	Model*					model;
	MaterialContainer*		materials;
	Light*					light;	// should be changed to array
	Camera*					camera;
	Shader			shader;

	/*=======================================
		Constructor
	=======================================*/

	public:
	Renderer();
	virtual			~Renderer()=default;

	/*=======================================
		Methods
	=======================================*/

	public:
	void			draw();
};
