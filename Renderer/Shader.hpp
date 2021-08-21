#pragma once
#include <vector>
#include <string>

#include <glad/glad.h>
#include <glm/glm.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/ext.hpp>

/*##############################################################################

	Shader Opengl

##############################################################################*/

/*
compile_shader(path, type);
compile_shader(path, type);
...
compile_shader(path, type);

link_shader_program();

*/


/*=========================================
	Enum classes
=========================================*/

enum class shader_type
{
	vertex = GL_VERTEX_SHADER,
	tess_control = GL_TESS_CONTROL_SHADER,
	tess_evaluation = GL_TESS_EVALUATION_SHADER,
	geometry = GL_GEOMETRY_SHADER,
	fragment = GL_FRAGMENT_SHADER,
	compute = GL_COMPUTE_SHADER
};

class Shader
{
	/*=========================================
		Members
	=========================================*/

	private:
	GLuint				program;
	std::vector<GLuint>	shaders;

	/*=======================================
		Constructor
	=======================================*/
	
	public:
	Shader();

	virtual				~Shader();

	/*=======================================
		Methods
	=======================================*/
	
	public:
	GLuint				compile_shader(const std::string& path, shader_type type);
	void				link_shader_program();
	GLuint				get_program() const;
	void				use();
	void				set_uniform(const std::string& name, float value);
	void				set_uniform(const std::string& name, int value);
	void				set_uniform(const std::string& name, const glm::vec3& value);
	void				set_uniform(const std::string& name, const glm::mat3& value, bool transpose = GL_FALSE);
	void				set_uniform(const std::string& name, const glm::mat4& value, bool transpose = GL_FALSE);
	
	private:
	void				check_shader(GLuint shader, shader_type);
	void				check_program(GLuint program);
};