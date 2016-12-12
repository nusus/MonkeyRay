#pragma once
#ifndef RenderManager_h__
#define RenderManager_h__

#include <list>
#include "RenderJob.h"

namespace LOGL
{
	class RenderManager
	{
	public:
		void Init()
		{
			for (auto& job: m_RenderJobList)
			{
				job.Init();
			}
		}

		void AddRenderJob(const RenderJob& job)
		{
			m_RenderJobList.push_back(job);
		}

		void Render()
		{
			for (auto& job: m_RenderJobList)
			{
				job.Render();
			}
		}

	protected:
		std::list<RenderJob> m_RenderJobList;

	private:
	};
}
#endif // RenderManager_h__