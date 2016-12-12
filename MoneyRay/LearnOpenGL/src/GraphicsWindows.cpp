#include "GraphicsWindows.h"
#include "config\ConfigParser.h"


const char* LOGL::GraphicsWindows::s_kConfigPath = "config/GraphicsWindowsConfig.xml";

int LOGL::GraphicsWindows::Init()
{
	ReadConfig();
	InitGLFW();
	InitGLEW();
	InitViewport();
	return 0;
}

int LOGL::GraphicsWindows::DestroyGraphicsWindow()
{
	glfwTerminate();
	return 0;
}

uint32_t LOGL::GraphicsWindows::GetScreenHeight() const
{
	return m_nScreenHeight;
}

uint32_t LOGL::GraphicsWindows::GetScreenWidth() const
{
	return m_nScreenWidth;
}

uint32_t LOGL::GraphicsWindows::GetScreenX() const
{
	return m_nScreenX;
}

uint32_t LOGL::GraphicsWindows::GetScreenY() const
{
	return m_nScreenY;
}

std::string LOGL::GraphicsWindows::GetWindowName() const
{
	return m_strWindowName;
}

GLFWwindow* LOGL::GraphicsWindows::GetGLFWWindow() const
{
	return m_GLFWwindow;
}

bool LOGL::GraphicsWindows::IsResizable() const
{
	return m_bResizable;
}

bool LOGL::GraphicsWindows::IsFullScreen() const
{
	return m_bFullScreen;
}

bool LOGL::GraphicsWindows::ReadConfig()
{
	ConfigParser config;
	config.ReadConfig(s_kConfigPath);
	ConfigParser& parser = config.GetGroup("window");
	m_nScreenHeight = parser.GetValueByKey<int>("screenHeight");
	m_nScreenWidth = parser.GetValueByKey<int>("screenWidth");
	m_nScreenX = parser.GetValueByKey<int>("screenX");
	m_nScreenY = parser.GetValueByKey<int>("screenY");
	m_bFullScreen = parser.GetValueByKey<bool>("fullScreen");
	m_bResizable = parser.GetValueByKey<bool>("resizable");
	m_strWindowName = parser.GetValueByKey<std::string>("windowName");

	return true;
}

bool LOGL::GraphicsWindows::InitGLFW()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, IsResizable());

	GLFWwindow* window = glfwCreateWindow(GetScreenWidth(), GetScreenHeight(), GetWindowName().c_str(), nullptr, nullptr);
	if (window == nullptr)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return false;
	}
	glfwMakeContextCurrent(window);
	m_GLFWwindow  = window;
	return true;
}

bool LOGL::GraphicsWindows::InitGLEW()
{
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)
	{
		std::cout << "Failed to initialize GLEW" << std::endl;
		return false;
	}
	return true;
}

bool LOGL::GraphicsWindows::InitViewport()
{
	int width, height;
	glfwGetFramebufferSize(m_GLFWwindow, &width, &height);
	glViewport(GetScreenX(), GetScreenY(), width, height);
	return true;
}

