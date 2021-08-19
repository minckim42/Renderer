#include "Light.hpp"

using namespace std;
using namespace glm;

Light::Light():
strength(1000),
color(1, 1, 1)
{}

Light::Light(vec3 position, float strength):
strength(strength),
color(1, 1, 1)
{
	set_position(position);
}

void		Light::draw(ShaderOpengl& shader)
{
	shader.set_uniform("light_position", get_position());
	shader.set_uniform("light_strength", strength);
	shader.set_uniform("light_color", color);
}