#pragma once
#ifndef RenderJob_h__
#define RenderJob_h__

#include <functional>

namespace LOGL
{
	class RenderJob
	{
	public:
		typedef std::function<void(void)> Callback;
	public:
		RenderJob(Callback renderCallback)
			:m_InitCallback([]() {}),
			m_RenderCallback(renderCallback)
		{

		}

		RenderJob(Callback initCallback, Callback renderCallback)
			:m_InitCallback(initCallback),
			m_RenderCallback(renderCallback)
		{

		}

		void Init()
		{
			m_InitCallback();
		}

		void Render()
		{
			m_RenderCallback();
		}

	protected:
		Callback m_InitCallback;
		Callback m_RenderCallback;
	private:
	};
}
#endif // RenderJob_h__