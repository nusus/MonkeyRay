#ifndef CMRCullVisitor_h__
#define CMRCullVisitor_h__
#include "CMRPrerequisites.h"
namespace MR
{
	class CMRCullVisitor 
	{
	public:
		typedef CMRMatrix::value_type value_type;

		enum ComputeNearFarMode
		{
			DO_NOT_COMPUTE_NEAR_FAR = 0,
			COMPUTE_NEAR_FAR_USING_BOUNDING_VOLUMES,
			COMPUTE_NEAR_FAR_USING_PRIMITIVES,
			COMPUTE_NEAR_USING_PRIMITIVES
		};

		value_type GetCalculateNearPlane()
		{
			//TODO: CMRCullVisitor is not implemented
			throw std::logic_error("The method or operation is not implemented.");
		}

		value_type GetCalculateFarPlane()
		{
			//TODO: CMRCullVisitor is not implemented
			throw std::logic_error("The method or operation is not implemented.");
		}

		void ClampProjectionMatrix(const CMRMatrixd& param1, value_type zNear, value_type zFar)
		{
			//TODO: CMRCullVisitor is not implemented
			throw std::logic_error("The method or operation is not implemented.");
		}

		void Reset()
		{
			//TODO:  is not implemented
			throw std::logic_error("The method or operation is not implemented.");
		}

		void SetFrameStamp(MR::CMRFrameStamp* param1)
		{
			//TODO: CMRCullVisitor is not implemented
			throw std::logic_error("The method or operation is not implemented.");
		}

		void SetTraversalNumber(unsigned int param1)
		{
			//TODO: CMRCullVisitor is not implemented
			throw std::logic_error("The method or operation is not implemented.");
		}

		void SetStateGraph(CMRStateGraph* pStateGraph)
		{
			//TODO: CMRCullVisitor is not implemented
			throw std::logic_error("The method or operation is not implemented.");
		}

		void SetRenderStage(CMRRenderStage* pRenderStage)
		{
			//TODO: CMRCullVisitor is not implemented
			throw std::logic_error("The method or operation is not implemented.");
		}

		void SetRenderInfo(const CMRRenderInfo& m_renderInfo)
		{
			//TODO: CMRCullVisitor is not implemented
			throw std::logic_error("The method or operation is not implemented.");
		}

		void PushViewport(CMRViewport* pViewport)
		{
			//TODO: CMRCullVisitor is not implemented
			throw std::logic_error("The method or operation is not implemented.");
		}

		void PushProjectionMatrix(MR::CMRRefMatrix* param1)
		{
			//TODO: CMRCullVisitor is not implemented
			throw std::logic_error("The method or operation is not implemented.");
		}

		void PushModelViewMatrix(MR::CMRRefMatrix* param1, CMRTransform::ReferenceFrame param2)
		{
			//TODO: CMRCullVisitor is not implemented
			throw std::logic_error("The method or operation is not implemented.");
		}

		void Traverse(CMRCamera& m_wpCamera)
		{
			//TODO: CMRCullVisitor is not implemented
			throw std::logic_error("The method or operation is not implemented.");
		}

		void PopModelViewMatrix()
		{
			//TODO: CMRCullVisitor is not implemented
			throw std::logic_error("The method or operation is not implemented.");
		}

		void PopProjectionMatrix()
		{
			//TODO: CMRCullVisitor is not implemented
			throw std::logic_error("The method or operation is not implemented.");
		}

		void PopViewport()
		{
			//TODO: CMRCullVisitor is not implemented
			throw std::logic_error("The method or operation is not implemented.");
		}

		void SetComputeNearFarMode(ComputeNearFarMode cnfm);
		ComputeNearFarMode GetComputeNearFarMode() const;


	};
}
#endif // CMRCullVisitor_h__
