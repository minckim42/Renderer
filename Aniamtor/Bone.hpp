#include <glm/glm.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/ext.hpp>
#include <algorithm>
#include <vector>

class Bone
{
	public:
	typedef unsigned int	uint;

	std::vector<glm::vec3>	position_keys;
	std::vector<double>		position_time;
	std::vector<glm::quat>	rotation_keys;
	std::vector<double>		rotation_time;
	std::vector<glm::vec3>	scale_keys;
	std::vector<double>		scale_time;
	std::vector<glm::mat4>&	matrices;
	uint					idx_mat;
	glm::mat4				offset;
	std::vector<Bone*>		children;

	private:
	void		set_matrix(
					const glm::vec3& parent_position,
					const glm::quat& parent_rotation,
					const glm::vec3& parent_scale,
					double time);
	glm::vec3	interpolate_vector_key(
					std::vector<glm::vec3>&	keys,
					std::vector<double>&	times,
					double					time);
	glm::quat	interpolate_quat_key(
					std::vector<glm::quat>&	keys,
					std::vector<double>&	times,
					double					time);
};