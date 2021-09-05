#include "Controlable.hpp"
#include <iostream>

using namespace std;
using namespace	glm;

/*##############################################################################

	State

##############################################################################*/

#define TIME_WALK_END	1500.f
#define TIME_DEPART_END	1910.f
#define TIME_FLY_START	TIME_DEPART_END
#define TIME_FLY_END	4435.f
#define TIME_LAND_START	TIME_FLY_END
#define TIME_LAND_END	9000.f
#define TIME_STOP_END	3000.f

#define MINIMUM_HEIGHT	1000.f

// double			time_fly_start = 1200;
// double			time_fly_end = 4250;


StateWalk*		State::walk;
StateFly*		State::fly;
StateDepart*	State::depart;
StateLand*		State::land;
StateStop*		State::stop;

//==============================================================================

State::State(Controlable* controlable):
controlable(controlable),
start(chrono::system_clock::now()),
prev(chrono::system_clock::now())
{}

StateWalk::StateWalk(Controlable* controlable): State(controlable) {}
StateFly::StateFly(Controlable* controlable): State(controlable) {}
StateDepart::StateDepart(Controlable* controlable): State(controlable) {}
StateLand::StateLand(Controlable* controlable): State(controlable) {}
StateStop::StateStop(Controlable* controlable): State(controlable) {}

//==============================================================================

State*		StateWalk::process()
{
	// cout << "walk" << endl;
	GLFWwindow*	win_ptr = controlable->window.get_window();
	TimePoint	now = chrono::system_clock::now();
	Duration	duration_prev(now - prev);
	Duration	duration_start(now - start);
	float		len = controlable->speed * 1000 * duration_prev.count();
	float		rad = controlable->sensitivity * duration_prev.count();
	bool		state_walking = false;
	vec3		front = cross(controlable->get_left(), controlable->up);
	float		time = duration_start.count() * 1000;

	prev = now;
	controlable->model->draw(*controlable->shader, controlable->matrix, time, 2);
	if (time > TIME_WALK_END)
	{
		start = now;
	}

	if (glfwGetKey(win_ptr, GLFW_KEY_W) == GLFW_PRESS)
	{
		controlable->move(front * len);
		state_walking = true;
	}
	if (glfwGetKey(win_ptr, GLFW_KEY_S) == GLFW_PRESS)
	{
		controlable->move(front * -len);
		state_walking = true;
	}
	if (glfwGetKey(win_ptr, GLFW_KEY_A) == GLFW_PRESS)
	{
		controlable->move_left(len);
		state_walking = true;
	}
	if (glfwGetKey(win_ptr, GLFW_KEY_D) == GLFW_PRESS)
	{
		controlable->move_left(-len);
		state_walking = true;
	}
	if (glfwGetKey(win_ptr, GLFW_KEY_SPACE) == GLFW_PRESS)
	{
		State::depart->start = now;
		State::depart->prev = now;
		return State::depart;
	}
	if (controlable->window.is_mouse_called())
	{
		int	x, y;
		controlable->window.get_mouse_motion(x, y);
		controlable->yaw(rad * -x);
	}
	if (state_walking == false)
	{
		State::stop->start = now;
		State::stop->prev = now;
		return State::stop;
	}

	return State::walk;
}

//==============================================================================

State*		StateDepart::process()
{
	// cout << "depart" << endl;
	GLFWwindow*	win_ptr = controlable->window.get_window();
	TimePoint	now = chrono::system_clock::now();
	Duration	duration_prev(now - prev);
	Duration	duration_start(now - start);
	float		len = controlable->speed * 1000 * duration_prev.count();
	float		rad = controlable->sensitivity * duration_prev.count();
	float		time = duration_start.count() * 1000;

	prev = now;
	// vec3		front = cross(controlable->get_left(), controlable->up);

	controlable->model->draw(*controlable->shader, controlable->matrix, time, 0);
	controlable->matrix[3].z = MINIMUM_HEIGHT / TIME_DEPART_END * time + 1;
	// cout << controlable->matrix[3].z << "time: " << time << endl;
	// if (controlable->matrix[3].z > MINIMUM_HEIGHT)
	if (time >= TIME_DEPART_END)
	{
		State::fly->start = now;
		State::fly->prev = now;
		return State::fly;
	}

	if (controlable->window.is_mouse_called())
	{
		int	x, y;
		controlable->window.get_mouse_motion(x, y);
		controlable->yaw(rad * -x);
	}
	return State::depart;
}

//==============================================================================

State*		StateFly::process()
{
	// cout << "fly" << endl;
	GLFWwindow*	win_ptr = controlable->window.get_window();
	TimePoint	now = chrono::system_clock::now();
	Duration	duration_prev(now - prev);
	Duration	duration_start(now - start);
	float		len = controlable->speed * 1000 * duration_prev.count();
	float		rad = controlable->sensitivity * duration_prev.count();
	float		time = duration_start.count() * 1000 + TIME_FLY_START;

	prev = now;
	controlable->model->draw(*controlable->shader, controlable->matrix, time, 0);
	if (time > TIME_FLY_END)
	{
		start = now;
	}
	if (glfwGetKey(win_ptr, GLFW_KEY_W) == GLFW_PRESS)
	{
		controlable->move_forward(len);
	}
	if (glfwGetKey(win_ptr, GLFW_KEY_S) == GLFW_PRESS)
	{
		controlable->move_forward(-len);
	}
	if (glfwGetKey(win_ptr, GLFW_KEY_A) == GLFW_PRESS)
	{
		controlable->move_left(len);
	}
	if (glfwGetKey(win_ptr, GLFW_KEY_D) == GLFW_PRESS)
	{
		controlable->move_left(-len);
	}
	if (glfwGetKey(win_ptr, GLFW_KEY_SPACE) == GLFW_PRESS)
	{
		controlable->move_up(len);
	}
	if (glfwGetKey(win_ptr, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
	{
		controlable->move_up(-len);
	}
	if (controlable->window.is_mouse_called())
	{
		int	x, y;
		controlable->window.get_mouse_motion(x, y);
		controlable->yaw(rad * -x, controlable->up);
		controlable->pitch(-rad * y);
	}
	if (controlable->get_position().z < MINIMUM_HEIGHT)
	{
		controlable->matrix[2] = vec4(controlable->up, 0);
		controlable->matrix[0] = vec4(normalize(cross(controlable->get_left(), controlable->up)), 0);
		State::land->start = now;
		State::land->prev = now;
		return State::land;
	}
	// if (glfwGetKey(win_ptr, GLFW_KEY_O) == GLFW_PRESS)
	// {
	// 	time_fly_start -= 5;
	// 	cout << "start: " << time_fly_start << endl;
	// }
	// if (glfwGetKey(win_ptr, GLFW_KEY_P) == GLFW_PRESS)
	// {
	// 	time_fly_start += 5;
	// 	cout << "start: " << time_fly_start << endl;
	// }
	// if (glfwGetKey(win_ptr, GLFW_KEY_LEFT_BRACKET) == GLFW_PRESS)
	// {
	// 	time_fly_end -= 5;
	// 	cout << "end: " << time_fly_end << endl;
	// }
	// if (glfwGetKey(win_ptr, GLFW_KEY_RIGHT_BRACKET) == GLFW_PRESS)
	// {
	// 	time_fly_end += 5;
	// 	cout << "end: " << time_fly_end << endl;
	// }

	return State::fly;
}

//==============================================================================

State*		StateLand::process()
{
	// cout << "land" << endl;
	GLFWwindow*	win_ptr = controlable->window.get_window();
	TimePoint	now = chrono::system_clock::now();
	Duration	duration_prev(now - prev);
	Duration	duration_start(now - start);
	float		len = controlable->speed * 1000 * duration_prev.count();
	float		rad = controlable->sensitivity * duration_prev.count();
	float		time = duration_start.count() * 1000;

	prev = now;

	controlable->model->draw(*controlable->shader, controlable->matrix, time + TIME_LAND_START, 0);
	if (time > TIME_LAND_END)
	{
		start = now;
	}
	controlable->move_up(-(MINIMUM_HEIGHT / (TIME_DEPART_END) * duration_prev.count() * 1000 + 10));
	if (controlable->get_position().z < 0)
	{
		controlable->matrix[3].z = 0;
		State::stop->start = now;
		State::stop->prev = now;
		return State::stop;
	}
	if (controlable->get_position().z < 0)
		controlable->matrix[3].z = 0;
	if (controlable->window.is_mouse_called())
	{
		int	x, y;
		controlable->window.get_mouse_motion(x, y);
		controlable->yaw(rad * -x);
	}

	return State::land;
}

//==============================================================================

State*		StateStop::process()
{
	// cout << "stop" << endl;
	GLFWwindow*	win_ptr = controlable->window.get_window();
	TimePoint	now = chrono::system_clock::now();
	Duration	duration_prev(now - prev);
	Duration	duration_start(now - start);
	float		len = controlable->speed * 1000 * duration_prev.count();
	float		rad = controlable->sensitivity * duration_prev.count();
	float		time = duration_start.count() * 1000;

	prev = now;

	controlable->model->draw(*controlable->shader, controlable->matrix, time, 1);
	if (time > TIME_STOP_END)
	{
		start = now;
	}
	if (glfwGetKey(win_ptr, GLFW_KEY_W) == GLFW_PRESS)
	{
		State::walk->start = now;
		State::walk->prev = now;
		return State::walk;
	}
	if (glfwGetKey(win_ptr, GLFW_KEY_S) == GLFW_PRESS)
	{
		State::walk->start = now;
		State::walk->prev = now;
		return State::walk;
	}
	if (glfwGetKey(win_ptr, GLFW_KEY_A) == GLFW_PRESS)
	{
		State::walk->start = now;
		State::walk->prev = now;
		return State::walk;
	}
	if (glfwGetKey(win_ptr, GLFW_KEY_D) == GLFW_PRESS)
	{
		State::walk->start = now;
		State::walk->prev = now;
		return State::walk;
	}
	if (glfwGetKey(win_ptr, GLFW_KEY_SPACE) == GLFW_PRESS)
	{
		State::depart->start = now;
		State::depart->prev = now;
		return State::depart;
	}
	if (controlable->window.is_mouse_called())
	{
		int	x, y;
		controlable->window.get_mouse_motion(x, y);
		controlable->yaw(rad * -x);
	}
	return State::stop;	
}

/*##############################################################################

	Controlable

##############################################################################*/

Controlable::Controlable(WindowGlfw& window):
	window(window), model(nullptr), speed(1), sensitivity(0.02)
{
	init_state();
	state = State::stop;
}

Controlable::Controlable(WindowGlfw& window, Model::ptr model):
	window(window), model(init_model(model)), speed(1), sensitivity(0.02)
{
	init_state();
	init_model();
	state = State::stop;
}

Controlable::Controlable(WindowGlfw& window, Model::ptr model, float move_speed):
	window(window), model(init_model(model)), speed(speed), sensitivity(0.02)
{
	init_state();
	state = State::stop;
}

Controlable::~Controlable()
{
	delete_state();
}

void		Controlable::init_state()
{
	State::walk = new StateWalk(this);
	State::fly = new StateFly(this);
	State::stop = new StateStop(this);
	State::depart = new StateDepart(this);
	State::land = new StateLand(this);
}

void		Controlable::delete_state()
{
	delete State::walk;
	delete State::fly;
	delete State::stop;
	delete State::depart;
	delete State::land;
}

void		Controlable::process()
{
	camera->matrix = matrix;
	camera->move_forward(-10000);
	camera->move_up(3000);
	camera->update_view();
	shader->set_uniform("eye", camera->get_position());
	shader->set_uniform("view", camera->view);
	shader->set_uniform("projection", camera->projection);	
	state = state->process();

	if (glfwGetKey(window.get_window(), GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window.get_window(), true); // shut down
	}
	// cout << to_string(matrix) << endl;
}

Model::ptr	Controlable::init_model(Model::ptr model_ptr)
{
	Model::ptr	root = make_shared<Model>();
	root->add_child(model_ptr);
	model_ptr->matrix = inverse(mat4(
		0, 0, 1, 0,
		1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, 0, 1
	) * model->matrix);
	root->up = vec3(0, 0, 1);
	return root;
}












// void		Controlable::key_process()
// {
// 	GLFWwindow*	win_ptr = window.get_window();
// 	TimePoint	now = chrono::system_clock::now();
// 	Duration	duration(now - prev);
	
// 	float		len = speed * 1000 * duration.count();
// 	float		rad = sensitivity * duration.count();

// 	if (glfwGetKey(win_ptr, GLFW_KEY_ESCAPE) == GLFW_PRESS)
// 	{
// 		glfwSetWindowShouldClose(win_ptr, true); // shut down
// 	}
// 	if (glfwGetKey(win_ptr, GLFW_KEY_W) == GLFW_PRESS)
// 	{
// 		move_forward(len);
// 	}
// 	if (glfwGetKey(win_ptr, GLFW_KEY_S) == GLFW_PRESS)
// 	{
// 		move_forward(-len);
// 	}
// 	if (glfwGetKey(win_ptr, GLFW_KEY_A) == GLFW_PRESS)
// 	{
// 		move_left(len);
// 	}
// 	if (glfwGetKey(win_ptr, GLFW_KEY_D) == GLFW_PRESS)
// 	{
// 		move_left(-len);
// 	}
// 	if (glfwGetKey(win_ptr, GLFW_KEY_LEFT) == GLFW_PRESS)
// 	{
// 		yaw(rad, u-p);
// 	}
// 	if (glfwGetKey(win_ptr, GLFW_KEY_RIGHT) == GLFW_PRESS)
// 	{
// 		yaw(-rad, -up);
// 	}
// 	if (glfwGetKey(win_ptr, GLFW_KEY_UP) == GLFW_PRESS)
// 	{
// 		pitch(rad);
// 	}
// 	if (glfwGetKey(win_ptr, GLFW_KEY_DOWN) == GLFW_PRESS)
// 	{
// 		pitch(-rad);
// 	}
// 	if (glfwGetKey(win_ptr, GLFW_KEY_SPACE) == GLFW_PRESS)
// 	{
// 		move(up * len);
// 	}
// 	if (glfwGetKey(win_ptr, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
// 	{
// 		move(up * -len);
// 	}
// 	if (glfwGetKey(win_ptr, GLFW_KEY_LEFT_BRACKET) == GLFW_PRESS)
// 	{
// 		speed /= 1.1;
// 		if (speed < 0.0000001)
// 			speed = 0.0000001;
// 		cout << "Speed decrease: " << speed << endl;
// 	}
// 	if (glfwGetKey(win_ptr, GLFW_KEY_RIGHT_BRACKET) == GLFW_PRESS)
// 	{
// 		speed *= 1.1;
// 		cout << "Speed increase: " << speed << endl;
// 	}
// 	if (glfwGetKey(win_ptr, GLFW_KEY_O) == GLFW_PRESS)
// 	{
// 		sensitivity /= 1.1;
// 		if (speed < 0.0000001)
// 			speed = 0.0000001;
// 		cout << "Rotate sensitivy decrease: " << speed << endl;
// 	}
// 	if (glfwGetKey(win_ptr, GLFW_KEY_P) == GLFW_PRESS)
// 	{
// 		sensitivity *= 1.1;
// 		cout << "Rotate sensitivy increase: " << speed << endl;
// 	}
// 	// if (glfwGetKey(win_ptr, GLFW_KEY_R) == GLFW_PRESS)
// 	// {
// 	// 	time = 0;
// 	// }


// }