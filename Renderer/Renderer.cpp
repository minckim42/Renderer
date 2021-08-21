#include "Renderer.hpp"

using namespace std;
using namespace glm;

/*##############################################################################

	Renderer

##############################################################################*/

/*=======================================
	Constructor
=======================================*/

Renderer::Renderer() 
{}

void			Renderer::draw()
{
	shader.set_uniform("eye", camera->get_position());
	shader.set_uniform("view", camera->view);
	shader.set_uniform("projection", camera->projection);
	light->draw(shader);
	model->draw(shader, model->matrix);
}
