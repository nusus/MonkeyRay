#ifndef CMRMemManager_h__
#define CMRMemManager_h__

#include "CMRRef.h"
#include "CMRContainerConfig.h"
namespace MR
{
	class CMRMemManager
	{
	public:
		typedef std::pair<unsigned int, const CMRRef*> FrameNumberObjectPair;
		typedef MR::list<FrameNumberObjectPair> ObjectToDeleteList;

		CMRMemManager(unsigned int nNumFramesToRetainObjects = 0);

		virtual ~CMRMemManager();

		void SetNumberFramesToRetainObjects(unsigned int nNumFramesToRetainObjects) { m_nNumberFramesToRetainObjects = nNumFramesToRetainObjects; }

		unsigned int GetNumberFramesToRetainObjects() const { return m_nNumberFramesToRetainObjects; }

		void SetCurrentFrameNumber(unsigned int nCurrentFrame) { m_nCurrentFrameNumber = nCurrentFrame; }

		unsigned int GetCurrentFrameNumber() const { return m_nCurrentFrameNumber; }

		inline void DeleteAux(const CMRRef* obj) { delete obj; }

		virtual void Flush();

		virtual void FlushAll();

		virtual void RequestDelete(const CMRRef* obj);
	protected:
		CMRMemManager(const CMRMemManager&):
			m_nNumberFramesToRetainObjects(0),
			m_nCurrentFrameNumber(0)
		{}

		CMRMemManager& operator = (const CMRMemManager&) { return *this; }

		unsigned int m_nNumberFramesToRetainObjects;
		unsigned int m_nCurrentFrameNumber;
		#if MR_USE_MULTITHREAD
std::mutex m_mutex;
#endif
		ObjectToDeleteList m_ObejectsToDelete;
	};
}
#endif // CMRMemManager_h__
