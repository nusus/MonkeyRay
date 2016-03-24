#ifndef CMRUpdateVisitor_h__
#define CMRUpdateVisitor_h__
#include "CMRNodeVisitor.h"
namespace MR
{
	class CMRUpdateVisitor : public CMRNodeVisitor
	{
	public:
		void Reset()
		{
			//TODO:  is not implemented
			throw std::logic_error("The method or operation is not implemented.");
		}

		void SetFrameStamp(const CMRFrameStamp* param1)
		{
			//TODO: CMRUpdateVisitor is not implemented
			throw std::logic_error("The method or operation is not implemented.");
		}

		void SetTraversalNumber(unsigned int uiFrameNumber)
		{
			//TODO: CMRUpdateVisitor is not implemented
			throw std::logic_error("The method or operation is not implemented.");
		}

		CMRNodeVisitor::TraversalMode GetTraversalMode()
		{
			//TODO: CMRUpdateVisitor is not implemented
			throw std::logic_error("The method or operation is not implemented.");
		}

		void SetTraversalMode(CMRNodeVisitor::TraversalMode param1)
		{
			//TODO: CMRUpdateVisitor is not implemented
			throw std::logic_error("The method or operation is not implemented.");
		}





	};
}
#endif // CMRUpdateVisitor_h__
