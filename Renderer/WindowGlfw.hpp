#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string>
#include "common.hpp"
#include "RendererBase.hpp"

/*##############################################################################

	WindowGlfw

##############################################################################*/

/*=========================================
	Enum classes
=========================================*/

enum class opengl_profile	
{
	core = GLFW_OPENGL_CORE_PROFILE
};

class WindowGlfw
{
	/*=========================================
		Types
	=========================================*/

	private:
	typedef unsigned int		uint;

	/*=========================================
		Members
	=========================================*/

	protected:
	GLFWwindow*			_window;
	std::string			_name;
	int					_width;
	int					_height;
	GLFWmonitor*		_monitor;
	GLFWwindow*			_share;

	/*=========================================
		Constructor & Destructor
	=========================================*/

	public:
	/* constructor */	WindowGlfw();
	/* constructor */	WindowGlfw(int width, int height, const std::string& name);
	virtual				~WindowGlfw();

	/*=========================================
		Initializer
	=========================================*/

	GLFWwindow*			init();
	WindowGlfw&			init_context_version_minor(int value=3);
	WindowGlfw&			init_context_version_major(int value=3);
	WindowGlfw&			init_opengl_profile(opengl_profile profile=opengl_profile::core);
	WindowGlfw&			init_monitor(GLFWmonitor* monitor);
	WindowGlfw&			init_share(GLFWwindow* share);
	WindowGlfw&			init_width(int value);
	WindowGlfw&			init_height(int value);

	/*=========================================
		Getter
	=========================================*/

	GLFWwindow*			get_window() const;
	const std::string&	get_name() const;
	int					get_width() const;
	int					get_height() const;

	bool				is_init() const;

	/*=========================================
		Other methods
	=========================================*/

	private:
	void				check_init(const std::string& function) const;
	void				check_init(const char* function) const;

	public:
	virtual void		prepare();
	virtual void		loop();
	virtual bool		work();
	virtual void		terminate();
};

/*=========================================
	Non member function
=========================================*/

void					init_glad();
void					frame_resize(GLFWwindow* window, int width, int height);