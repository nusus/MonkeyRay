#ifndef CMRNode_h__
#define CMRNode_h__

#include "CMRBoundingSphere.h"
#include "CMRObject.h"
namespace MR
{
	class CMRNodeVisitor;
	class CMRDrawable;
	class CMRGeometry;
	class CMRGroup;
	class CMRTransform;
	class CMRNode;
	class CMRSwitch;
	class CMRGeode;
	class CMRCamera;

	typedef vector<CMRNode*> CMRNodePath;

	class CMRNode : CMRObject
	{
	public:
		typedef unsigned int NodeMask;
	public:
		inline const CMRBoundingSphere& GetBound() const
		{
			//TODO:  is not implemented
			throw std::logic_error("The method or operation is not implemented.");
		}

		virtual void ResizeGLObjectBuffers(unsigned int) override
		{
			//TODO: CMRNode is not implemented
			throw std::logic_error("The method or operation is not implemented.");
		}


	protected:
	private:


		

	};
}
#endif // CMRNode_h__
