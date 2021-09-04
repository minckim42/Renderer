#include "Controlable.hpp"
#include <iostream>

using namespace std;
using namespace	glm;

Controlable::Controlable(WindowGlfw& window):
	window(window), model(nullptr), speed(1), sensitivity(1)
{}

Controlable::Controlable(WindowGlfw& window, Model::ptr model):
	window(window), model(model), speed(1), sensitivity(1)
{}

Controlable::Controlable(WindowGlfw& window, Model::ptr model, float move_speed):
	window(window), model(model), speed(speed), sensitivity(1)
{}

void		Controlable::move_process()
{
	GLFWwindow*	win_ptr = window.get_window();
	TimePoint	now = chrono::system_clock::now();
	Duration	duration(now - prev);
	
	float		len = speed * 1000 * duration.count();
	float		rad = sensitivity * duration.count();

	if (glfwGetKey(win_ptr, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(win_ptr, true); // shut down
	}
	if (glfwGetKey(win_ptr, GLFW_KEY_W) == GLFW_PRESS)
	{
		move_forward(len);
	}
	if (glfwGetKey(win_ptr, GLFW_KEY_S) == GLFW_PRESS)
	{
		move_forward(-len);
	}
	if (glfwGetKey(win_ptr, GLFW_KEY_A) == GLFW_PRESS)
	{
		move_left(len);
	}
	if (glfwGetKey(win_ptr, GLFW_KEY_D) == GLFW_PRESS)
	{
		move_left(-len);
	}
	if (glfwGetKey(win_ptr, GLFW_KEY_LEFT) == GLFW_PRESS)
	{
		yaw(rad, up);
	}
	if (glfwGetKey(win_ptr, GLFW_KEY_RIGHT) == GLFW_PRESS)
	{
		yaw(-rad, up);
	}
	if (glfwGetKey(win_ptr, GLFW_KEY_UP) == GLFW_PRESS)
	{
		pitch(rad);
	}
	if (glfwGetKey(win_ptr, GLFW_KEY_DOWN) == GLFW_PRESS)
	{
		pitch(-rad);
	}
	if (glfwGetKey(win_ptr, GLFW_KEY_SPACE) == GLFW_PRESS)
	{
		move(up * len);
	}
	if (glfwGetKey(win_ptr, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
	{
		move(up * -len);
	}
	if (glfwGetKey(win_ptr, GLFW_KEY_LEFT_BRACKET) == GLFW_PRESS)
	{
		speed /= 1.1;
		if (speed < 0.0000001)
			speed = 0.0000001;
		cout << "Speed decrease: " << speed << endl;
	}
	if (glfwGetKey(win_ptr, GLFW_KEY_RIGHT_BRACKET) == GLFW_PRESS)
	{
		speed *= 1.1;
		cout << "Speed increase: " << speed << endl;
	}
	if (glfwGetKey(win_ptr, GLFW_KEY_O) == GLFW_PRESS)
	{
		sensitivity /= 1.1;
		if (speed < 0.0000001)
			speed = 0.0000001;
		cout << "Rotate sensitivy decrease: " << speed << endl;
	}
	if (glfwGetKey(win_ptr, GLFW_KEY_P) == GLFW_PRESS)
	{
		sensitivity *= 1.1;
		cout << "Rotate sensitivy increase: " << speed << endl;
	}
	// if (glfwGetKey(win_ptr, GLFW_KEY_R) == GLFW_PRESS)
	// {
	// 	time = 0;
	// }


}