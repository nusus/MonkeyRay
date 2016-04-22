#ifndef CMRRenderInfo_h__
#define CMRRenderInfo_h__

#include "CMRView.h"
#include "CMRRenderBin.h"
#include "CMRState.h"

namespace MR
{
	class CMRRenderInfo
	{
	public:
		typedef vector<CMRRenderBin*> RenderBinStack;

	public:
		CMRRenderInfo() :
			m_pView(nullptr)
		{

		}
		
		CMRRenderInfo(const CMRRenderInfo& rhs)
			:m_spState(rhs.m_spState),
			m_pView(rhs.m_pView),
			m_renderBinStack(rhs.m_renderBinStack)

		{

		}

		CMRRenderInfo(CMRState* pState, CMRView* pView):
			m_spState(pState),
			m_pView(pView)
		{

		}

		CMRRenderInfo& operator=(const CMRRenderInfo& rhs)
		{
			if (this == &rhs)
			{
				return *this;
			}
			m_spState = rhs.m_spState;
			m_pView = rhs.m_pView;
			m_renderBinStack = rhs.m_renderBinStack;
			return *this;
		}

		void SetState(CMRState* pState)
		{
			m_spState = pState;
		}

		CMRState* GetState()
		{
			return m_spState.Get();
		}

		const CMRState* GetState() const
		{
			return m_spState.Get();
		}
			

		void SetView(CMRView* pView)
		{
			m_pView = pView;
		}

		CMRView* GetView()
		{
			return m_pView;
		}

		const CMRView* GetView() const
		{
			return m_pView;
		}

		void PushRenderBin(CMRRenderBin* pRenderBin)
		{
			m_renderBinStack.push_back(pRenderBin);
		}

		void PopRenderBin()
		{
			m_renderBinStack.pop_back();
		}

		RenderBinStack& GetRenderBinStack() { return m_renderBinStack; }
	protected:
		SmartPtr<CMRState> m_spState;
		CMRView* m_pView;
		RenderBinStack m_renderBinStack;
	};
}

#endif // CMRRenderInfo_h__
