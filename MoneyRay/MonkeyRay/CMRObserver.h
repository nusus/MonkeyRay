#ifndef CMRObserver_h__
#define CMRObserver_h__

#include "CMRRef.h"
#include "CMRContainerConfig.h"
namespace MR
{
	class CMRSubsciber
	{
	public:
		CMRSubsciber();
		virtual ~CMRSubsciber();

		virtual void SubsciberDeleted(void*) {}
	protected:
	private:
	};

	class CMRSubsciption :public MR::CMRRef
	{
	public:
		typedef set<CMRSubsciber*> Subscribers;

		CMRSubsciption(const CMRRef* ptr);

		CMRRef* GetPublisher()
		{
			return m_pPublisher;
		}

		const CMRRef* GetPublisher() const
		{
			return m_pPublisher;
		}

#if MR_USE_MULTITHREAD
		inline std::mutex* GetSubscriptionMutex() { return &m_mutex; }
#endif
		void AddSubscriber(CMRSubsciber* obj);
		void RemoveSubscriber(CMRSubsciber* obj);

		void SignalObjectDeleted(void* ptr);

		CMRRef* AddRefLock();

		Subscribers& GetSubscribers() { return m_Subscibers; }
		const Subscribers& GetSubscribers() const { return m_Subscibers; }
	protected:
		CMRSubsciption(const CMRSubsciption& obj) :CMRRef(obj) {}
		CMRSubsciption& operator = (const CMRSubsciption& obj) { return *this; }
		virtual ~CMRSubsciption();

	protected:
#if MR_USE_MULTITHREAD
		std::mutex m_mutex;
#endif
		CMRRef* m_pPublisher;
		Subscribers m_Subscibers;
	private:
	};

	

}
#endif // CMRObserver_h__
