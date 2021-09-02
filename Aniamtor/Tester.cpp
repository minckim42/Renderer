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

// inline bool		is_odd(uint i)
// {
// 	return i & 1;
// }

// inline bool		is_even(uint i)
// {
// 	return !(i & 1);
// }

// Model::ptr		sample_model()
// {
// 	Model::ptr	model = make_shared<Model>();
// 	model->meshes.emplace_back(make_shared<Mesh>());
// 	Mesh::ptr	mesh = model->meshes[0];

// 	const uint	n_bone = 5;
// 	const uint	n_vertex = (n_bone - 1) * 4 + 2;
// 	const uint	n_face = (n_bone - 1)  *4;

// 	for (uint i = 0 ; i < n_vertex ; i++)
// 	{
// 		mesh->vertices.emplace_back();
// 		Vertex& v = mesh->vertices.back();
// 		v.position = vec3(i / 2 * 2 * 100, -50, 0);
// 		v.normal = vec3(0, 0, 1);
// 		v.tex_coord = vec2(is_odd(i) ? 0 : 1, (i / 2) / (n_vertex / 2 - 1));
// 		v.tangent = vec3(1, 0, 0);
// 		v.bi_tangent = vec3(0, 1, 0);
// 		if (i % 4 == 0 || i % 4 == 1)
// 		{
// 			v.bones[1] = i/(n_bone - 1) + 1;
// 			v.weights[0] = 0.5;
// 			v.weights[1] = 0.5;
// 		}
// 		else
// 		{
// 			v.weights[0] = 1;
// 		}
// 		v.bones[0] = i/(n_bone - 1);
// 	}

// 	for (uint i = 0 ; i < n_face ; i++)
// 	{
// 		if (is_even(i))
// 		{
// 			mesh->indices.emplace_back(i);
// 			mesh->indices.emplace_back(i + 1);
// 			mesh->indices.emplace_back(i + 2);
// 		}
// 		else
// 		{
// 			mesh->indices.emplace_back(i);
// 			mesh->indices.emplace_back(i + 2);
// 			mesh->indices.emplace_back(i + 1);
// 		}
// 	}

// 	mat4	offset = mat4(1);
// 	mesh->bone = make_shared<Bone>(mesh->matrices, offset);
// 	Bone::ptr	bone_curr = mesh->bone;
// 	bone_curr->children.emplace_back(make_shared<Bone>(mesh->matrices, offset));
// 	bone_curr->animations.emplace_back();
// 	bone_curr->animations[0].position_keys.emplace_back(vec3(0, 0, 0));
// 	bone_curr->animations[0].position_time.emplace_back(0);
// 	bone_curr->animations[0].rotation_keys.emplace_back(quat(0, 0, 0, 1));
// 	bone_curr->animations[0].rotation_time.emplace_back(0);
// 	bone_curr->animations[0].scale_keys.emplace_back(vec3(1, 1, 1));
// 	bone_curr->animations[0].scale_time.emplace_back(0);

// 	bone_curr->animations[0].position_keys.emplace_back(vec3(0, 0, 0));
// 	bone_curr->animations[0].position_time.emplace_back(1000);
// 	bone_curr->animations[0].rotation_keys.emplace_back(quat(cos(3.14/6), sin(3.14/6) * vec3(0, 0, 1)));
// 	bone_curr->animations[0].rotation_time.emplace_back(1000);
// 	bone_curr->animations[0].scale_keys.emplace_back(vec3(1, 1, 1));
// 	bone_curr->animations[0].scale_time.emplace_back(1000);

// 	for (uint i = 1 ; i < n_bone ; i++)
// 	{
// 		mat4	offset = mat4(1);
// 		offset[3] += vec4(400, 0, 0, 0);
// 		bone_curr->children.emplace_back(make_shared<Bone>(mesh->matrices, offset));
// 		bone_curr->children[0]->animations.emplace_back();
// 		bone_curr->children[0]->animations[0].position_keys.emplace_back(vec3(0, 0, 0));
// 		bone_curr->children[0]->animations[0].position_time.emplace_back(0);
// 		bone_curr->children[0]->animations[0].rotation_keys.emplace_back(quat(0, 0, 0, 1));
// 		bone_curr->children[0]->animations[0].rotation_time.emplace_back(0);
// 		bone_curr->children[0]->animations[0].scale_keys.emplace_back(vec3(1, 1, 1));
// 		bone_curr->children[0]->animations[0].scale_time.emplace_back(0);

// 		bone_curr->children[0]->animations[0].position_keys.emplace_back(vec3(0, 0, 0));
// 		bone_curr->children[0]->animations[0].position_time.emplace_back(1000);
// 		bone_curr->children[0]->animations[0].rotation_keys.emplace_back(quat(cos(3.14/6), sin(3.14/6) * vec3(0, 0, 1)));
// 		bone_curr->children[0]->animations[0].rotation_time.emplace_back(1000);
// 		bone_curr->children[0]->animations[0].scale_keys.emplace_back(vec3(1, 1, 1));
// 		bone_curr->children[0]->animations[0].scale_time.emplace_back(1000);

// 		bone_curr = bone_curr->children[0];
// 	}
// 	Material::container.emplace("temp", Material());
// 	mesh->material = &Material::container["temp"];

// 	return model;
// }

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
		model->draw(*shader, mat4(1), time);
		// cout << time << endl;
		return true;
	}
};

int		main()
{
	try
	{
		Window		window(1920, 1080, "Test");
		Material::init_default_texture();
		Material::init_default_texture_normal();

		// Model::ptr	model = assimp_loader("../../sources/walking_man/rp_nathan_animated_003_walking.fbx");
		Model::ptr	model = assimp_loader("../../sources/dragon/Dragon_Baked_Actions_fbx_7.4_binary.fbx");
		// Model::ptr	model = sample_model();
		
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