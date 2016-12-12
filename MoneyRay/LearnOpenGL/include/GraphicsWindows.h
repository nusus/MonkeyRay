#pragma once
#ifndef GraphicsWindows_h__
#define GraphicsWindows_h__
// GLEW
#define GLEW_STATIC
#include <GL/glew.h>
// GLFW
#include <GLFW/glfw3.h>

#include <ctype.h>
#include <stdint.h>
#include <string>
#include <iostream>
#include <memory>

namespace LOGL
{
	class GraphicsWindows
	{
	public:
		int Init();

		int DestroyGraphicsWindow();

		uint32_t GetScreenHeight() const;

		uint32_t GetScreenWidth() const;

		uint32_t GetScreenX() const;

		uint32_t GetScreenY() const;

		std::string GetWindowName() const;

		GLFWwindow* GetGLFWWindow() const;

		bool IsResizable() const;

		bool IsFullScreen() const;

	protected:
		bool ReadConfig();

		bool InitGLFW();

		bool InitGLEW();

		bool InitViewport();

	private:
		uint32_t	m_nScreenHeight;
		uint32_t	m_nScreenWidth;
		uint32_t	m_nScreenX;
		uint32_t	m_nScreenY;
		std::string m_strWindowName;
		bool		m_bFullScreen;
		bool		m_bResizable;
		GLFWwindow* m_GLFWwindow;

		static const char* s_kConfigPath;
	};
}
#endif // GraphicsWindows_h__