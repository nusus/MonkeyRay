#ifndef CMRObject_h__
#define CMRObject_h__
#include "CMRPrerequisites.h"
#include "CMRRef.h"
namespace MR
{
	class CMRNode;
	class CMRNodeVisitor;

	class CMRObject : public CMRRef
	{	
	public:
		virtual CMRNode* AsNode() { return nullptr; }
		virtual const CMRNode* AsNode() const { return nullptr; }

		virtual CMRNodeVisitor* AsNodeVisitor() { return nullptr; }
		virtual const CMRNodeVisitor* AsNodeVisitor() const { return nullptr; }

	public:
		virtual void SetName(const string& name);
		void SetName(const char* pszName);	
		const string& GetName() const;
		
	protected:
		virtual ~CMRObject();;
		string m_strName;
	private:
		CMRObject& operator = (const CMRObject&);
	};

}
#endif // CMRObject_h__
