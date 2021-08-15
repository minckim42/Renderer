#include "WindowGlfw.hpp"
#include <iostream>

/*##############################################################################
	WindowGlfw
##############################################################################*/

using namespace std;

/* constructor */	WindowGlfw::WindowGlfw():
_window(0),
_name("nonamed"),
_width(1280),
_height(720),
_monitor(0),
_share(0)
{}

//------------------------------------------------------------------------------

/* constructor */	WindowGlfw::WindowGlfw(int width, int height, const std::string& name):
_window(0),
_name(name),
_width(width),
_height(height),
_monitor(0),
_share(0)
{}

//------------------------------------------------------------------------------

/* destructor */	WindowGlfw::~WindowGlfw()
{
	if (_window)
		glfwTerminate();
}

//------------------------------------------------------------------------------

GLFWwindow*			WindowGlfw::init()
{
	check_init(__func__);
	glfwInit();
	init_context_version_minor(3);
	init_context_version_major(3);
	init_opengl_profile(opengl_profile::core);
	_window = glfwCreateWindow(_width, _height, _name.c_str(), _monitor, _share);
	if (!_window)
	{
		glfwTerminate();
		throw string("GLFW: Failed to create window");
	}
	glfwMakeContextCurrent(_window);
	return _window;
}

//------------------------------------------------------------------------------

WindowGlfw&		WindowGlfw::init_context_version_major(int value)
{
	check_init(__func__);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, value);
	return *this;
}

//------------------------------------------------------------------------------

WindowGlfw&		WindowGlfw::init_context_version_minor(int value)
{
	check_init(__func__);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, value);
	return *this;
}

//------------------------------------------------------------------------------

WindowGlfw&		WindowGlfw::init_opengl_profile(opengl_profile profile)
{
	check_init(__func__);
	glfwWindowHint(GLFW_OPENGL_PROFILE, static_cast<int>(profile));
	return *this;
}

//------------------------------------------------------------------------------

WindowGlfw&		WindowGlfw::init_width(int value)
{
	check_init(__func__);
	_width = value;
	return *this;
}

//------------------------------------------------------------------------------

WindowGlfw&		WindowGlfw::init_height(int value)
{
	check_init(__func__);
	_height = value;
	return *this;
}

//------------------------------------------------------------------------------

GLFWwindow*		WindowGlfw::get_window() const
{
	return _window;
}

//------------------------------------------------------------------------------

const std::string&	WindowGlfw::get_name() const
{
	return _name;
}

//------------------------------------------------------------------------------

int					WindowGlfw::get_width() const
{
	return _width;
}

//------------------------------------------------------------------------------

int					WindowGlfw::get_height() const
{
	return _height;
}

//------------------------------------------------------------------------------

bool				WindowGlfw::is_init() const
{
	return static_cast<bool>(_window);
}

//------------------------------------------------------------------------------

void				WindowGlfw::check_init(const string& function) const
{
	if (is_init())
		throw string("GLFW: Already initialized: ") + function;
}

void				WindowGlfw::check_init(const char* function) const
{
	if (is_init())
		throw string("GLFW: Already initialized: ") + function;
}

//------------------------------------------------------------------------------

void				WindowGlfw::prepare()
{}

//------------------------------------------------------------------------------

bool				WindowGlfw::work()
{
	return true;
}

//------------------------------------------------------------------------------

void				WindowGlfw::loop()
{
	prepare();
	while (!glfwWindowShouldClose(_window) && work())
	{
		glfwSwapBuffers(_window);
		glfwPollEvents();
	}
	terminate();
}

//------------------------------------------------------------------------------

void				WindowGlfw::terminate()
{}

//------------------------------------------------------------------------------

void			init_glad()
{
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		throw string("GLAD: Failed to initialize GLAD");
}

