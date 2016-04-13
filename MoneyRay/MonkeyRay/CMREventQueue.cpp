#include "CMREventQueue.h"
#include "CMRGUIEventAdapter.h"

using namespace MR;

MR::CMREventQueue::CMREventQueue(CMRGUIEventAdapter::MouseYOrientation mouseYOrientation)
{
	m_useFixedMouseInputRange = false;

	m_startTick = osg::Timer::instance()->GetStartTick();

	m_accumulateEventState = new CMRGUIEventAdapter();
	m_accumulateEventState->SetMouseYOrientation(mouseYOrientation);

	m_firstTouchEmulatesMouse = true;
}

void MR::CMREventQueue::SetEvents(Events & events)
{
	OpenThreads::ScopedLock<OpenThreads::Mutex> lock(m_eventQueueMutex);
	m_eventQueue = events;
}

bool MR::CMREventQueue::TakeEvents(Events & events)
{
	OpenThreads::ScopedLock<OpenThreads::Mutex> lock(m_eventQueueMutex);
	if (!m_eventQueue.empty())
	{
		events.splice(events.end(), m_eventQueue);
		return true;
	}
	else
	{
		return false;
	}
}

bool MR::CMREventQueue::TakeEvents(Events & events, double cutOffTime)
{
	OpenThreads::ScopedLock<OpenThreads::Mutex> lock(m_eventQueueMutex);
	if (!m_eventQueue.empty())
	{
		Events::reverse_iterator ritr = m_eventQueue.rbegin();
		for (; ritr != m_eventQueue.rend() && ((*ritr)->GetTime() > cutOffTime); ++ritr) {}

		if (ritr == m_eventQueue.rend()) return false;

		for (Events::iterator itr = m_eventQueue.begin();
		itr != ritr.base();
			++itr)
		{
			events.push_back(*itr);
		}

		double previousTime = cutOffTime;
		for (Events::reverse_iterator itr = events.rbegin();
		itr != events.rend();
			++itr)
		{
			if ((*itr)->GetTime() > previousTime)
			{
				//OSG_INFO << "Reset event time from " << (*itr)->GetTime() << " to " << previousTime << std::endl;
				(*itr)->SetTime(previousTime);
			}
			else
			{
				previousTime = (*itr)->GetTime();
			}
		}

		m_eventQueue.erase(m_eventQueue.begin(), ritr.base());

		return true;
	}
	else
	{
		return false;
	}
}

bool MR::CMREventQueue::CopyEvents(Events & events) const
{
	OpenThreads::ScopedLock<OpenThreads::Mutex> lock(m_eventQueueMutex);
	if (!m_eventQueue.empty())
	{
		events.insert(events.end(), m_eventQueue.begin(),m_eventQueue.end());
		return true;
	}
	else
	{
		return false;
	}
}

void MR::CMREventQueue::AppendEvents(Events & events)
{
	OpenThreads::ScopedLock<OpenThreads::Mutex> lock(m_eventQueueMutex);
	m_eventQueue.insert(m_eventQueue.end(), events.begin(), events.end());
}

void MR::CMREventQueue::AddEvent(CMREvent * event)
{
	OpenThreads::ScopedLock<OpenThreads::Mutex> lock(m_eventQueueMutex);
	m_eventQueue.push_back(event);
}

void MR::CMREventQueue::SyncWindowRectangleWithGraphicsContext()
{
	const osg::GraphicsContext::Traits* traits = (GetGraphicsContext() != 0) ? GetGraphicsContext()->GetTraits() : 0;
	if (traits) m_accumulateEventState->SetWindowRectangle(traits->x, traits->y, traits->width, traits->height, !m_useFixedMouseInputRange);
}

CMRGUIEventAdapter * MR::CMREventQueue::WindowResize(int x, int y, int width, int height, double time)
{
	m_accumulateEventState->SetWindowRectangle(x, y, width, height, !m_useFixedMouseInputRange);

	CMRGUIEventAdapter* event = new CMRGUIEventAdapter(*m_accumulateEventState);
	event->SetEventType(CMRGUIEventAdapter::RESIZE);
	event->SetTime(time);

	AddEvent(event);

	return event;
}

CMRGUIEventAdapter * MR::CMREventQueue::MouseScroll(CMRGUIEventAdapter::ScrollingMotion sm, double time)
{
	CMRGUIEventAdapter* event = new CMRGUIEventAdapter(*m_accumulateEventState);
	event->SetEventType(CMRGUIEventAdapter::SCROLL);
	event->SetScrollingMotion(sm);
	event->SetTime(time);

	AddEvent(event);

	return event;
}

CMRGUIEventAdapter * MR::CMREventQueue::MouseScroll2D(float x, float y, double time)
{
	return nullptr;
}

void MR::CMREventQueue::MouseWarped(float x, float y)
{
	m_accumulateEventState->SetX(x);
	m_accumulateEventState->SetY(y);
}

CMRGUIEventAdapter * MR::CMREventQueue::MouseMotion(float x, float y, double time)
{
	m_accumulateEventState->SetX(x);
	m_accumulateEventState->SetY(y);

	CMRGUIEventAdapter* event = new CMRGUIEventAdapter(*m_accumulateEventState);
	event->SetEventType(event->GetButtonMask() ? CMRGUIEventAdapter::DRAG : CMRGUIEventAdapter::MOVE);
	event->SetTime(time);

	AddEvent(event);

	return event;
}

CMRGUIEventAdapter * MR::CMREventQueue::MouseButtonPress(float x, float y, unsigned int button, double time)
{
	m_accumulateEventState->SetX(x);
	m_accumulateEventState->SetY(y);

	switch (button)
	{
	case(1) :
		m_accumulateEventState->SetButtonMask(CMRGUIEventAdapter::LEFT_MOUSE_BUTTON | m_accumulateEventState->GetButtonMask());
		break;
	case(2) :
		m_accumulateEventState->SetButtonMask(CMRGUIEventAdapter::MIDDLE_MOUSE_BUTTON | m_accumulateEventState->GetButtonMask());
		break;
	case(3) :
		m_accumulateEventState->SetButtonMask(CMRGUIEventAdapter::RIGHT_MOUSE_BUTTON | m_accumulateEventState->GetButtonMask());
		break;
	}

	CMRGUIEventAdapter* event = new CMRGUIEventAdapter(*m_accumulateEventState);
	event->SetEventType(CMRGUIEventAdapter::PUSH);
	event->SetTime(time);

	switch (button)
	{
	case(1) :
		event->SetButton(CMRGUIEventAdapter::LEFT_MOUSE_BUTTON);
		break;
	case(2) :
		event->SetButton(CMRGUIEventAdapter::MIDDLE_MOUSE_BUTTON);
		break;
	case(3) :
		event->SetButton(CMRGUIEventAdapter::RIGHT_MOUSE_BUTTON);
		break;
	}

	AddEvent(event);

	return event;
}

CMRGUIEventAdapter * MR::CMREventQueue::MouseDoubleButtonPress(float x, float y, unsigned int button, double time)
{
	m_accumulateEventState->SetX(x);
	m_accumulateEventState->SetY(y);

	switch (button)
	{
	case(1) :
		m_accumulateEventState->SetButtonMask(CMRGUIEventAdapter::LEFT_MOUSE_BUTTON | m_accumulateEventState->GetButtonMask());
		break;
	case(2) :
		m_accumulateEventState->SetButtonMask(CMRGUIEventAdapter::MIDDLE_MOUSE_BUTTON | m_accumulateEventState->GetButtonMask());
		break;
	case(3) :
		m_accumulateEventState->SetButtonMask(CMRGUIEventAdapter::RIGHT_MOUSE_BUTTON | m_accumulateEventState->GetButtonMask());
		break;
	}

	CMRGUIEventAdapter* event = new CMRGUIEventAdapter(*m_accumulateEventState);
	event->SetEventType(CMRGUIEventAdapter::DOUBLECLICK);
	event->SetTime(time);

	switch (button)
	{
	case(1) :
		event->SetButton(CMRGUIEventAdapter::LEFT_MOUSE_BUTTON);
		break;
	case(2) :
		event->SetButton(CMRGUIEventAdapter::MIDDLE_MOUSE_BUTTON);
		break;
	case(3) :
		event->SetButton(CMRGUIEventAdapter::RIGHT_MOUSE_BUTTON);
		break;
	}

	AddEvent(event);

	return event;
}

CMRGUIEventAdapter * MR::CMREventQueue::MouseButtonRelease(float x, float y, unsigned int button, double time)
{
	m_accumulateEventState->SetX(x);
	m_accumulateEventState->SetY(y);

	switch (button)
	{
	case(1) :
		m_accumulateEventState->SetButtonMask(~CMRGUIEventAdapter::LEFT_MOUSE_BUTTON & m_accumulateEventState->GetButtonMask());
		break;
	case(2) :
		m_accumulateEventState->SetButtonMask(~CMRGUIEventAdapter::MIDDLE_MOUSE_BUTTON & m_accumulateEventState->GetButtonMask());
		break;
	case(3) :
		m_accumulateEventState->SetButtonMask(~CMRGUIEventAdapter::RIGHT_MOUSE_BUTTON & m_accumulateEventState->GetButtonMask());
		break;
	}

	CMRGUIEventAdapter* event = new CMRGUIEventAdapter(*m_accumulateEventState);
	event->SetEventType(CMRGUIEventAdapter::RELEASE);
	event->SetTime(time);

	switch (button)
	{
	case(1) :
		event->SetButton(CMRGUIEventAdapter::LEFT_MOUSE_BUTTON);
		break;
	case(2) :
		event->SetButton(CMRGUIEventAdapter::MIDDLE_MOUSE_BUTTON);
		break;
	case(3) :
		event->SetButton(CMRGUIEventAdapter::RIGHT_MOUSE_BUTTON);
		break;
	}

	AddEvent(event);

	return event;
}

CMRGUIEventAdapter * MR::CMREventQueue::KeyPress(int key, double time, int unmodifiedKey)
{
	switch (key)
	{
	case(CMRGUIEventAdapter::KEY_Shift_L) : m_accumulateEventState->SetModKeyMask(CMRGUIEventAdapter::MODKEY_LEFT_SHIFT | m_accumulateEventState->GetModKeyMask()); break;
	case(CMRGUIEventAdapter::KEY_Shift_R) : m_accumulateEventState->SetModKeyMask(CMRGUIEventAdapter::MODKEY_RIGHT_SHIFT | m_accumulateEventState->GetModKeyMask()); break;
	case(CMRGUIEventAdapter::KEY_Control_L) : m_accumulateEventState->SetModKeyMask(CMRGUIEventAdapter::MODKEY_LEFT_CTRL | m_accumulateEventState->GetModKeyMask()); break;
	case(CMRGUIEventAdapter::KEY_Control_R) : m_accumulateEventState->SetModKeyMask(CMRGUIEventAdapter::MODKEY_RIGHT_CTRL | m_accumulateEventState->GetModKeyMask()); break;
	case(CMRGUIEventAdapter::KEY_Meta_L) : m_accumulateEventState->SetModKeyMask(CMRGUIEventAdapter::MODKEY_LEFT_META | m_accumulateEventState->GetModKeyMask()); break;
	case(CMRGUIEventAdapter::KEY_Meta_R) : m_accumulateEventState->SetModKeyMask(CMRGUIEventAdapter::MODKEY_RIGHT_META | m_accumulateEventState->GetModKeyMask()); break;
	case(CMRGUIEventAdapter::KEY_Alt_L) : m_accumulateEventState->SetModKeyMask(CMRGUIEventAdapter::MODKEY_LEFT_ALT | m_accumulateEventState->GetModKeyMask()); break;
	case(CMRGUIEventAdapter::KEY_Alt_R) : m_accumulateEventState->SetModKeyMask(CMRGUIEventAdapter::MODKEY_RIGHT_ALT | m_accumulateEventState->GetModKeyMask()); break;
	case(CMRGUIEventAdapter::KEY_Super_L) : m_accumulateEventState->SetModKeyMask(CMRGUIEventAdapter::MODKEY_LEFT_SUPER | m_accumulateEventState->GetModKeyMask()); break;
	case(CMRGUIEventAdapter::KEY_Super_R) : m_accumulateEventState->SetModKeyMask(CMRGUIEventAdapter::MODKEY_RIGHT_SUPER | m_accumulateEventState->GetModKeyMask()); break;
	case(CMRGUIEventAdapter::KEY_Hyper_L) : m_accumulateEventState->SetModKeyMask(CMRGUIEventAdapter::MODKEY_LEFT_HYPER | m_accumulateEventState->GetModKeyMask()); break;
	case(CMRGUIEventAdapter::KEY_Hyper_R) : m_accumulateEventState->SetModKeyMask(CMRGUIEventAdapter::MODKEY_RIGHT_HYPER | m_accumulateEventState->GetModKeyMask()); break;
	case(CMRGUIEventAdapter::KEY_Caps_Lock) :
	{
		if ((m_accumulateEventState->GetModKeyMask() & CMRGUIEventAdapter::MODKEY_CAPS_LOCK) != 0)
			m_accumulateEventState->SetModKeyMask(~CMRGUIEventAdapter::MODKEY_CAPS_LOCK & m_accumulateEventState->GetModKeyMask());
		else
			m_accumulateEventState->SetModKeyMask(CMRGUIEventAdapter::MODKEY_CAPS_LOCK | m_accumulateEventState->GetModKeyMask());
		break;
	}
	case(CMRGUIEventAdapter::KEY_Num_Lock) :
	{
		if ((m_accumulateEventState->GetModKeyMask() & CMRGUIEventAdapter::MODKEY_NUM_LOCK) != 0)
			m_accumulateEventState->SetModKeyMask(~CMRGUIEventAdapter::MODKEY_NUM_LOCK & m_accumulateEventState->GetModKeyMask());
		else
			m_accumulateEventState->SetModKeyMask(CMRGUIEventAdapter::MODKEY_NUM_LOCK | m_accumulateEventState->GetModKeyMask());
		break;
	}
	default: break;
	}

	CMRGUIEventAdapter* event = new CMRGUIEventAdapter(*m_accumulateEventState);
	event->SetEventType(CMRGUIEventAdapter::KEYDOWN);
	event->SetKey(key);
	event->SetUnmodifiedKey(unmodifiedKey);
	event->SetTime(time);

	AddEvent(event);

	return event;
}

CMRGUIEventAdapter * MR::CMREventQueue::KeyRelease(int key, double time, int unmodifiedKey)
{
	switch (key)
	{
	case(CMRGUIEventAdapter::KEY_Shift_L) : m_accumulateEventState->SetModKeyMask(~CMRGUIEventAdapter::MODKEY_LEFT_SHIFT & m_accumulateEventState->GetModKeyMask()); break;
	case(CMRGUIEventAdapter::KEY_Shift_R) : m_accumulateEventState->SetModKeyMask(~CMRGUIEventAdapter::MODKEY_RIGHT_SHIFT & m_accumulateEventState->GetModKeyMask()); break;
	case(CMRGUIEventAdapter::KEY_Control_L) : m_accumulateEventState->SetModKeyMask(~CMRGUIEventAdapter::MODKEY_LEFT_CTRL & m_accumulateEventState->GetModKeyMask()); break;
	case(CMRGUIEventAdapter::KEY_Control_R) : m_accumulateEventState->SetModKeyMask(~CMRGUIEventAdapter::MODKEY_RIGHT_CTRL & m_accumulateEventState->GetModKeyMask()); break;
	case(CMRGUIEventAdapter::KEY_Meta_L) : m_accumulateEventState->SetModKeyMask(~CMRGUIEventAdapter::MODKEY_LEFT_META & m_accumulateEventState->GetModKeyMask()); break;
	case(CMRGUIEventAdapter::KEY_Meta_R) : m_accumulateEventState->SetModKeyMask(~CMRGUIEventAdapter::MODKEY_RIGHT_META & m_accumulateEventState->GetModKeyMask()); break;
	case(CMRGUIEventAdapter::KEY_Alt_L) : m_accumulateEventState->SetModKeyMask(~CMRGUIEventAdapter::MODKEY_LEFT_ALT & m_accumulateEventState->GetModKeyMask()); break;
	case(CMRGUIEventAdapter::KEY_Alt_R) : m_accumulateEventState->SetModKeyMask(~CMRGUIEventAdapter::MODKEY_RIGHT_ALT & m_accumulateEventState->GetModKeyMask()); break;
	case(CMRGUIEventAdapter::KEY_Super_L) : m_accumulateEventState->SetModKeyMask(~CMRGUIEventAdapter::MODKEY_LEFT_SUPER & m_accumulateEventState->GetModKeyMask()); break;
	case(CMRGUIEventAdapter::KEY_Super_R) : m_accumulateEventState->SetModKeyMask(~CMRGUIEventAdapter::MODKEY_RIGHT_SUPER & m_accumulateEventState->GetModKeyMask()); break;
	case(CMRGUIEventAdapter::KEY_Hyper_L) : m_accumulateEventState->SetModKeyMask(~CMRGUIEventAdapter::MODKEY_LEFT_HYPER & m_accumulateEventState->GetModKeyMask()); break;
	case(CMRGUIEventAdapter::KEY_Hyper_R) : m_accumulateEventState->SetModKeyMask(~CMRGUIEventAdapter::MODKEY_RIGHT_HYPER & m_accumulateEventState->GetModKeyMask()); break;
	default: break;
	}

	CMRGUIEventAdapter* event = new CMRGUIEventAdapter(*m_accumulateEventState);
	event->SetEventType(CMRGUIEventAdapter::KEYUP);
	event->SetKey(key);
	event->SetUnmodifiedKey(unmodifiedKey);
	event->SetTime(time);

	AddEvent(event);

	return event;
}

CMRGUIEventAdapter * MR::CMREventQueue::CloseWindow(double time)
{
	CMRGUIEventAdapter* event = new CMRGUIEventAdapter(*m_accumulateEventState);
	event->SetEventType(CMRGUIEventAdapter::CLOSE_WINDOW);
	event->SetTime(time);

	AddEvent(event);

	return event;
}

CMRGUIEventAdapter * MR::CMREventQueue::QuitApplication(double time)
{
	CMRGUIEventAdapter* event = new CMRGUIEventAdapter(*m_accumulateEventState);
	event->SetEventType(CMRGUIEventAdapter::QUIT_APPLICATION);
	event->SetTime(time);

	AddEvent(event);

	return event;
}

CMRGUIEventAdapter * MR::CMREventQueue::Frame(double time)
{
	CMRGUIEventAdapter* event = new CMRGUIEventAdapter(*m_accumulateEventState);
	event->SetEventType(CMRGUIEventAdapter::FRAME);
	event->SetTime(time);

	AddEvent(event);

	return event;
}

void MR::CMREventQueue::Clear()
{
	OpenThreads::ScopedLock<OpenThreads::Mutex> lock(m_eventQueueMutex);
	m_eventQueue.clear();
}

CMRGUIEventAdapter * MR::CMREventQueue::CreateEvent()
{
	if (m_accumulateEventState.Valid()) return new CMRGUIEventAdapter(*m_accumulateEventState.Get());
	else return new CMRGUIEventAdapter();
}

CMRGUIEventAdapter * MR::CMREventQueue::UserEvent(CMRRef * userEventData, double time)
{
	CMRGUIEventAdapter* event = new CMRGUIEventAdapter(*m_accumulateEventState);
	event->SetEventType(CMRGUIEventAdapter::USER);
	event->SetUserData(userEventData);
	event->SetTime(time);

	AddEvent(event);

	return event;
}

MR::CMREventQueue::~CMREventQueue()
{
}


