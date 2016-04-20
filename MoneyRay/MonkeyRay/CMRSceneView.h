#ifndef CMRSceneView_h__
#define CMRSceneView_h__
#include "CMRPrerequisites.h"
#include "CMRRenderStage.h"
#include "CMRCullVisitor.h"
#include "CMRTemplateMatrix.h"
namespace MR
{
	class CMRSceneView
	{
	public:

		void SetViewport(CMRViewport* pViewport)
		{
			m_wpCamera->SetViewport(pViewport);
		}

		void SetViewport(int x, int y, int width, int height)
		{
			m_wpCamera->SetViewport(x, y, width, height);
		}

		CMRViewport* GetViewport() {
			return (m_wpCamera->GetViewport() != nullptr) ? m_wpCamera->GetViewport() : nullptr;
		}

		void SetCamera(CMRCamera* pCamera);
		CMRCamera* GetCamera();
		const CMRCamera* GetCamera() const;

		void SetSceneData(CMRNode* pNode);
		CMRNode* GetSceneData();
		const CMRNode* GetSceneData() const;

		const CMRViewport* GetViewport() const
		{
			return (m_wpCamera->GetViewport() != nullptr) ? m_wpCamera->GetViewport() : nullptr;
		}

		inline void SetProjectionMatrix(const CMRMatrixf& matrix);
		inline void SetProjectionMatrix(const CMRMatrixd& matrix);

		void SetProjectionMatrixAsFrustum(double left, double right, double bottom, double top, double zNear, double zFar);
		void SetProjectionMatrixAsPerspective(double fvoy, double aspectRatio, double zNear, double zFar);

		CMRMatrixd& GetProjectionMatrix();
		const CMRMatrixd& GetProjectionMatrix() const;

		bool GetProjectionMatrixAsFrustum(double& left, double& right, double& bottom, double& top, double& zNear, double& zFar) const;

		bool GetProjectionMatrixAsPerspective(double& fvoy, double& aspectRatio, double& zNear, double& zFar) const;


		inline void SetView(const CMRMatrixf& matrix);
		inline void SetView(const CMRMatrixd& matrix);
		void SetViewMatrixAsLookAt(const CMRVec3d& eye, const CMRVec3d& center, const CMRVec3d& up);

		CMRMatrixd& GetViewMatrix();
		const CMRMatrixd& GetViewMatrix() const;

		void GetViewMatrixAsLookAt(CMRVec3d& eye, CMRVec3d& center, CMRVec3d& up, float lookDistance = 1.0f) const;

		virtual void Cull()
		{
			m_renderInfo.SetView(m_wpCamera->GetView());
			if (!m_renderInfo.GetState())
			{
				CMR_STD_OUT << "scene view no valid m_wpState attached, creating a default state automatically." << CMR_STD_ENDL;
				m_renderInfo.SetState(new CMRState);
			}
			if (!m_spStateGraph)
			{
				CMR_STD_OUT << "scene view no valid shader graph attached, creating a default shader graph automatically" << CMR_STD_ENDL;
				m_spStateGraph = new CMRStateGraph;
			}
			if (!m_spRenderStage)
			{
				CMR_STD_OUT << "scene view no valid render stage attached, creating a default render stage" << CMR_STD_ENDL;
				m_spRenderStage = new CMRRenderStage;
			}

			bool bComputeNearFar = CullStage(GetProjectionMatrix(), GetViewMatrix(), m_spCullVisitor.Get(), m_spStateGraph.Get(), m_spRenderStage.Get(), GetViewport());

			if (bComputeNearFar)
			{
				CMRCullVisitor::value_type zNear = m_spCullVisitor->GetCalculateNearPlane();
				CMRCullVisitor::value_type zFar = m_spCullVisitor->GetCalculateFarPlane();
				m_spCullVisitor->ClampProjectionMatrix(GetProjectionMatrix(), zNear, zFar);
			}
		}

		//update the uniforms pre defined in the system.
		void UpdateUniforms()
		{

		}
	protected:
		virtual bool CullStage(const CMRMatrixd& projection, const CMRMatrixd& modelView, CMRCullVisitor* pCullVisitor, CMRStateGraph* pStateGraph, CMRRenderStage* pRenderStage, CMRViewport* pViewport)
		{
			if (!m_wpCamera.Valid() || !pViewport)
			{
				return false;
			}

			SmartPtr<CMRRefMatrix> proj = new CMRRefMatrix(projection);
			SmartPtr<CMRRefMatrix> mv = new CMRRefMatrix(modelView);

			pCullVisitor->Reset();
			pCullVisitor->SetFrameStamp(m_spFrameStamp.Get());

			if (m_spFrameStamp.Valid())
			{
				pCullVisitor->SetTraversalNumber(m_spFrameStamp->GetFrameNumber());
			}

			pCullVisitor->SetStateGraph(pStateGraph);
			pCullVisitor->SetRenderStage(pRenderStage);

			pCullVisitor->SetRenderInfo(m_renderInfo);
			pRenderStage->Reset();
			pRenderStage->Clean();


			pRenderStage->SetInitialViewMatrix(mv.Get());
			pRenderStage->SetViewport(pViewport);
			pRenderStage->SetClearColor(m_wpCamera->GetClearColor());
			pRenderStage->SetClearDepth(m_wpCamera->GetClearDepth());
			pRenderStage->SetClearStencil(m_wpCamera->GetClearStencil());
			pRenderStage->SetClearMask(m_wpCamera->GetColorMask());
			pRenderStage->SetCamera(m_wpCamera.Get());


			pCullVisitor->PushViewport(pViewport);
			pCullVisitor->PushProjectionMatrix(proj.Get());
			pCullVisitor->PushModelViewMatrix(mv.Get(), CMRTransform::ABSOLUTE_RF);

			{
				CMRCallback* pCallback = m_wpCamera->GetCullCallback();
				if (pCallback)
				{
					pCallback->Run(m_wpCamera.Get(), pCullVisitor);
				}
				else
				{
					pCullVisitor->Traverse(*m_wpCamera);
				}
			}

			pCullVisitor->PopModelViewMatrix();
			pCullVisitor->PopProjectionMatrix();
			pCullVisitor->PopViewport();


			pRenderStage->Sort();
			pStateGraph->Prune();

			bool bComputeNearFar = (pCullVisitor->GetComputeNearFarMode() != CMRCullVisitor::DO_NOT_COMPUTE_NEAR_FAR && GetSceneData() != 0);

			return bComputeNearFar;
		}

		const CMRMatrixd ComputeMVPW() const
		{

		}

		void ClearArea(int x, int y, int width, int height, const CMRVec4& color);


		CMRRenderInfo m_renderInfo;
		bool m_bInitCalled;
		
		SmartPtr<CMRNodeVisitor> m_spInitVisitor;
		SmartPtr<CMRNodeVisitor> m_spUpdateVisitor;
		SmartPtr<CMRCullVisitor> m_spCullVisitor;

		SmartPtr<CMRStateGraph> m_spStateGraph;
		SmartPtr<CMRRenderStage> m_spRenderStage;

		SmartPtr<CMRFrameStamp> m_spFrameStamp;
		WeakPtr<CMRCamera> m_wpCamera;


		double m_dPreviousFrameTime;
		double m_dPreviousSimulationTime;

	private:
	};
}
#endif // CMRSceneView_h__
