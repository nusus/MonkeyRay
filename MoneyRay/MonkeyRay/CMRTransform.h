#ifndef CMRTransform_h__
#define CMRTransform_h__
#include "CMRMatrix.h"
#include "CMRGroup.h"
#include "CMRMatrixTransform.h"
#include "CMRPositionAttitudeTransform.h"
namespace MR
{
	extern CMRMatrix ComputeLocalToWorld(const CMRNodePath& nodePath, bool bIgnoreCameras = true);

	extern CMRMatrix ComputeWorldToLocal(const CMRNodePath& nodePath, bool bIgnoreCameras = true);

	extern CMRMatrix ComputeLocalToEye(const CMRMatrix& modelView, const CMRNodePath& nodePath, bool bIgnoreCameras = true);

	extern CMRMatrix ComputeEyeToLocal(const CMRMatrix& modelView, const CMRNodePath& nodePath, bool bIgnoreCameras = true);

	class CMRTransform : public CMRGroup
	{
	public:
		CMRTransform();

		CMRTransform(const CMRTransform& transform, const CMRCopyPolicy& policy = CMRCopyPolicy::SHALLOW_COPY);

		META_NODE(CMRTransform);

		virtual CMRTransform* AsTransform() { return this; }
		virtual const CMRTransform* AsTransform() const { return this; }

		virtual CMRMatrixTransform* AsMatrixTransform() { return nullptr; }
		virtual const CMRMatrixTransform* AsMatrixTransform() const { return nullptr; }

		virtual CMRPositionAttitudeTransform* AsPositionAttitudeTransform() { return nullptr; }
		virtual const CMRPositionAttitudeTransform* AsPositionAttitudeTransform()  const { return nullptr; }


		enum ReferenceFrame
		{
			RELATIVE_RF,
			ABSOLUTE_RF,
			ABSOLUTE_RF_INHERIT_VIEWPORT
		};

		void SetReferenceFrame(ReferenceFrame rf);
		ReferenceFrame GetReferenceFrame() const { return m_referenceFrame; }

		virtual bool ComputeLocalToWorldMatrix(CMRMatrix& matrix, CMRNodeVisitor* nv) const
		{
			if (m_referenceFrame == RELATIVE_RF)
			{
				return false;
			}
			else
			{
				matrix.MakeIdentity();
				return true;
			}
		}

		virtual bool ComputeWorldToLocalMatrix(CMRMatrix& matrix, CMRNodeVisitor* nv) const
		{
			if (m_referenceFrame == RELATIVE_RF)
			{
				return false;
			}
			else
			{
				matrix.MakeIdentity();
				return true;
			}
		}

		virtual CMRBoundingSphere ComputeBound() const;
	protected:
		virtual ~CMRTransform();

		ReferenceFrame m_referenceFrame;
	
	private:
	};
}
#endif // CMRTransform_h__
