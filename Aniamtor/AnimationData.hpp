#include <glm/glm.hpp>
#include <vector>

#include "Mesh.hpp"

class AnimationData
{
public:
	std::vector<Mesh>		meshes;
	std::vector<glm::mat4>	matrices;


	AnimationData(/* args */);
	~AnimationData();
};
