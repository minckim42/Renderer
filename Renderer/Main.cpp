#include "WindowGlfw.hpp"
#include "Renderer.hpp"
#include "Object.hpp"
#include "ObjLoader.hpp"
#include <iostream>
#include <glm/glm.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/ext.hpp>
using namespace std;
using namespace glm;

// #define BIGBOY
// #define BOX
#define SONA
// #define STAR

 #define ROTATE


float	get_model_size(Model& model)
{
	auto	box = model.get_bounding_box();
	return sqrt(dot((box.first - box.second), (box.first - box.second)));
}

class Window: public WindowGlfw
{
	public:
	Renderer*	renderer;
	float		model_size;

	public:
	Window(int width, int height, const std::string& name):
		WindowGlfw(width, height, name)
	{}

	bool		work()
	{
		glClearColor(0.3, 0.3, 0.3, 1);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		key_process();
		#ifdef ROTATE
		renderer->model->children[1]->matrix = rotate(0.005f, vec3(0, 0, 1)) * renderer->model->children[1]->matrix;
		#endif
		renderer->draw();
		return true;
	}

	void 			key_process()
	{
		float	len = model_size * 0.01;
		float	rad = 0.01;
		if (glfwGetKey(get_window(), GLFW_KEY_ESCAPE) == GLFW_PRESS)
		{
			glfwSetWindowShouldClose(get_window(), true);
		}
		if (glfwGetKey(get_window(), GLFW_KEY_W) == GLFW_PRESS)
		{
			renderer->camera->move_forward(len);
		}
		if (glfwGetKey(get_window(), GLFW_KEY_S) == GLFW_PRESS)
		{
			renderer->camera->move_forward(-len);
		}
		if (glfwGetKey(get_window(), GLFW_KEY_A) == GLFW_PRESS)
		{
			renderer->camera->move_left(len);
		}
		if (glfwGetKey(get_window(), GLFW_KEY_D) == GLFW_PRESS)
		{
			renderer->camera->move_left(-len);
		}
		if (glfwGetKey(get_window(), GLFW_KEY_LEFT) == GLFW_PRESS)
		{
			renderer->camera->yaw(rad, vec3(0, 0, 1));
		}
		if (glfwGetKey(get_window(), GLFW_KEY_RIGHT) == GLFW_PRESS)
		{
			renderer->camera->yaw(-rad, vec3(0, 0, 1));
		}
		if (glfwGetKey(get_window(), GLFW_KEY_UP) == GLFW_PRESS)
		{
			renderer->camera->pitch(rad);
		}
		if (glfwGetKey(get_window(), GLFW_KEY_DOWN) == GLFW_PRESS)
		{
			renderer->camera->pitch(-rad);
		}
		if (glfwGetKey(get_window(), GLFW_KEY_SPACE) == GLFW_PRESS)
		{
			renderer->camera->move(vec3(0, 0, len));
		}
		if (glfwGetKey(get_window(), GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
		{
			renderer->camera->move(vec3(0, 0, -len));
		}
		renderer->camera->update_view();

		// cout << to_string(renderer->camera->get_position()) << endl;
		// cout << to_string(renderer->camera->get_direction()) << endl;
		// cout << to_string(camera->projection) << endl;
	}

};



int		main()
{
	try
	{
		Window		window(1920, 1080, "test");
		window.init();
		init_glad();

		Renderer	renderer;
		renderer.shader.compile_shader("shader_vertex.glsl", shader_type::vertex);
		renderer.shader.compile_shader("shader_fragment.glsl", shader_type::fragment);
		renderer.shader.link_shader_program();
		window.renderer = &renderer;

		Light		light;
		light.set_position(vec3(5000, 0, 0));
		light.strength = 5000;

		Model				world;

		MaterialContainer	materials;
		Material::init_default_texture();
		Material::init_default_texture_normal();

		obj_loader("./ground/ground.obj", world, materials);

		shared_ptr<Model>	model = make_shared<Model>();
		world.add_child(model);

		#ifdef BOX
		obj_loader("./box/box.obj", *model, materials);
		#endif

		#ifdef SONA
		obj_loader("./sona/cloth.obj", *model, materials);
		obj_loader("./sona/skin.obj", *model, materials);
		obj_loader("./sona/hair.obj", *model, materials);
		obj_loader("./sona/weapon.obj", *model, materials);
		#endif


		#ifdef BIGBOY
		obj_loader("../../sources/big_boy/big_boy.obj", *model, materials);
		#endif

		#ifdef STAR
		obj_loader("../../sources/starpolis/starpolis_1.obj", *model, materials);
		light.set_position(vec3(0, 1000000, 0));
		light.strength = 1;
		#endif
		float	model_size = get_model_size(*model);
		window.model_size = model_size;

		Camera		camera(
						vec3(0, -model_size * 2, model_size / 2),
						vec3(0, 1, 0), vec3(0, 0, 1),
						pi<float>() / 3,
						16.0f/9,
						model_size * 10,
						model_size * 0.001
					);

		renderer.camera = &camera;
		renderer.light = &light;
		renderer.model = &world;

		renderer.shader.use();
		glEnable(GL_DEPTH_TEST);
		cout << model_size << endl;

		window.loop();
	}
	catch(const string& e)
	{
		std::cerr << e << '\n';
	}


	return 0;
}