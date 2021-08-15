#include "WindowGlfw.hpp"
#include <iostream>

using namespace std;

class Window: public WindowGlfw
{
	public:
	bool	work()
	{
		cout << "hi\n";
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

	return 0;
}