#include "Renderer.hpp"

using namespace std;
using namespace glm;

/*##############################################################################

	Renderer

##############################################################################*/

/*=======================================
	Methods
=======================================*/

void			Renderer::draw()
{
	shader.set_uniform("view", camera.view);
	shader.set_uniform("perspective", camera.matrix);
	shader.set_uniform("light_position", light.get_position());
	shader.set_uniform("light_position", light.strength);
	model.draw(shader, model.matrix);
}

void			Renderer::add_file(const string& path, model_format format)
{
	switch (format)
	{
		case model_format::obj:
			break;
		default:
			break;
	}
}

