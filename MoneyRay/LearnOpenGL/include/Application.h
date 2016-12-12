#pragma once
#ifndef Application_h__
#define Application_h__

#include "GraphicsWindows.h"
#include "event\EventManager.h"
#include "RenderManager.h"

namespace LOGL 
{
	class Application
	{
	public:
		Application();

		Application(const Application& rhs) = delete;
		Application& operator=(const Application& rhs) = delete;

		Application(Application&& rhs) = delete;
		Application& operator=(Application&& rhs) = delete;

		~Application();

	public:
		int Init();

		int Run();

		RenderManager& GetRenderManager();

	protected:
		void InitEvent();

		void InitGraphicsWindow();

		void InitRenderManager();

		void Update();

		void Render();
	protected:
		GraphicsWindows		m_GraphicsWindows;
		EventManager		m_EventManager;
		RenderManager		m_RenderManager;
	};
}
#endif // Application_h__