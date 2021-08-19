#include "WindowGlfw.hpp"
#include "Renderer.hpp"
#include "Object.hpp"
#include <iostream>
#include <glm/glm.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/ext.hpp>
using namespace std;
using namespace glm;

//#define BOX
#define SONA

int		main()
{
	try
	{
		WindowGlfw	window(1920, 1080, "test");
		Renderer	renderer;
		window.init();
		init_glad();
		Material::init_default_texture();
		Material::init_default_texture_normal();

		window.renderer = &renderer;
		renderer.window = window.get_window();

		renderer.shader.compile_shader("shader_vertex.glsl", shader_type::vertex);
		renderer.shader.compile_shader("shader_fragment.glsl", shader_type::fragment);
		renderer.shader.link_shader_program();

		renderer.light.set_position(vec3(5000, 5000, 5000));
		renderer.light.strength = 80000;

		#ifdef BOX
		renderer.add_file("./box/box.obj", model_format::obj);
		#endif

		#ifdef SONA
		renderer.add_file("./sona/cloth.obj", model_format::obj);
		renderer.add_file("./sona/skin.obj", model_format::obj);
		renderer.add_file("./sona/hair.obj", model_format::obj);
		renderer.add_file("./sona/weapon.obj", model_format::obj);
		#endif

		window.loop();
	}
	catch(const string& e)
	{
		std::cerr << e << '\n';
	}
	


	return 0;
}