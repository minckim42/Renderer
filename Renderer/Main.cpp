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


class test
{
	public:
	
	test(int x)
	{
		cout << "default: " << this << endl;
	}
	
	test(const test& x)
	{
		cout << "const copy: " << this << endl;
	}
	
	test(test& x)
	{
		cout << "copy: " << this << endl;
	}
	
	test(const test&& x)
	{
		cout << "const move: " << this << endl;
	}
	
	test(test&& x)
	{
		cout << "move: " << this << endl;
	}

	test&	operator=(test& x)
	{
		cout << "alloc: " << this << endl;
		return *this;
	}

	test&	operator=(test&& x)
	{
		cout << "move alloc: " << this << endl;
		return *this;
	}

	~test()
	{
		cout << "byebye" << endl;
	}


};


int		main()
{
	test	t2(1);


	WindowGlfw*		win = new Window();
	win->init();
	init_glad();
	win->loop();
	delete win;

	test	t3(test(1));
	cout << &t2 << endl;
	cout << &t3 << endl;

	t3 = test(2);
	cout << &t3 << endl;

	return 0;
}