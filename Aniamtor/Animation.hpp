#pragma once
#include <glm/glm.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/ext.hpp>
#include <glm/gtx/quaternion.hpp>
#include <vector>

/*##############################################################################

	Animation

##############################################################################*/

struct Animation
{
	std::vector<glm::vec3>	position_keys;
	std::vector<double>		position_time;
	std::vector<glm::quat>	rotation_keys;
	std::vector<double>		rotation_time;
	std::vector<glm::vec3>	scale_keys;
	std::vector<double>		scale_time;

	glm::mat4	interpolate(double time);

	glm::vec3	interpolate_vector_key(
					std::vector<glm::vec3>&	keys,
					std::vector<double>&	times,
					double					time);
	
	glm::quat	interpolate_quat_key(
					std::vector<glm::quat>&	keys,
					std::vector<double>&	times,
					double					time);
};