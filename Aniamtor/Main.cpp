
// #include "AssimpLoader.hpp"
// #include "WindowGlfw.hpp"
// #include "Camera.hpp"
// #include "Shader.hpp"
// #include "Light.hpp"
// #include "Controlable.hpp"
// #include <iostream>
// #include <chrono>

// #define FHD 1920, 1080
// #define HD 1280, 720
// #define RESOLUTION FHD


// using namespace std;
// using namespace glm;
// typedef unsigned int	uint;

// class Window : public WindowGlfw
// {
// 	public:

// 	typedef chrono::system_clock::time_point	TimePoint;
// 	typedef chrono::duration<double>			Duration;

// 	Camera*				camera;
// 	Shader*				shader;
// 	Light*				light;
// 	float				speed;
// 	float				rot_speed;
// 	float				model_size;
// 	Model::ptr			model;
// 	TimePoint			prev_time;



// 	Window(int w, int h, const string& name): 
// 		WindowGlfw(w, h, name),
// 		speed(3000),
// 		rot_speed(1),
// 		model_size(1)
// 	{
// 		init();
// 		init_glad();
// 		prev_time = chrono::system_clock::now();
// 	}





// 	bool		work()
// 	{
// 		Duration	duration = prev_time - chrono::system_clock::now();
// 		double		time = duration.count();
// 		glClearColor(0.2, 0.2, 0.2, 1);
// 		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

// 		shader->set_uniform("eye", camera->get_position());
// 		shader->set_uniform("view", camera->view);
// 		shader->set_uniform("projection", camera->projection);
// 		light->draw(*shader);
// 		model->draw(*shader, mat4(1), time, 0);
// 		// model->draw(*shader, mat4(1), time, 1);
// 		// model->draw(*shader, mat4(1), time, 2);
// 		// model->draw(*shader, mat4(1));
// 		// cout << time << endl;
// 		return true;
// 	}
// };

// int		main()
// {
// 	try
// 	{
// 		Window		window(RESOLUTION, "Test");
// 		Material::init_default_texture();
// 		Material::init_default_texture_normal();

// 		string		file_name = 
// 			// "../../sources/walking_man/rp_nathan_animated_003_walking.fbx";
// 			"../../sources/dragon/Dragon_Baked_Actions_fbx_7.4_binary.fbx";
// 			// "../../sources/backpack/backpack.obj";
		
// 		Model::ptr	model = assimp_loader(file_name);
		
// 		Shader		shader;
// 		shader.compile_shader("shader_vertex.glsl", shader_type::vertex);
// 		shader.compile_shader("shader_fragment.glsl", shader_type::fragment);
// 		shader.link_shader_program();

// 		Model::box	bound = model->get_bounding_box();
		
		

// 		float		model_size = length(bound.first - bound.second);
// 		cout << "model size: " << model_size << endl;
// 		#ifdef UP_Z
// 		Camera		camera(
// 						vec3(0, -model_size * 2, model_size / 2),
// 						FRONT, 
// 						UP,
// 						pi<float>() / 2,
// 						16.0f/9,
// 						model_size * 10,
// 						model_size * 0.001
// 					);
// 		#else
// 		Camera		camera(
// 						vec3(0, model_size / 2, model_size * 2),
// 						FRONT, 
// 						UP,
// 						pi<float>() / 3,
// 						16.0f/9,
// 						model_size * 100,
// 						model_size * 0.01
// 					);
// 		#endif

// 		Light		light;
// 		light.set_position((-FRONT + UP) * model_size * 3);
// 		light.strength = model_size * 4.5;

// 		window.model = model;
// 		window.model_size = model_size;
// 		window.shader = &shader;
// 		window.light = &light;
// 		window.camera = &camera;

// 		shader.use();
// 		glEnable(GL_DEPTH_TEST);
// 		window.loop();
// 	}
// 	catch (const std::string& err)
// 	{
// 		cout << err << endl;
// 	}
// }

// #endif