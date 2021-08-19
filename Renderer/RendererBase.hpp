#pragma once
#include <GLFW/glfw3.h>

class RendererBase
{
	public:
	virtual void		prepare() = 0;
	virtual bool		loop() = 0;
	virtual void		terminate() = 0;
};
