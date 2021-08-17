#include "Light.hpp"

using namespace std;
using namespace glm;

Light::Light(vec3 position, float strength):
strength(strength)
{
	set_position(position);
}