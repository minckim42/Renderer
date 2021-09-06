#include "World.hpp"

#define RESOULTION				FHD
#define LIGHT_DISTANCE			DISTANCE_SUN

using namespace std;
using namespace glm;

/*##############################################################################

	World

##############################################################################*/

World::World():
	WindowGlfw(RESOULTION, "Sylvan Library"),
	dragon(*this, assimp_loader(FILE_DRAGON), 10),
	camera(
		vec3(0, 0, 0),
		vec3(1, 0, 0), 
		vec3(0, 0, 1),
		pi<float>() / 4,
		16.0f/9,
		100000,
		1
	),
	mat_identity(1)
{
	Material::init_default_texture();
	Material::init_default_texture_normal();

	shader.compile_shader("shader_vertex.glsl", shader_type::vertex);
	shader.compile_shader("shader_fragment.glsl", shader_type::fragment);
	shader.link_shader_program();


	light.set_position(vec3(-1, -1, 1) * DISTANCE_SUN);	// Sun
	light.strength = DISTANCE_SUN * 1.7;	// 1.7 ~~ sqrt(3)
	light.color =  vec3(1, 1, 0.95);		// yellow
	
	building = make_shared<Model>();
	building->add_child(assimp_loader(FILE_BUILDING_SOLID));
	building->add_child(assimp_loader(FILE_BUILDING_GROUND));
	building->add_child(assimp_loader(FILE_BUILDING_MULLION));
	building->add_child(assimp_loader(FILE_BUILDING_RAIL));
	building->add_child(assimp_loader(FILE_BUILDING_STIE));
	building->add_child(assimp_loader(FILE_BUILDING_FURNITURE));
	building->add_child(assimp_loader(FILE_BUILDING_GLASS));

	dragon.camera = &camera;
	dragon.shader = &shader;

	dragon.set_position(vec3(-20000, -10000, 0));

	hide_cursor();

	shader.use();
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glBlendEquation(GL_FUNC_ADD);
	glEnable(GL_CULL_FACE);
}

//==============================================================================

bool		World::work()
{
	glClearColor(COLOR_SKY, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	light.draw(shader);
	dragon.process();
	building->draw(shader, mat_identity);
	return true;
}