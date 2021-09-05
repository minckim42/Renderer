#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string>

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
	friend void		callback_frame(GLFWwindow* window, int width, int height);
	friend void		callback_mouse(GLFWwindow* window, double x, double y);
	/*=========================================
		Types
	=========================================*/

	private:
	typedef unsigned int		uint;

	/*=========================================
		Members
	=========================================*/

	protected:
	GLFWwindow*				_window;
	std::string				_name;
	GLFWmonitor*			_monitor;
	GLFWwindow*				_share;
	static int				_width;
	static int				_height;
	static double			_mouse_x;
	static double			_mouse_y;
	static bool				_frame_called;
	static bool				_mouse_called;

	/*=========================================
		Constructor & Destructor
	=========================================*/

	public:
	WindowGlfw();
	WindowGlfw(int width, int height, const std::string& name);
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
	bool				is_frame_called() const;
	bool				is_mouse_called() const;
	void				get_mouse_motion(int& x, int& y) const;
	void				get_mouse_position(int& x, int& y) const;
	void				get_frame_size(int& w, int& h) const;

	/*=========================================
		Other methods
	=========================================*/

	private:
	void				check_init(const std::string& function) const;
	void				check_init(const char* function) const;
	void				clear_callback_flag();

	public:
	virtual void		prepare();
	virtual void		loop();
	virtual bool		work();
	virtual void		terminate();
	void				hide_mouse();
};
/*##############################################################################

	Non member function

##############################################################################*/

void					init_glad();
void					callback_frame(GLFWwindow* window, int width, int height);
void					callback_mouse(GLFWwindow* window, double x, double y);