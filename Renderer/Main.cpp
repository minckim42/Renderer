#include "WindowGlfw.hpp"
#include "Renderer.hpp"
#include "Object.hpp"
#include "ObjLoader.hpp"
#include "AssimpLoader.hpp"
#include <iostream>
#include <glm/glm.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/ext.hpp>
#include <chrono>
using namespace std;
using namespace glm;


// #define ROTATE


#define UP_Z

#ifdef UP_Z
# define FRONT vec3(0, 1, 0)
# define UP vec3(0, 0, 1)
#else
# define FRONT vec3(0, 0, -1)
# define UP vec3(0, 1, 0)
#endif


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
	float		speed;
	
	chrono::system_clock::time_point	prev;

	public:
	Window(int width, int height, const std::string& name):
		WindowGlfw(width, height, name),
		prev(chrono::system_clock::now()),
		speed(1)
	{}

	bool		work()
	{
		glClearColor(0.0, 0.0, 0.0, 1);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		key_process();
		#ifdef ROTATE
		renderer->model->children[0]->matrix = rotate(0.005f, UP) * renderer->model->children[0]->matrix;
		#endif
		renderer->draw();
		return true;
	}

	void 			key_process()
	{
		chrono::duration<float>	interval(chrono::system_clock::now() - prev);

		float	len = model_size * 0.001 * interval.count() * speed;
		float	rad = 0.0005 * interval.count();
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
			renderer->camera->yaw(rad, renderer->camera->up);
		}
		if (glfwGetKey(get_window(), GLFW_KEY_RIGHT) == GLFW_PRESS)
		{
			renderer->camera->yaw(-rad, renderer->camera->up);
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
			renderer->camera->move(UP * len);
		}
		if (glfwGetKey(get_window(), GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
		{
			renderer->camera->move(UP * -len);
		}
		if (glfwGetKey(get_window(), GLFW_KEY_LEFT_BRACKET) == GLFW_PRESS)
		{
			speed /= 1.1;
			if (speed < 0.0000001)
				speed = 0.0000001;
			cout << speed << endl;
		}
		if (glfwGetKey(get_window(), GLFW_KEY_RIGHT_BRACKET) == GLFW_PRESS)
		{
			speed *= 1.1;
			cout << speed << endl;
		}
		renderer->camera->update_view();

		// cout << to_string(renderer->camera->get_position()) << endl;
		// cout << to_string(renderer->camera->get_direction()) << endl;
		// cout << to_string(camera->projection) << endl;
	}

};


// #define BIGBOY
// #define BOX
// #define SONA
// #define STAR
// #define CLOCK
// #define WALKING_MAN
// #define PACK
#define HOUSE

// #define GROUND

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



		shared_ptr<Model>	model = make_shared<Model>();
		world.add_child(model);



		#ifdef BOX
		obj_loader("./box/box.obj", *model, materials);
		#endif

		#ifdef SONA
		//obj_loader("./sona/cloth.obj", *model, materials);
		//obj_loader("./sona/skin.obj", *model, materials);
		//obj_loader("./sona/hair.obj", *model, materials);
		//obj_loader("./sona/weapon.obj", *model, materials);

		model->add_child(assimp_loader("./sona/cloth.obj", materials));
		model->add_child(assimp_loader("./sona/skin.obj", materials));
		model->add_child(assimp_loader("./sona/hair.obj", materials));
		model->add_child(assimp_loader("./sona/weapon.obj", materials));

		#endif


		#ifdef BIGBOY
		model->add_child(assimp_loader("../../sources/big_boy/big_boy.obj", materials));
		#endif

		#ifdef STAR
		model->add_child(assimp_loader("../../sources/starpolis/starpolis.obj", materials));
		light.set_position(vec3(0, 100000, 0));
		light.strength = 300000;
		#endif
		
		#ifdef PACK
		model->add_child(assimp_loader("./backpack/backpack.obj", materials));
		light.set_position(vec3(0, 1000, 0));
		light.strength = 1000;
		#endif

		#ifdef WALKING_MAN
		model->add_child(assimp_loader("../../sources/walking_man/rp_nathan_animated_003_walking.fbx", materials));
		light.set_position(vec3(0, 0, 1000));
		light.strength = 1000;
		#endif

		#ifdef CLOCK
		model->add_child(assimp_loader("../../sources/clock/clock3.obj", materials));
		light.set_position(vec3(0, 0, 1000));
		light.strength = 1000;
		#endif

		#ifdef HOUSE
		model->add_child(assimp_loader("../../sources/house/house.3ds", materials));
		light.set_position(vec3(0, 100000, 100000));
		light.strength = 200000;
		#endif

		#ifdef GROUND
		obj_loader("./ground/ground.obj", world, materials);
		#endif

		float	model_size = get_model_size(*model);
		window.model_size = model_size;

		#ifdef UP_Z
		Camera		camera(
						vec3(0, -model_size * 2, model_size / 2),
						FRONT, 
						UP,
						pi<float>() / 2,
						16.0f/9,
						model_size * 10,
						model_size * 0.001
					);
		#else
		Camera		camera(
						vec3(0, model_size / 2, model_size * 2),
						FRONT, 
						UP,
						pi<float>() / 3,
						16.0f/9,
						model_size * 10,
						model_size * 0.001
					);
		#endif

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