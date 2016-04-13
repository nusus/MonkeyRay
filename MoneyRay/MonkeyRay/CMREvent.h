#ifndef CMREVENT
#define CMREVENT 1


#include "CMRObject.h"

namespace MR {

	class CMRGUIEventAdapter;

	class CMREvent : public MR::CMRObject
	{
	public:
		CMREvent();

		CMREvent(const CMREvent& rhs, const MR::CMRCopyPolicy& copyop = MR::CMRCopyPolicy::SHALLOW_COPY);

		META_OBJECT(io, CMREvent);

		virtual CMRGUIEventAdapter* AsGUIEventAdapter() { return 0; }
		virtual const CMRGUIEventAdapter* AsGUIEventAdapter() const { return 0; }
		void SetHandled(bool handled) const { m_handled = handled; }
		bool GetHandled() const { return m_handled; }
		void SetTime(double time) { m_time = time; }
		double GetTime() const { return m_time; }

	protected:
		virtual ~CMREvent() {}

		mutable bool        m_handled;
		double              m_time;

	};
}
#endif