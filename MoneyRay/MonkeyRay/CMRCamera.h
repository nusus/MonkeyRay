#ifndef CMRCamera_h__
#define CMRCamera_h__
#include "CMRNode.h"
#include "CMRView.h"
#include "CMRViewport.h"
#include "CMRGraphicsContext.h"
namespace MR
{
	class CMRView;
	class CMRCamera : public CMRNode
	{
	public:
		CMRCamera();


	public:
		virtual CMRCamera* AsCamera();
		virtual const CMRCamera* AsCamera() const;

		void SetView(CMRViewBase* pView);
		CMRViewBase* GetView();
		const CMRViewBase* GetView() const;

		void SetViewport(CMRViewport* pViewport);
		void SetViewport(int x, int y, int width, int height);
		const CMRViewport* GetViewport() const;
		CMRViewport* GetViewport();

		inline void SetProjectionMatrix(const vmath::mat4& matrix);
		vmath::mat4& GetProjectionMatrix();
		const vmath::mat4& GetProjectionMatrix() const;

		void SetProjectionMatrixAsFrustum(double left, double right,
			double bottom, double top,
			double zNear, double zFar);
		bool GetProjectionMatrixAsFrustum(double& left, double& right,
			double& bottom, double& top,
			double& zNear, double& zFar) const;

		void SetProjectionMatrixAsPerspective(double fovy, double aspectRatio,
			double zNear, double zFar);
		bool GetProjectionMatrixAsPerspective(double& fovy, double& aspectRatio,
			double& zNear, double& zFar) const;

		void SetViewMatrix(const vmath::mat4& matrix);
		vmath::mat4& GetViewMatrix();
		const vmath::mat4&  GetViewMatrix() const;

		void SetViewMatrixAsLookAt(const vmath::vec3& eye, const vmath::vec3& center, const vmath::vec3& up);
		void GetViewMatrixAsLookAt(vmath::vec3& eye, vmath::vec3& center, vmath::vec3& up, double lookDistance = 1.0) const;

		vmath::mat4 GetInverseViewMatrix() const;

		void SetGraphicsContext(CMRGraphicsContext* context);
		CMRGraphicsContext* GetGraphicsContext();
		const CMRGraphicsContext* GetGraphicsContext() const;

		void SetRender(CMROperation* rc);
		CMROperation* GetRender();
		const CMROperation* GetRender() const;


	protected:
		CMRCamera(const CMRCamera&) {}
		CMRCamera& operator=(const CMRCamera&) { return *this; }
		virtual ~CMRCamera();


	protected:
		CMRViewBase*					m_pView;
		vmath::mat4						m_matProjectionMatrix;
		vmath::mat4						m_matViewMatrix;
		SmartPtr<CMRGraphicsContext>	m_spGraphicsContext;
		SmartPtr<CMROperation>			m_spRender;
		SmartPtr<CMRViewport>			m_spViewport;
	};
}
#endif // CMRCamera_h__
