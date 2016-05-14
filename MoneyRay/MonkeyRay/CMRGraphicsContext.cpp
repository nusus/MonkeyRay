#include "CMRGraphicsContext.h"

using namespace MR;

CMRGraphicsContext* MR::CMRGraphicsContext::Instance(bool bScreen, string strWindowName, int nWidth, int nHeight)
{
	static CMRGraphicsContext context(CMRGraphicsContext::Traits::GetSpecifiedTraits(bScreen, strWindowName, nWidth, nHeight));
	return &context;
}

void MR::CMRGraphicsContext::SwapBuffers()
{
	glfwSwapBuffers(m_pWindow);
}

bool MR::CMRGraphicsContext::IsRealized() const
{
	return m_bRealized;
}

void MR::CMRGraphicsContext::Realize()
{
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

	GLenum err = glewInit();
	if (GLEW_OK != err)
	{
		std::cout << "Error initializing GLEW: " << glewGetErrorString(err) << std::endl;
		exit(EXIT_FAILURE);
	}

	m_bRealized = true;

	//TODO: event settings;
}

void MR::CMRGraphicsContext::DestroyWindow()
{
	glfwTerminate();
	m_pWindow = nullptr;
}

MR::CMRGraphicsContext::CMRGraphicsContext(Traits traits) :
	m_bRealized(false),
	m_traits(traits),
	m_pWindow(nullptr)
{

}

MR::CMRGraphicsContext::~CMRGraphicsContext()
{
	DestroyWindow();
}

MR::CMRGraphicsContext::Traits MR::CMRGraphicsContext::Traits::GetFullScreenTraits(string strName /*= "MonkeyRay"*/)
{
	Traits ret;
	ret.SetFullScreen(true);
	ret.SetWindowName(strName);
	return ret;
}

MR::CMRGraphicsContext::Traits MR::CMRGraphicsContext::Traits::GetSpecifiedTraits(bool bScreen, string strWindowName, int nWidth, int nHeight)
{
	Traits ret;
	if (!bScreen)
	{
		ret.SetMonitor(nullptr);
	}
	ret.SetFullScreen(bScreen);
	ret.SetWindowName(strWindowName);
	ret.SetWidth(nWidth);
	ret.SetHeight(nHeight);
	return ret;
}

void MR::CMRGraphicsContext::Traits::Init()
{
	if (!glfwInit())
	{
		CMR_STD_OUT << "glfw initialize failed" << CMR_STD_ENDL;
		return;
	}
	GLFWmonitor* monitor = glfwGetPrimaryMonitor();
	const GLFWvidmode* mode = glfwGetVideoMode(monitor);
	SetFullScreen(false);
	SetWindowName("MonkeyRay");
	SetWidth(mode->width);
	SetHeight(mode->height);
	SetRebBits(mode->redBits);
	SetGreenBits(mode->greenBits);
	SetBlueBits(mode->blueBits);
	SetRefreshRate(mode->refreshRate);
	SetMonitor(monitor);
}

MR::CMRGraphicsContext::Traits::Traits(bool bFullScreen, string strWindowName, int nWidth, int nHeight, int red, int green, int blue, int rate, GLFWmonitor* pMonitor) :
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

MR::CMRGraphicsContext::Traits::Traits() :
	windowName("MonkeyRay"),
	fullScreen(true)
{
	Init();
}
