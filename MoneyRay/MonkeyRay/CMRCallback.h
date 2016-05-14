#ifndef CMRCallback_h__
#define CMRCallback_h__

#include "CMRObject.h"
#include "SmartPtr.h"

namespace MR
{
	class CMRCallback : public CMRObject
	{
	public:
		CMRCallback();
	public:

		virtual bool Run(CMRObject* pObject);

		virtual void RunImpl(CMRObject* pObject);

		bool Traverse(CMRObject* pObject);

		void AddNestedCallback(CMRCallback* pc);

		void RemoveNestedCallback(CMRCallback* pUC);

		void SetNestedCallback(CMRCallback* param1);
		CMRCallback* GetNestedCallback();
		const CMRCallback* GetNestedCallback() const;

	protected:
		virtual ~CMRCallback();
		SmartPtr<CMRCallback> m_spNestedCallback;
	};
}
#endif // CMRCallback_h__
