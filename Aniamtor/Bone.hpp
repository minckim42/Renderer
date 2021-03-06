#pragma once
#include "Animation.hpp"
#include <glm/glm.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/ext.hpp>
#include <glm/gtx/quaternion.hpp>
#include <algorithm>
#include <vector>
#include <memory>
#include <string>

/*##############################################################################

	Bone

##############################################################################*/

class Bone
{
	/*=========================================
		Types
	=========================================*/
	public:
	typedef unsigned int			uint;
	typedef std::shared_ptr<Bone>	ptr;
	
	/*=========================================
		Members
	=========================================*/
	public:
	std::vector<Animation>	animations;
	std::vector<glm::mat4>&	matrices;
	uint					idx_mat;
	glm::mat4				offset;
	glm::mat4				world_transform;
	std::vector<Bone::ptr>	children;
	// uint					idx_child;
	std::string				name;

	/*=========================================
		Constructor
	=========================================*/
	public:
	// Bone(std::vector<glm::mat4>& matrices, const glm::mat4& offset);
	Bone(
		std::vector<glm::mat4>&	matrices,
		const glm::mat4&		offset,
		const glm::mat4&		world_transform,
		const std::string&		name);

	/*=========================================
		Methods
	=========================================*/
	public:
	void		set_matrix(uint animation_id, const glm::mat4& prev, double time);
	glm::mat4&	matrix();

	private:


};