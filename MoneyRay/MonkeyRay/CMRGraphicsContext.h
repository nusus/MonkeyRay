#ifndef CMRGraphicsContext_h__
#define CMRGraphicsContext_h__
#include "CMRObject.h"
#include "..\Test\glfw3.h"
namespace MR
{
	class CMRCamera;

	class CMRGraphicsContext : public CMRObject
	{

	public:
		struct Traits
		{
			static Traits GetFullScreenTraits(string strName = "MonkeyRay")
			{
				GLFWmonitor* monitor = glfwGetPrimaryMonitor();
				const GLFWvidmode* mode = glfwGetVideoMode(monitor);
				return Traits(true, strName, mode->width, mode->height, mode->redBits, mode->greenBits, mode->blueBits, mode->refreshRate, monitor);
			}
			static Traits GetSpecifiedTraits(bool bScreen, string strWindowName, int nWidth, int nHeight)
			{
				GLFWmonitor* monitor = glfwGetPrimaryMonitor();
				const GLFWvidmode* mode = glfwGetVideoMode(monitor);
				GLFWmonitor* ret_monitor = bScreen ? monitor : nullptr;
				return Traits(bScreen, strWindowName, nWidth, nHeight, mode->redBits, mode->greenBits, mode->blueBits, mode->refreshRate, ret_monitor);
			}

			int width;
			int height;

			string		windowName;
			bool        fullScreen;

			int rebBits;
			int greenBits;
			int blueBits;
			int refreshRate;

			GLFWmonitor* m_pMonitor;
		protected:
			Traits(bool bFullScreen, string strWindowName, int nWidth, int nHeight, int red, int green, int blue, int rate, GLFWmonitor* pMonitor):
				width(nWidth),
				height(nHeight),
				windowName(strWindowName),
				fullScreen(bFullScreen),
				rebBits(red),
				greenBits(green),
				blueBits(blue),
				refreshRate(rate),
				m_pMonitor(pMonitor)
			{
			}
		};


		typedef list< SmartPtr<CMROperation> > GraphicsOperationQueue;
	public:
		static CMRGraphicsContext* CreateDefaultGraphicsContext()
		{
			static CMRGraphicsContext context(Traits::GetFullScreenTraits());
			return &context;
		}


	public:
		void RunOperations()
		{
			//TODO:  is not implemented
			throw std::logic_error("The method or operation is not implemented.");
		}

		void SwapBuffers()
		{
			glfwSwapBuffers(m_pWindow);
		}

			bool IsRealized() const
		{
			return m_bRealized;
		}

			CMRState* GetState() const
			{
				//TODO: CMRGraphicsContext is not implemented
				throw std::logic_error("The method or operation is not implemented.");
			}

			void Realize()
			{
				if (!glfwInit())
				{
					m_bRealized = false;
					return;
				}
				glfwWindowHint(GLFW_RED_BITS, m_traits.rebBits);
				glfwWindowHint(GLFW_GREEN_BITS, m_traits.greenBits);
				glfwWindowHint(GLFW_BLUE_BITS, m_traits.blueBits);
				glfwWindowHint(GLFW_REFRESH_RATE, m_traits.refreshRate);
				m_pWindow = glfwCreateWindow(m_traits.width, m_traits.height, m_traits.windowName.c_str(), m_traits.m_pMonitor, NULL);
				if (!m_pWindow)
				{
					m_bRealized = false;
					DestroyWindow();
					return;
				}

				glfwMakeContextCurrent(m_pWindow);

				//event settings;
			}

			CMRNode* GetSceneData()
			{
				//TODO: CMRGraphicsContext is not implemented
				throw std::logic_error("The method or operation is not implemented.");
			}

			void DestroyWindow()
			{
				glfwTerminate();
				m_pWindow = nullptr;
			}
			virtual const char* ClassName() const override
			{
				return "CMRGraphicsContext";
			}

	protected:
		CMRGraphicsContext(Traits traits) :
			m_bRealized(false),
			m_traits(traits),
			m_pWindow(false)
		{

		}

		~CMRGraphicsContext() 
		{
			DestroyWindow();
		}



		virtual CMRObject* Clone() const override
		{
			return NULL;
		}

		virtual CMRObject* Copy(const CMRCopyPolicy& policy) const override
		{
			return NULL;
		}

	protected:
		bool m_bRealized;
		Traits m_traits;
		GLFWwindow* m_pWindow;

		GraphicsOperationQueue m_operations;
		SmartPtr<CMROperation> m_currentOperation;
	};
}
#endif // CMRGraphicsContext_h__
