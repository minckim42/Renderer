#include "ShaderOpengl.hpp"
#include <fstream>
#include <iostream>
#include <sstream>
using namespace std;
using namespace glm;

/*=========================================
	Canonical form
=========================================*/

ShaderOpengl::~ShaderOpengl()
{
	glDeleteProgram(program);
}

/*=========================================
	Public methods
=========================================*/

GLuint			ShaderOpengl::compile_shader(const string& path, shader_type type)
{
	ifstream		ifs(path);
	size_t			len;
	stringstream	ss;

	if (ifs.is_open() == false)
		throw std::string("Failed to open shader source file: ") + path;

	ss << ifs.rdbuf();
	string code = ss.str();

	const char* data = code.c_str();
	GLuint		object = glCreateShader(static_cast<GLenum>(type));

	glShaderSource(object, 1, &data, NULL);
	glCompileShader(object);
	check_shader(object, type);
	shaders.push_back(object);
	return object;
}

//------------------------------------------------------------------------------

void			ShaderOpengl::link_shader_program()
{
	program = glCreateProgram();
	for (GLuint i : shaders)
	{
		glAttachShader(program, i);
	}
	glLinkProgram(program);
	check_program(program);
	for (GLuint i : shaders)
	{
		glDeleteShader(i);
	}
	shaders.clear();
}

//------------------------------------------------------------------------------

GLuint			ShaderOpengl::get_program() const
{
	return program;
}

//------------------------------------------------------------------------------

void			ShaderOpengl::use()
{
	glUseProgram(program);
}

//------------------------------------------------------------------------------

void			ShaderOpengl::set_uniform(const string& name, float value)
{
	glUniform1f(glGetUniformLocation(program, name.c_str()), value);
}

//------------------------------------------------------------------------------

void			ShaderOpengl::set_uniform(const string& name, int value)
{
	glUniform1i(glGetUniformLocation(program, name.c_str()), value);
}

//------------------------------------------------------------------------------

void			ShaderOpengl::set_uniform(const string& name, const vec3& value)
{
	glUniform3f(glGetUniformLocation(program, name.c_str()), value[0], value[1], value[2]);
}

//------------------------------------------------------------------------------

void			ShaderOpengl::set_uniform(const string& name, const mat3& value, bool transpose)
{
	glUniformMatrix3fv(glGetUniformLocation(program, name.c_str()), 1, GL_FALSE, value_ptr(value));
}

//------------------------------------------------------------------------------

void			ShaderOpengl::set_uniform(const string& name, const mat4& value, bool transpose)
{
	glUniformMatrix4fv(glGetUniformLocation(program, name.c_str()), 1, GL_FALSE, value_ptr(value));
}

/*=========================================
	private methods
=========================================*/

void			ShaderOpengl::check_shader(GLuint shader, shader_type type)
{
	string	shader_name;

	switch (type)
	{
	case shader_type::vertex:
		shader_name = "vertex shader";
		break;
	case shader_type::fragment:
		shader_name = "fragment shader";
		break;
	default:
		break;
	}

	int			success;
	char		log[512];
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(shader, 512, NULL, log);
		throw std::string("ERROR::SHADER::COMPILATION_FAILED: ") + shader_name + '\n' + log;
	}
}

//------------------------------------------------------------------------------

void			ShaderOpengl::check_program(GLuint program)
{
	int			success;
	char		log[512];

	glGetProgramiv(program, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(program, 512, NULL, log);
		std::string("ERROR::SHADER::LINK_FAILED\n") + log;
	}
}