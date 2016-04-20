#ifndef CMRGraphicsContext_h__
#define CMRGraphicsContext_h__
#include "CMRObject.h"
#include "CMROperationThread.h"
#include "SmartPtr.h"
namespace MR
{
	class CMRCamera;

	class CMRGraphicsContext : public CMRRef
	{
	public:
		struct Traits
		{
		public:
			Traits();
			Traits(bool bFullScreen, string strWindowName, int nWidth, int nHeight, int red, int green, int blue, int rate, GLFWmonitor* pMonitor);


		public:
			static Traits GetFullScreenTraits(string strName = "MonkeyRay");

			static Traits GetSpecifiedTraits(bool bScreen, string strWindowName, int nWidth, int nHeight);


		public:
			int				width;
			int				height;
			string			windowName;
			bool			fullScreen;
			int				rebBits;
			int				greenBits;
			int				blueBits;
			int				refreshRate;
			GLFWmonitor*	m_pMonitor;
		};

		typedef list< SmartPtr<CMROperation> > GraphicsOperationQueue;


	public:
		static CMRGraphicsContext* CreateDefaultGraphicsContext();

		void SwapBuffers();

		bool IsRealized() const;

		void Realize();

		void DestroyWindow();


	protected:
		CMRGraphicsContext() :m_traits(Traits::GetFullScreenTraits()){}
		CMRGraphicsContext(Traits traits);
		CMRGraphicsContext(const CMRGraphicsContext& rhs) = delete;
		CMRGraphicsContext& operator=(const CMRGraphicsContext& rhs) = delete;
		virtual ~CMRGraphicsContext();


	protected:
		bool m_bRealized;
		Traits m_traits;
		GLFWwindow* m_pWindow;
	};
}
#endif // CMRGraphicsContext_h__
