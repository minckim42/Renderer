#include "WindowGlfw.hpp"
#include "Object.hpp"
#include <iostream>
#include <glm/glm.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/ext.hpp>
using namespace std;
using namespace glm;

class Window: public WindowGlfw
{
	public:
	bool	work()
	{
		// cout << "hi\n";
		return true;
	}
	~Window()
	{};
};



int		main()
{
	WindowGlfw*		win = new Window();
	win->init();
	init_glad();
	win->loop();
	delete win;

	glm::mat4	mmm(
		1, 0, 0, 0, 
		0, 1, 0, 0,
		0, 0, 1, 0, 
		2, 2, 2, 1 );

	cout << glm::to_string(mmm) << endl;

	mmm = glm::rotate(mmm, 0.5f, vec3(0.0f, 0.0f, 1.0f));
	cout << glm::to_string(mmm) << endl;

	mat4	rot = rotate(0.1f, vec3(0, 0, 1));

	cout << to_string(rot * mmm) << endl;

	Object		a;
	cout << to_string(a.matrix) << endl;
	vec3 ve(0,0,1);
	a.yaw(0.2);
	a.yaw(0.2, ve);

	cout << to_string(a.matrix) << endl;
	return 0;
}