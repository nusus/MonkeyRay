#ifndef CMRMemManager_h__
#define CMRMemManager_h__
#include "CMRPrerequisites.h"
#include "CMRRef.h"
namespace MR
{
	class CMRMemManager
	{
	public:
		typedef std::pair<unsigned int, const CMRRef*> FrameNumberObjectPair;
		typedef MR::list<FrameNumberObjectPair> ObjectToDeleteList;

	public:
		CMRMemManager(unsigned int nNumFramesToRetainObjects = 0);

		virtual ~CMRMemManager();

	public:
		void SetNumberFramesToRetainObjects(unsigned int nNumFramesToRetainObjects);

		unsigned int GetNumberFramesToRetainObjects() const;

		void SetCurrentFrameNumber(unsigned int nCurrentFrame);

		unsigned int GetCurrentFrameNumber() const;

		void DeleteAux(const CMRRef* obj);

		virtual void Flush();

		virtual void FlushAll();

		virtual void RequestDelete(const CMRRef* obj);
	protected:
		CMRMemManager(const CMRMemManager&);

		CMRMemManager& operator = (const CMRMemManager&);

	protected:
		unsigned int m_nNumberFramesToRetainObjects;
		unsigned int m_nCurrentFrameNumber;
		#if MR_USE_MULTITHREAD
std::mutex m_mutex;
#endif
		ObjectToDeleteList m_ObejectsToDelete;
	};
}
#endif // CMRMemManager_h__
