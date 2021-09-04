#define ANIMATOR_TEST
#ifdef ANIMATOR_TEST

#include "AssimpLoader.hpp"
#include "WindowGlfw.hpp"
#include "Camera.hpp"
#include "Shader.hpp"
#include "Light.hpp"
#include <iostream>
#include <chrono>

using namespace std;
using namespace glm;

typedef unsigned int		uint;

// #define UP_Z

#ifdef UP_Z
# define FRONT vec3(0, 1, 0)
# define UP vec3(0, 0, 1)
#else
# define FRONT vec3(0, 0, -1)
# define UP vec3(0, 1, 0)
#endif

class Window : public WindowGlfw
{
	public:
	Camera*				camera;
	Shader*				shader;
	Light*				light;
	float				speed;
	float				rot_speed;
	float				model_size;
	float				time;
	Model::ptr			model;
	
	chrono::system_clock::time_point	prev;

	Window(): WindowGlfw(1920, 1080, "Test")
	{
		init();
		init_glad();
	}
	Window(int w, int h, const string& name): 
		WindowGlfw(w, h, name),
		speed(3000),
		rot_speed(1),
		model_size(1),
		time(0)
	{
		init();
		init_glad();
		prev = chrono::system_clock::now();
	}
	void 			key_process()
	{
		chrono::duration<float>	interval(chrono::system_clock::now() - prev);

		float	len = model_size * 0.001 * interval.count() * 0.0005 * speed;
		float	rad = 0.0009 * interval.count() * rot_speed;
		if (glfwGetKey(get_window(), GLFW_KEY_ESCAPE) == GLFW_PRESS)
		{
			glfwSetWindowShouldClose(get_window(), true);
		}
		if (glfwGetKey(get_window(), GLFW_KEY_W) == GLFW_PRESS)
		{
			camera->move_forward(len);
		}
		if (glfwGetKey(get_window(), GLFW_KEY_S) == GLFW_PRESS)
		{
			camera->move_forward(-len);
		}
		if (glfwGetKey(get_window(), GLFW_KEY_A) == GLFW_PRESS)
		{
			camera->move_left(len);
		}
		if (glfwGetKey(get_window(), GLFW_KEY_D) == GLFW_PRESS)
		{
			camera->move_left(-len);
		}
		if (glfwGetKey(get_window(), GLFW_KEY_LEFT) == GLFW_PRESS)
		{
			camera->yaw(rad, camera->up);
		}
		if (glfwGetKey(get_window(), GLFW_KEY_RIGHT) == GLFW_PRESS)
		{
			camera->yaw(-rad, camera->up);
		}
		if (glfwGetKey(get_window(), GLFW_KEY_UP) == GLFW_PRESS)
		{
			camera->pitch(rad);
		}
		if (glfwGetKey(get_window(), GLFW_KEY_DOWN) == GLFW_PRESS)
		{
			camera->pitch(-rad);
		}
		if (glfwGetKey(get_window(), GLFW_KEY_SPACE) == GLFW_PRESS)
		{
			camera->move(UP * len);
		}
		if (glfwGetKey(get_window(), GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
		{
			camera->move(UP * -len);
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
		if (glfwGetKey(get_window(), GLFW_KEY_O) == GLFW_PRESS)
		{
			rot_speed /= 1.1;
			if (speed < 0.0000001)
				speed = 0.0000001;
			cout << speed << endl;
		}
		if (glfwGetKey(get_window(), GLFW_KEY_P) == GLFW_PRESS)
		{
			rot_speed *= 1.1;
			cout << speed << endl;
		}
		if (glfwGetKey(get_window(), GLFW_KEY_R) == GLFW_PRESS)
		{
			time = 0;
		}
		camera->update_view();
	}

	bool		work()
	{
		time += 5;
		glClearColor(0.2, 0.2, 0.2, 1);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		key_process();

		shader->set_uniform("eye", camera->get_position());
		shader->set_uniform("view", camera->view);
		shader->set_uniform("projection", camera->projection);
		light->draw(*shader);
		model->draw(*shader, mat4(1), time, 0);
		// model->draw(*shader, mat4(1));
		// cout << time << endl;
		return true;
	}
};

#define HD 1280, 720

int		main()
{
	try
	{
		Window		window(HD, "Test");
		Material::init_default_texture();
		Material::init_default_texture_normal();

		string		file_name = 
			"../../sources/walking_man/rp_nathan_animated_003_walking.fbx";
			// "../../sources/dragon/Dragon_Baked_Actions_fbx_7.4_binary.fbx";
			// "../../sources/backpack/backpack.obj";
		
		Model::ptr	model = assimp_loader(file_name);
		
		Shader		shader;
		shader.compile_shader("shader_vertex.glsl", shader_type::vertex);
		shader.compile_shader("shader_fragment.glsl", shader_type::fragment);
		shader.link_shader_program();

		Model::box	bound = model->get_bounding_box();
		
		

		float		model_size = length(bound.first - bound.second);
		cout << "model size: " << model_size << endl;
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
						model_size * 100,
						model_size * 0.01
					);
		#endif

		Light		light;
		light.set_position((-FRONT + UP) * model_size * 3);
		light.strength = model_size * 4.5;

		window.model = model;
		window.model_size = model_size;
		window.shader = &shader;
		window.light = &light;
		window.camera = &camera;

		shader.use();
		glEnable(GL_DEPTH_TEST);
		window.loop();
	}
	catch (const std::string& err)
	{
		cout << err << endl;
	}
}

#endif