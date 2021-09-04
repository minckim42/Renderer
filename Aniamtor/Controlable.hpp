#pragma once
#include "WindowGlfw.hpp"
#include "Object.hpp"
#include "Model.hpp"
#include "Camera.hpp"
#include <chrono>

class Controlable: public Object
{
	typedef std::chrono::system_clock::time_point	TimePoint;
	typedef std::chrono::duration<double>			Duration;

	public:
	WindowGlfw&		window;
	Model::ptr		model;
	float			speed;	// meter per second
	float			sensitivity;
	TimePoint		prev;

	Controlable(WindowGlfw& window);
	Controlable(WindowGlfw& window, Model::ptr model);
	Controlable(WindowGlfw& window, Model::ptr model, float speed);
	
	void	move_process();
};