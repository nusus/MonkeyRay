#ifndef CMRGraphicsWindow_h__
#define CMRGraphicsWindow_h__
#include "CMRPrerequisites.h"
namespace MR
{
	class CMRGraphicsWindow
	{
	public:
		CMRGraphicsWindow()
			:m_nScreenX(0),
			m_nScreenY(0),
			m_nWidth(640),
			m_nHeight(480),
			m_nFullScreen(false),
			m_strWindowName("MonkeyRay")
		{}

		CMRGraphicsWindow(int x, int y, int width, int height, bool bFullScreen, string windowName) :
			m_nScreenX(x),
			m_nScreenY(y),
			m_nWidth(width),
			m_nHeight(height),
			m_nFullScreen(bFullScreen),
			m_strWindowName(windowName)
		{}

	
	public:
		void SetScreenX(int x) { m_nScreenX = x; }
		const int GetScreenX() const { return m_nScreenX; }

		void SetScreenY(int y) { m_nScreenY = y; }
		const int GetScreenY() const { return m_nScreenY; }

		int GetWidth() const { return m_nWidth; }
		void SetWidth(int val) { m_nWidth = val; }

		int GetHeight() const { return m_nHeight; }
		void SetHeight(int val) { m_nHeight = val; }
		
		bool GetFullScreen() const { return m_nFullScreen; }
		void SetFullScreen(bool val) { m_nFullScreen = val; }
		
		MR::string GetWindowName() const { return m_strWindowName; }
		void SetWindowName(MR::string val) { m_strWindowName = val; }


	protected:		
		int m_nScreenX, m_nScreenY, m_nWidth, m_nHeight;
		bool m_nFullScreen;
		string m_strWindowName;
	};
}
#endif // CMRGraphicsWindow_h__
