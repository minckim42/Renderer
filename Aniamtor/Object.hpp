#pragma once
#include <glm/glm.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/ext.hpp>
#include <memory>

/*##############################################################################

	Object

##############################################################################*/

class Object
{
	/*=========================================
		Types
	=========================================*/
	public:
	typedef std::shared_ptr<Object>		ptr;

	/*=========================================
		Members
	=========================================*/
	public:
	glm::mat4			matrix;
	glm::vec3			up;

	/*=======================================
		Constructor
	=======================================*/
	public:
	Object();
	Object(const glm::mat4& mat);
	Object(glm::vec3 position, glm::vec3 x,	glm::vec3 z); // z is prior to x
	Object(const Object& x) = default;
	
	virtual				~Object() = default;
	Object&				operator=(const Object& x) = default;
	Object&				operator=(Object&& x);

	/*=======================================
		Methods
	=======================================*/
	
	public:
	virtual Object&		move(const glm::vec3& v);
	virtual Object&		move_forward(float len);
	virtual Object&		move_left(float len);
	virtual Object&		move_up(float len);
	virtual Object&		pitch(float rad);
	// virtual Object&		pitch(float rad, glm::vec3 up);
	virtual Object&		yaw(float rad);
	virtual Object&		yaw(float rad, glm::vec3 up);

	glm::vec3			get_position() const;
	glm::vec3			get_direction() const;
	glm::vec3			get_left() const;
	glm::vec3			get_z() const;

	void				set_identity();
	void				set_position(const glm::vec3& v);
};