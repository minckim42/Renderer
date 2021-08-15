#include <glm/glm.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/ext.hpp>

/*##############################################################################

	Object

##############################################################################*/

class Object
{
	/*=========================================
		Members
	=========================================*/
	
	public:
	glm::mat4			matrix;

	/*=======================================
		Canonical form
	=======================================*/
	/* constructor */	Object();
	/* constructor */	Object(const glm::mat4& mat);

	/*=======================================
		Public Methods
	=======================================*/
	
	public:
	Object&				move(const glm::vec3& v);
	Object&				move_forward(float len);
	Object&				move_left(float len);
	Object&				move_up(float len);
	Object&				pitch(float rad);
	Object&				yaw(float rad, glm::vec3 up=glm::vec3(0,0,1));

	glm::vec3			get_position() const;
	glm::vec3			get_direction() const;
	glm::vec3			get_right() const;
	glm::vec3			get_up() const;
};