#include "CMRGUIEventAdapter.h"

using namespace MR;

CMRGUIEventAdapter::CMRGUIEventAdapter() :
	m_eventType(NONE),
	m_windowX(0),
	m_windowY(0),
	m_windowWidth(1280),
	m_windowHeight(1024),
	m_key(0),
	m_unmodifiedKey(0),
	m_button(0),
	m_Xmin(-1.0),
	m_Xmax(1.0),
	m_Ymin(-1.0),
	m_Ymax(1.0),
	m_mx(0.0),
	m_my(0.0),
	m_buttonMask(0),
	m_modKeyMask(0),
	m_mouseYOrientation(Y_INCREASING_DOWNWARDS),
	m_scrolling()
{}


MR::CMRGUIEventAdapter::CMRGUIEventAdapter(const CMRGUIEventAdapter & rhs, const CMRCopyPolicy & copyop):
	    m_eventType(rhs.m_eventType),
		//m_context(rhs.m_context),
		m_windowX(rhs.m_windowX),
		m_windowY(rhs.m_windowY),
		m_windowWidth(rhs.m_windowWidth),
		m_windowHeight(rhs.m_windowHeight),
		m_key(rhs.m_key),
		m_unmodifiedKey(rhs.m_unmodifiedKey),
		m_button(rhs.m_button),
		m_Xmin(rhs.m_Xmin),
		m_Xmax(rhs.m_Xmax),
		m_Ymin(rhs.m_Ymin),
		m_Ymax(rhs.m_Ymax),
		m_mx(rhs.m_mx),
		m_my(rhs.m_my),
		m_buttonMask(rhs.m_buttonMask),
		m_modKeyMask(rhs.m_modKeyMask),
		m_mouseYOrientation(rhs.m_mouseYOrientation),
		m_scrolling(rhs.m_scrolling)
{}

SmartPtr<CMRGUIEventAdapter>& MR::CMRGUIEventAdapter::GetAccumulatedEventState()
{
	static SmartPtr<CMRGUIEventAdapter> s_eventState = new CMRGUIEventAdapter;
	return s_eventState;
}



void MR::CMRGUIEventAdapter::SetWindowRectangle(int x, int y, int width, int height, bool updateMouseRange)
{
	m_windowX = x;
	m_windowY = y;
	m_windowWidth = width;
	m_windowHeight = height;

	if (updateMouseRange)
	{
		SetInputRange(0, 0, width, height);
	}
}

void MR::CMRGUIEventAdapter::SetInputRange(float Xmin, float Ymin, float Xmax, float Ymax)
{
	m_Xmin = Xmin;
	m_Ymin = Ymin;
	m_Xmax = Xmax;
	m_Ymax = Ymax;
}

MR::CMRGUIEventAdapter::~CMRGUIEventAdapter()
{
}

