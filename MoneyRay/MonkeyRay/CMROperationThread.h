#ifndef CMROperationThread_h__
#define CMROperationThread_h__
#include "CMRRef.h"
namespace MR
{
	class CMROperation : virtual public CMRRef
	{
	public:
		CMROperation(const string& strName, bool bKeep)
			:m_strName(strName),
			m_bKeep(bKeep)
		{

		}

		void SetName(const string& name) { m_strName = name; }
		string GetName() const { return m_strName; }

		void SetKeep(const bool bKeep) { m_bKeep = bKeep; }
		bool GetKeep() const { return m_bKeep; }

		virtual void ReleaseOperation() {}

		void Test()
		{

		}
	protected:
		CMROperation() :m_bKeep(false) {}
		CMROperation(const CMROperation& op)
			:m_strName(op.m_strName),
			m_bKeep(op.m_bKeep) {}
		virtual ~CMROperation() {}
	protected:
		string m_strName;
		bool m_bKeep;
	};
}
#endif // CMROperationThread_h__
