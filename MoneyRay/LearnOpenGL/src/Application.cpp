#include "Application.h"
#include <functional>
#include <iostream>

void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	std::cout << key << std::endl;
}

LOGL::Application::Application() :m_GraphicsWindows()
{

}

LOGL::Application::~Application()
{

}

int LOGL::Application::Init()
{
	InitGraphicsWindow();
	InitEvent();
	InitRenderManager();
	return 0;
}

int LOGL::Application::Run()
{
	while (!glfwWindowShouldClose(m_GraphicsWindows.GetGLFWWindow()))
	{
		glfwPollEvents();
		Update();
		Render();
		glfwSwapBuffers(m_GraphicsWindows.GetGLFWWindow());
	}

	m_GraphicsWindows.DestroyGraphicsWindow();
	return 0;
}

LOGL::RenderManager& LOGL::Application::GetRenderManager()
{
	return m_RenderManager;
}

void LOGL::Application::InitEvent()
{
	std::function<void(GLFWwindow*, int, int, int, int)> fn = 
		[&](GLFWwindow* window, int key, int scancode, int action, int mode) 
	{
		m_EventManager.ReceiveUserInput(window, key, scancode, action, mode);
	};
	//glfwSetKeyCallback(m_GraphicsWindows.GetGLFWWindow(), fn.target<void(GLFWwindow*, int, int, int, int)>());
	glfwSetKeyCallback(m_GraphicsWindows.GetGLFWWindow(), KeyCallback);
}

void LOGL::Application::InitGraphicsWindow()
{
	m_GraphicsWindows.Init();
}

void LOGL::Application::InitRenderManager()
{
	m_RenderManager.Init();
}

void LOGL::Application::Update()
{

}

void LOGL::Application::Render()
{
	m_RenderManager.Render();
}
