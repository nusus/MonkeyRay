#ifndef CMREVENTQUEUE
#define CMREVENTQUEUE 1

#include "CMRGUIEventAdapter.h"

#include "SmartPtr.h"
//#include <osg/Timer>
#include <list>
namespace MR {
	class  CMREventQueue : public MR::CMRRef
	{
	public:

		CMREventQueue(CMRGUIEventAdapter::MouseYOrientation mouseYOrientation = CMRGUIEventAdapter::Y_INCREASING_DOWNWARDS);

		typedef std::list< MR::SmartPtr<CMREvent> > Events;

		bool Empty() const
		{
			OpenThreads::ScopedLock<OpenThreads::Mutex> lock(m_eventQueueMutex);
			return m_eventQueue.empty();
		}
		void SetEvents(Events& events);
		bool TakeEvents(Events& events);
		bool TakeEvents(Events& events, double cutOffTime);
		bool CopyEvents(Events& events) const;
		void AppendEvents(Events& events);
		void AddEvent(CMREvent* event);
		void SetUseFixedMouseInputRange(bool useFixedMouseInputRange) { m_useFixedMouseInputRange = useFixedMouseInputRange; }
		bool GetUseFixedMouseInputRange() { return m_useFixedMouseInputRange; }
		void SetGraphicsContext(osg::GraphicsContext* context) { GetCurrentEventState()->SetGraphicsContext(context); }
		osg::GraphicsContext* GetGraphicsContext() { return GetCurrentEventState()->GetGraphicsContext(); }
		const osg::GraphicsContext* GetGraphicsContext() const { return GetCurrentEventState()->GetGraphicsContext(); }
		void SyncWindowRectangleWithGraphicsContext();
		void SetMouseInputRange(float xMin, float yMin, float xMax, float yMax) { GetCurrentEventState()->SetInputRange(xMin, yMin, xMax, yMax); }
		CMRGUIEventAdapter* WindowResize(int x, int y, int width, int height) { return WindowResize(x, y, width, height, GetTime()); }
		CMRGUIEventAdapter* WindowResize(int x, int y, int width, int height, double time);
		CMRGUIEventAdapter* MouseScroll(CMRGUIEventAdapter::ScrollingMotion sm) { return MouseScroll(sm, GetTime()); }
		CMRGUIEventAdapter* MouseScroll(CMRGUIEventAdapter::ScrollingMotion sm, double time);
		CMRGUIEventAdapter* MouseScroll2D(float x, float y) { return MouseScroll2D(x, y, GetTime()); }
		CMRGUIEventAdapter* MouseScroll2D(float x, float y, double time);

		void MouseWarped(float x, float y);
		CMRGUIEventAdapter* MouseMotion(float x, float y) { return MouseMotion(x, y, GetTime()); }
		CMRGUIEventAdapter* MouseMotion(float x, float y, double time);
		CMRGUIEventAdapter* MouseButtonPress(float x, float y, unsigned int button) { return MouseButtonPress(x, y, button, GetTime()); }
		CMRGUIEventAdapter* MouseButtonPress(float x, float y, unsigned int button, double time);
		CMRGUIEventAdapter* MouseDoubleButtonPress(float x, float y, unsigned int button) { return MouseDoubleButtonPress(x, y, button, GetTime()); }
		CMRGUIEventAdapter* MouseDoubleButtonPress(float x, float y, unsigned int button, double time);

		CMRGUIEventAdapter* MouseButtonRelease(float x, float y, unsigned int button) { return MouseButtonRelease(x, y, button, GetTime()); }
		CMRGUIEventAdapter* MouseButtonRelease(float x, float y, unsigned int button, double time);

		CMRGUIEventAdapter* KeyPress(int key, int unmodifiedKey = 0) { return KeyPress(key, GetTime(), unmodifiedKey); }
		CMRGUIEventAdapter* KeyPress(int key, double time, int unmodifiedKey = 0);
		CMRGUIEventAdapter* KeyRelease(int key, int unmodifiedKey = 0) { return KeyRelease(key, GetTime(), unmodifiedKey); }
		CMRGUIEventAdapter* KeyRelease(int key, double time, int unmodifiedKey = 0);

		CMRGUIEventAdapter* CloseWindow() { return CloseWindow(GetTime()); }
		CMRGUIEventAdapter* CloseWindow(double time);
		CMRGUIEventAdapter* QuitApplication() { return QuitApplication(GetTime()); }
		CMRGUIEventAdapter* QuitApplication(double time);
		CMRGUIEventAdapter* Frame(double time);

		void SetStartTick(osg::Timer_t tick) { m_startTick = tick; Clear(); }
		osg::Timer_t getStartTick() const { return m_startTick; }

		double GetTime() const { return osg::Timer::instance()->delta_s(m_startTick, osg::Timer::instance()->tick()); }
		void Clear();
		CMRGUIEventAdapter* CreateEvent();
		void SetCurrentEventState(CMRGUIEventAdapter* ea) { m_accumulateEventState = ea; }
		CMRGUIEventAdapter* GetCurrentEventState() { return m_accumulateEventState.Get(); }
		CMRGUIEventAdapter* UserEvent(CMRRef* userEventData) { return UserEvent(userEventData, GetTime()); }
		CMRGUIEventAdapter* UserEvent(CMRRef* userEventData, double time);
	
	protected:
		virtual ~CMREventQueue();
		CMREventQueue& operator = (const CMREventQueue&) { return *this; }
		SmartPtr<CMRGUIEventAdapter>   m_accumulateEventState;
		bool                        m_useFixedMouseInputRange;
		osg::Timer_t                m_startTick;
		mutable OpenThreads::Mutex  m_eventQueueMutex;
		Events                      m_eventQueue;
		bool                        m_firstTouchEmulatesMouse;

	};
}
#endif