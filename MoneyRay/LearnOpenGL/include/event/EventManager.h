#pragma once
#ifndef EventManager_h__
#define EventManager_h__

// GLEW
#define GLEW_STATIC
#include <GL/glew.h>
// GLFW
#include <GLFW/glfw3.h>
#include <iostream>

namespace LOGL
{
	class EventManager
	{
	public:
		void ReceiveUserInput(GLFWwindow* window, int key, int scancode, int action, int mode);
	protected:
	private:
	};
}
#endif // EventManager_h__