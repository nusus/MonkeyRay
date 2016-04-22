#ifndef CMRApplication_h__
#define CMRApplication_h__
#include <glfw3.h>
#include "CMRProgram.h"
#include "CMRCamera.h"
namespace MR
{
	class CMRApplication
	{
	public:
		struct WindowInfo 
		{
			WindowInfo(unsigned int width, unsigned int height, const std::string& strTitle):
				windowWidth(width),
				windowHeight(height),
				windowTitle(strTitle)
			{}
			unsigned int windowWidth;
			unsigned int windowHeight;
			std::string windowTitle;
		};

	public:
		CMRApplication()
			:m_pWindow(nullptr),
			m_pCamera(new CMRCamera()),
			m_pProgram(new CMRProgram()),
			m_uiFrameNumber(0),
			m_windowInfo(640, 480, "Hello World")
		{
		}

		~CMRApplication()
		{
			Clear();
			if (m_pCamera)
			{
				delete m_pCamera;
				m_pCamera = nullptr;
			}
			if (m_pProgram)
			{
				delete m_pProgram;
				m_pProgram = nullptr;
			}
			glfwTerminate();
		}

		void Clear()
		{
			for (CMRMesh* pMesh : m_pMesh)
			{
				if (pMesh)
				{
					delete pMesh;
					pMesh = nullptr;
				}
			}
		}

		void SetWindowInfo(const WindowInfo& info)
		{
			m_windowInfo = info;
		}

		virtual bool Init()
		{
			/* Initialize the library */
			if (!glfwInit())
				return false;
			GLFWmonitor* monitor = glfwGetPrimaryMonitor();
			const GLFWvidmode* mode = glfwGetVideoMode(monitor);

			/* Create a windowed mode window and its OpenGL context */
			m_pWindow = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
			if (!m_pWindow)
			{

				glfwTerminate();
				return false;
			}
			/* Make the window's context current */
			glfwMakeContextCurrent(m_pWindow);

			//≥ı ºªØglew¿©’πø‚  
			GLenum err = glewInit();
			if (GLEW_OK != err)
			{
				std::cout << "Error initializing GLEW: " << glewGetErrorString(err) << std::endl;
				exit(EXIT_FAILURE);
			}

			m_pCamera->Init();

			InitShader();
			InitTexture();

			InitView();
			InitRenderInfo();
			glClearColor(0.0, 0.0, 0.0, 0.0);
			return true;
		}

		virtual void InitShader()
		{
			MR::CMRShader* vertexShader = new MR::CMRShader(MR::CMRShader::VERTEX, "test1.vs");
			MR::CMRShader* fragmentShader = new MR::CMRShader(MR::CMRShader::FRAGMENT, "test1.fs");
			m_pProgram->AddShader(vertexShader);
			m_pProgram->AddShader(fragmentShader);
			m_pProgram->InitProgram();
			if (m_pProgram->IsReady())
			{
				m_pProgram->UseProgram();
			}
		}

		virtual void InitTexture()
		{
			m_pProgram->Uniformli("tex_object", 0);
		}

		virtual void InitView()
		{
			m_pCamera->SetProjectionMatrix(60.0f, m_windowInfo.windowWidth, m_windowInfo.windowHeight, 0.1f, 1000.0f);

			vmath::vecN<float, 3> eye;
			eye[0] = 0.0f;
			eye[1] = 0.0f;
			eye[2] = 10.0f;

			vmath::vecN<float, 3> center;
			center[0] = 0.0f;
			center[1] = 0.0f;
			center[2] = 0.0f;

			vmath::vecN<float, 3> up;
			up[0] = 0.0f;
			up[1] = 1.0f;
			up[2] = 0.0f;
			m_pCamera->LookAt(eye, center, up);

			m_pProgram->UseProgram();
			m_pProgram->UniformMatrix4fv("uni_model_view_matrix", m_pCamera->GetModelViewMatrix() * vmath::translate(vmath::vec3(0.0f, 0.0f, -10.0f)) * vmath::rotate(90.0f, vmath::vec3(1.0f, 0.0f, 0.0f)));
			m_pProgram->UniformMatrix4fv("uni_projection_matrix", m_pCamera->GetProjectionMatrix());
		}

		virtual void InitRenderInfo()
		{
			for (CMRMesh* pMesh : m_pMesh)
			{
				if (pMesh)
				{
					pMesh->LoadMesh();
				}
			}
		}

		void AddMesh(CMRMesh* pMesh)
		{
			m_pMesh.push_back(pMesh);
		}

		virtual void Frame()
		{
			/* Loop until the user closes the window */
			while (!glfwWindowShouldClose(m_pWindow))
			{
				Update();
				/* Render here */
				Render();

				/* Swap front and back buffers */
				glfwSwapBuffers(m_pWindow);

				/* Poll for and process events */
				glfwPollEvents();
			}

		}

		void Render()
		{
			m_pProgram->UseProgram();
			for (auto pMesh : m_pMesh)
			{
				if (pMesh)
				{
					pMesh->Render();
				}
			}
		}

		virtual void Update()
		{
			m_uiFrameNumber += 1;
			m_pCamera->Update(m_uiFrameNumber);

			//m_pProgram->UniformMatrix4fv("uni_model_view_matrix", m_pCamera->GetModelViewMatrix());
		}

		virtual int Run()
		{
			if (Init())
			{
				Frame();
				return EXIT_SUCCESS;
			}
			else
			{
				exit(EXIT_FAILURE);
				return EXIT_FAILURE;
			}
		}

	protected:
		GLFWwindow* m_pWindow;
		CMRCamera*  m_pCamera;
		CMRProgram* m_pProgram;
		unsigned int m_uiFrameNumber;
		WindowInfo m_windowInfo;
		std::vector<CMRMesh*> m_pMesh;
	private:
	};
}
#endif // CMRApplication_h__
