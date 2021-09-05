#pragma once
#include "WindowGlfw.hpp"
#include "Object.hpp"
#include "Model.hpp"
#include "Camera.hpp"
#include <chrono>

/*##############################################################################

	State

##############################################################################*/

class StateWalk;
class StateFly;
class StateDepart;
class StateLand;
class StateStop;
class Controlable;

class State
{
	public:
	typedef std::chrono::system_clock::time_point	TimePoint;
	typedef std::chrono::duration<double>			Duration;
	
	public:
	TimePoint			start;
	TimePoint			prev;
	Controlable*		controlable;

	static StateWalk*	walk;
	static StateFly*	fly;
	static StateDepart*	depart;
	static StateLand*	land;
	static StateStop*	stop;

	State(Controlable* controlable);
	virtual State*		process() = 0;
};

class StateWalk: public State
{
	public:
	StateWalk(Controlable* controlable);
	State*	process();
};

class StateFly: public State
{
	public:
	StateFly(Controlable* controlable);
	State*	process();
};

class StateDepart: public State
{
	public:
	StateDepart(Controlable* controlable);
	State*	process();
};

class StateLand: public State
{
	public:
	StateLand(Controlable* controlable);
	State*	process();
};

class StateStop: public State
{
	public:
	StateStop(Controlable* controlable);
	State*	process();
};

/*##############################################################################

	Controlable

##############################################################################*/

class Controlable: public Object
{
	/*=========================================
		Type
	=========================================*/
	typedef std::chrono::system_clock::time_point	TimePoint;
	typedef std::chrono::duration<double>			Duration;
	/*=========================================
		Members
	=========================================*/
	public:
	WindowGlfw&		window;
	Model::ptr		model;
	float			speed;	// meter per second
	float			sensitivity;
	TimePoint		prev;
	State*			state;
	Shader*			shader;
	Camera*			camera;

	/*=======================================
		Constructor
	=======================================*/
	Controlable(WindowGlfw& window);
	Controlable(WindowGlfw& window, Model::ptr model);
	Controlable(WindowGlfw& window, Model::ptr model, float speed);
	virtual	~Controlable();
	/*=======================================
		Methods
	=======================================*/	
	void		process();
	void		init_state();
	Model::ptr	init_model(Model::ptr model);
	void		delete_state();
	void		update_camera();
};


