#include "Renderer.hpp"

using namespace std;
using namespace glm;

/*##############################################################################

	Renderer

##############################################################################*/

/*=======================================
	Methods
=======================================*/
#include <iostream>
void			Renderer::draw()
{
	shader.set_uniform("eye", camera.get_position());
	light.draw(shader);
	shader.set_uniform("view", camera.view);
	shader.set_uniform("projection", camera.projection);
	model.draw(shader, model.matrix);
}

//------------------------------------------------------------------------------

void			Renderer::add_file(const string& path, model_format format)
{
	switch (format)
	{
		case model_format::obj:
			load_obj(path, model, materials);
			break;
		default:
			break;
	}
}

//------------------------------------------------------------------------------

void			Renderer::load_obj(const std::string& path, Model& model, container_material& materials)
{
	ObjLoader	tmp(path, model, materials);
}

//------------------------------------------------------------------------------

void			Renderer::prepare()
{
	if (!shader.get_program())
		throw string("Shader does not exist");
	set_model_size();
	camera.set_position(vec3(model_size * 2, 0, model_size / 2));
	glEnable(GL_DEPTH_TEST);
}

//------------------------------------------------------------------------------

bool			Renderer::loop()
{
	shader.use();
	glClearColor(0.3, 0.3, 0.3, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	key_process();
	model.matrix = rotate(0.005f, vec3(0, 0, 1)) * model.matrix;
	draw();
	return true;
}

//------------------------------------------------------------------------------

void			Renderer::terminate()
{}

//------------------------------------------------------------------------------

void 			Renderer::key_process()
{
	float	len = model_size * 0.01;
	float	rad = 0.01;
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
        glfwSetWindowShouldClose(window, true);
	}
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
    {
		camera.move_forward(len);
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
    {
		camera.move_forward(-len);
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
    {
		camera.move_left(len);
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
    {
		camera.move_left(-len);
	}
	if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
    {
		camera.yaw(rad, vec3(0, 0, 1));
	}
	if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
    {
		camera.yaw(-rad, vec3(0, 0, 1));
	}
	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
    {
		camera.pitch(rad);
	}
	if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
    {
		camera.pitch(-rad);
	}
	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
    {
		camera.move(vec3(0, 0, len));
	}
	if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
    {
		camera.move(vec3(0, 0, -len));
	}
	camera.update_view();

	// cout << to_string(camera.get_position()) << endl;
	// cout << to_string(camera.get_direction()) << endl;
	// cout << to_string(camera.projection) << endl;
}

void			Renderer::set_model_size()
{
	auto	size_pair = model.get_bounding_box();
	model_size = sqrt(dot((size_pair.first - size_pair.second), (size_pair.first - size_pair.second)));
}