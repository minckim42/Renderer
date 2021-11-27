#include "World.hpp"
#include <iostream>

using namespace std;

int			main(int argc, char** argv)
{
	try
	{
		World	world;
		world.loop();
	}
	catch(const string& err)
	{
		std::cerr << err << '\n';
	}
}