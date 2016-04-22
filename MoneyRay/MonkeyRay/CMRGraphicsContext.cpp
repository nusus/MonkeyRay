#include "CMRGraphicsContext.h"

using namespace MR;

CMRGraphicsContext* MR::CMRGraphicsContext::CreateDefaultGraphicsContext()
{
	static CMRGraphicsContext context(CMRGraphicsContext::Traits::GetFullScreenTraits());
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
	m_pWindow(false)
{

}

MR::CMRGraphicsContext::~CMRGraphicsContext()
{
	DestroyWindow();
}

MR::CMRGraphicsContext::Traits MR::CMRGraphicsContext::Traits::GetFullScreenTraits(string strName /*= "MonkeyRay"*/)
{
	GLFWmonitor* monitor = glfwGetPrimaryMonitor();
	const GLFWvidmode* mode = glfwGetVideoMode(monitor);
	return Traits(true, strName, mode->width, mode->height, mode->redBits, mode->greenBits, mode->blueBits, mode->refreshRate, monitor);
}

MR::CMRGraphicsContext::Traits MR::CMRGraphicsContext::Traits::GetSpecifiedTraits(bool bScreen, string strWindowName, int nWidth, int nHeight)
{
	GLFWmonitor* monitor = glfwGetPrimaryMonitor();
	const GLFWvidmode* mode = glfwGetVideoMode(monitor);
	GLFWmonitor* ret_monitor = bScreen ? monitor : nullptr;
	return Traits(bScreen, strWindowName, nWidth, nHeight, mode->redBits, mode->greenBits, mode->blueBits, mode->refreshRate, ret_monitor);
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
	GLFWmonitor* monitor = glfwGetPrimaryMonitor();
	const GLFWvidmode* mode = glfwGetVideoMode(monitor);
	width = mode->width;
	height = mode->height;
	rebBits = mode->redBits;
	greenBits = mode->greenBits;
	blueBits = mode->blueBits;
	refreshRate = mode->refreshRate;
	m_pMonitor = monitor;
}
