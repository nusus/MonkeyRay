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

			void Init();

			int GetWidth() const { return width; }
			void SetWidth(int val) { width = val; }

			int GetHeight() const { return height; }
			void SetHeight(int val) { height = val; }

			MR::string GetWindowName() const { return windowName; }
			void SetWindowName(MR::string val) { windowName = val; }

			bool GetFullScreen() const { return fullScreen; }
			void SetFullScreen(bool val) { fullScreen = val; }

			int GetRebBits() const { return rebBits; }
			void SetRebBits(int val) { rebBits = val; }

			int GetGreenBits() const { return greenBits; }
			void SetGreenBits(int val) { greenBits = val; }

			int GetBlueBits() const { return blueBits; }
			void SetBlueBits(int val) { blueBits = val; }

			int GetRefreshRate() const { return refreshRate; }
			void SetRefreshRate(int val) { refreshRate = val; }

			GLFWmonitor* GetMonitor() const { return m_pMonitor; }
			void SetMonitor(GLFWmonitor* val) { m_pMonitor = val; }


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
		static CMRGraphicsContext* Instance(bool bScreen, string strWindowName, int nWidth, int nHeight);

		void SwapBuffers();

		bool IsRealized() const;

		void Realize();

		void DestroyWindow();


	protected:
		CMRGraphicsContext() :m_traits(Traits::GetFullScreenTraits()), m_bRealized(false){}
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
