#include "WindowGlfw.hpp"
#include <iostream>

using namespace std;

/*##############################################################################

	WindowGlfw

##############################################################################*/
int				WindowGlfw::_width = 1920;
int				WindowGlfw::_height = 1080;
double			WindowGlfw::_mouse_x = WindowGlfw::_width / 2;
double			WindowGlfw::_mouse_y = WindowGlfw::_height / 2;
bool			WindowGlfw::_frame_called = false;
bool			WindowGlfw::_mouse_called = false;


//------------------------------------------------------------------------------

WindowGlfw::WindowGlfw():
_window(0),
_name("nonamed"),
_monitor(0),
_share(0)
{}

//------------------------------------------------------------------------------

WindowGlfw::WindowGlfw(int width, int height, const std::string& name):
_window(0),
_name(name),
_monitor(0),
_share(0)
{
	_width = width;
	_height = height;
	init();
	init_glad();
}

//------------------------------------------------------------------------------

WindowGlfw::~WindowGlfw()
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

bool				WindowGlfw::is_frame_called() const
{
	return _frame_called;
}

//------------------------------------------------------------------------------

bool				WindowGlfw::is_mouse_called() const
{
	return _mouse_called;
}

//------------------------------------------------------------------------------

void				WindowGlfw::get_mouse_motion(int& x, int& y) const
{
	static int		prev_x = WindowGlfw::_mouse_x;
	static int		prev_y = WindowGlfw::_mouse_y;
	x = _mouse_x - prev_x;
	y = _mouse_y - prev_y;
	prev_x = _mouse_x;
	prev_y = _mouse_y;
}

//------------------------------------------------------------------------------

void				WindowGlfw::get_mouse_position(int& x, int& y) const
{
	x = _mouse_x;
	y = _mouse_y;
}

//------------------------------------------------------------------------------

void				WindowGlfw::get_frame_size(int& w, int& h) const
{
	w = _width;
	h = _height;
}

//------------------------------------------------------------------------------

void				WindowGlfw::check_init(const string& function) const
{
	if (is_init())
		throw string("GLFW: Already initialized: ") + function;
}

//------------------------------------------------------------------------------

void				WindowGlfw::check_init(const char* function) const
{
	if (is_init())
		throw string("GLFW: Already initialized: ") + function;
}

//------------------------------------------------------------------------------

void				WindowGlfw::clear_callback_flag()
{
	_frame_called = false;
	_mouse_called = false;
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
	glfwSetFramebufferSizeCallback(_window, callback_frame);
	glfwSetCursorPosCallback(_window, callback_mouse);
	while (!glfwWindowShouldClose(_window) && work())
	{
		glfwSwapBuffers(_window);
		clear_callback_flag();
		glfwPollEvents();
	}
	terminate();
}

//------------------------------------------------------------------------------

void				WindowGlfw::terminate()
{}

//------------------------------------------------------------------------------

void				WindowGlfw::hide_cursor()
{
	glfwSetInputMode(_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

/*##############################################################################

	Non member function

##############################################################################*/

void			init_glad()
{
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		throw string("GLAD: Failed to initialize GLAD");
}

//------------------------------------------------------------------------------

void			callback_frame(GLFWwindow* window, int width, int height)
{
	WindowGlfw::_width = width;
	WindowGlfw::_height = height;
	WindowGlfw::_frame_called = true;
}

//------------------------------------------------------------------------------

void			callback_mouse(GLFWwindow* window, double x, double y)
{
	WindowGlfw::_mouse_x = x;
	WindowGlfw::_mouse_y = y;
	WindowGlfw::_mouse_called = true;
}