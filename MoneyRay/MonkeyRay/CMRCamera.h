#ifndef CMRCamera_h__
#define CMRCamera_h__
#include "CMRTransform.h"
#include "CMRCullSettings.h"
#include "CMRRender.h"
#include "CMRMacroUtil.h"
#include "CMRVec4.h"
#include "CMRColorMask.h"
#include "CMRViewport.h"
#include "CMRMatrixf.h"
#include "CMRMatrixd.h"
#include "CMRVec3d.h"
#include "CMRVec3f.h"
#include "CMRRenderInfo.h"
#include "CMRViewBase.h"
#include "CMRGraphicsContext.h"
namespace MR
{
	class CMRCamera : public CMRTransform, public CMRCullSettings
	{
	public:
		enum TransformOrder
		{
			PRE_MULTIPLY,
			POST_MULTIPLY
		};

		enum ProjectionResizePolicy
		{
			FIXED, 
			HORIZONTAL, 
			VERTICAL
		};

		enum RenderOrder
		{
			PRE_RENDER,
			NESTED_RENDER,
			POST_RENDER
		};

		enum BufferComponent
		{
			DEPTH_BUFFER,
			STENCIL_BUFFER,
			PACKED_DEPTH_STENCIL_BUFFER,
			COLOR_BUFFER,
			COLOR_BUFFER0,
			COLOR_BUFFER1 = COLOR_BUFFER0 + 1,
			COLOR_BUFFER2 = COLOR_BUFFER0 + 2,
			COLOR_BUFFER3 = COLOR_BUFFER0 + 3,
			COLOR_BUFFER4 = COLOR_BUFFER0 + 4,
			COLOR_BUFFER5 = COLOR_BUFFER0 + 5,
			COLOR_BUFFER6 = COLOR_BUFFER0 + 6,
			COLOR_BUFFER7 = COLOR_BUFFER0 + 7,
			COLOR_BUFFER8 = COLOR_BUFFER0 + 8,
			COLOR_BUFFER9 = COLOR_BUFFER0 + 9,
			COLOR_BUFFER10 = COLOR_BUFFER0 + 10,
			COLOR_BUFFER11 = COLOR_BUFFER0 + 11,
			COLOR_BUFFER12 = COLOR_BUFFER0 + 12,
			COLOR_BUFFER13 = COLOR_BUFFER0 + 13,
			COLOR_BUFFER14 = COLOR_BUFFER0 + 14,
			COLOR_BUFFER15 = COLOR_BUFFER0 + 15
		};

		struct DrawCallBack : virtual public CMRObject 
		{
			DrawCallBack();
			DrawCallBack(const DrawCallBack&, const CMRCopyPolicy&) {}
			META_OBJECT(Monkey, DrawCallBack);
			virtual void operator() (const CMRRenderInfo& renderInfo ) const;
			virtual void operator() (const CMRCamera& camera) const {}
		};
	public:
		CMRCamera();
		
		CMRCamera(const CMRCamera& camera, const CMRCopyPolicy& policy = CMRCopyPolicy::SHALLOW_COPY);

		META_NODE(CMRCamera);

	public:
		virtual CMRCamera* AsCamera() { return this; }
		virtual const CMRCamera* AsCamera() const { return this; }

		void SetView(CMRView* pView) { m_pView = pView; }
		CMRView* GetView() { return m_pView; }
		const CMRView* GetView() const { return m_pView; }

		inline void SetClearMask(GLbitfield mask) { m_clearMask = mask;		ApplyMaskAction(CLEAR_MASK); }

		void SetClearColor(const CMRVec4& color) { m_clearColor = color;  ApplyMaskAction(CLEAR_COLOR); }

		const CMRVec4& GetClearColor() const { return m_clearColor; }

		void SetClearAccum(const CMRVec4& accum) { m_clearAccum = accum; }
		const CMRVec4& GetClearAccum() const { return m_clearAccum; }

		void SetClearDepth(const double depth) { m_clearDepth = depth; }
		double GetClearDepth() const { return m_clearDepth; }

		void SetClearStencil(int stencil) { m_clearStencil = stencil; }
		const int GetClearStencil() const { return m_clearStencil; }

		void SetColorMask(CMRColorMask* colorMask);
		void SetColorMask(bool red, bool green, bool blue, bool alpha);
		CMRColorMask* GetColorMask();
		const CMRColorMask* GetColorMask() const;

		void SetViewport(CMRViewport* pViewport);
		void SetViewport(int x, int y, int width, int height);
		const CMRViewport* GetViewport() const;
		CMRViewport* GetViewport();

		void SetTransformOrder(TransformOrder order) { m_transformOrder = order; }
		TransformOrder GetTransformOrder() const { return m_transformOrder; }

		inline void SetProjectionResizePolicy(ProjectionResizePolicy policy) { m_projectionResizePolicy = policy; }
		inline ProjectionResizePolicy GetProjectionResizePolicy() const { return m_projectionResizePolicy; }

		inline void SetProjectionMatrix(const CMRMatrixf& matrix);
		inline void SetProjectionMatrix(const CMRMatrixd& matrix);

		void SetProjectionMatrixAsOrtho(double left, double right,
			double bottom, double top,
			double zNear, double zFar);

		void SetProjectionMatrixAsOrtho2D(double left, double right,
			double bottom, double top);

		void SetProjectionMatrixAsFrustum(double left, double right,
			double bottom, double top,
			double zNear, double zFar);

		void SetProjectionMatrixAsPerspective(double fovy, double aspectRatio,
			double zNear, double zFar);

		CMRMatrixd& GetProjectionMatrix() { return m_projectionMatrix; }
		const CMRMatrixd& GetProjectionMatrix() const { return m_projectionMatrix; }


		bool GetProjectionMatrixAsOrtho(double& left, double& right,
			double& bottom, double& top,
			double& zNear, double& zFar) const;

		bool GetProjectionMatrixAsFrustum(double& left, double& right,
			double& bottom, double& top,
			double& zNear, double& zFar) const;

		bool GetProjectionMatrixAsPerspective(double& fovy, double& aspectRatio,
			double& zNear, double& zFar) const;

		inline void SetViewMatrix(const CMRMatrixf& matrix) { m_viewMatrix.Set(matrix); DirtyBound(); }

		inline void SetViewMatrix(const CMRMatrixd& matrix) { m_viewMatrix.Set(matrix); DirtyBound(); }

		CMRMatrixd GetViewMatrix() { return m_viewMatrix; }
		const CMRMatrixd GetViewMatrix() const { return m_viewMatrix; }

		void SetViewMatrixAsLookAt(const CMRVec3d& eye, const CMRVec3d& center, const CMRVec3d& up);

		void GetViewMatrixAsLookAt(CMRVec3d& eye, CMRVec3d& center, CMRVec3d& up, double lookDistance = 1.0) const;

		void GetViewMatrixAsLookAt(CMRVec3f& eye, CMRVec3f& center, CMRVec3f& up, double lookDistance = 1.0) const;

		CMRMatrixd GetInverseViewMatrix() const;

		void SetRenderOrder(RenderOrder order, int orderNum = 0) 
		{ 
			m_renderOrder = order; 
			m_renderOrderNum = orderNum;
		}

		RenderOrder GetRenderOrder() const { return m_renderOrder; }

		int GetRenderOrderNum() const { return m_renderOrderNum; }

		void SetDrawBuffer(GLenum buffer) { m_drawBuffer = buffer; ApplyMaskAction(DRAW_BUFFER); }
		GLenum GetDrawBuffer() const { return m_drawBuffer; }

		void SetReadBuffer(GLenum buffer) { m_readBuffer = buffer; ApplyMaskAction(READ_BUFFER); }
		GLenum GetReadBuffer() const { return m_readBuffer; }

		static const unsigned int FACE_CONTROLLED_BY_GEOMETRY_SHADER;

		void Attach(BufferComponent buffer, GLenum internalFormat);

		void Attach(BufferComponent buffer, CMRTexture* texture, unsigned int level = 0, unsigned int face = 0, bool mipMapGeneration = false,
			unsigned int multisampleSamples = 0,
			unsigned int multisampleColorSamples = 0);

		void Attach(BufferComponent buffer, CMRImage* image,
			unsigned int multisampleSamples = 0,
			unsigned int multisampleColorSamples = 0);

		void Detach(BufferComponent buffer);

		void SetGraphicsContext(CMRGraphicsContext* context);
		CMRGraphicsContext* GetGraphicsContext() { return m_graphicsContext.Get(); }

		const CMRGraphicsContext* GetGraphicsContext() const { return m_graphicsContext.Get(); }

		void SetRender(CMRGraphicsOperation* rc) { m_render = rc; }
		CMRGraphicsOperation* GetRender() { return m_render.Get(); }
		const CMRGraphicsOperation* GetRender() const { return m_render.Get(); }

		void SetRenderCache(CMRObject* cache) { m_renderCache = cache; }
		CMRObject* GetRenderCache() { return m_renderCache.Get(); }
		const CMRObject* GetRenderCache() const { return m_renderCache.Get(); }

		void SetInitialDrawCallback(DrawCallBack* cb) { m_initialDrawCallback = cb; }
		DrawCallBack* GetInitialDrawCallback() { return m_initialDrawCallback.Get(); }
		const DrawCallBack* GetInitialDrawCallback() const { return m_initialDrawCallback.Get(); }

		void SetPreDrawCallback(DrawCallBack* cb) { m_preDrawCallback = cb; }
		DrawCallBack* GetPreDrawCallback() { return m_preDrawCallback.Get(); }
		const DrawCallBack* GetPreDrawCallback() const { return m_preDrawCallback.Get(); }

		void SetPostDrawCallBack(DrawCallBack* cb) { m_postDrawCallback = cb; }
		DrawCallBack* GetPostDrawCallback() { return m_postDrawCallback.Get(); }
		const DrawCallBack* GetPostDrawCallback() const { return m_postDrawCallback.Get(); }

		void SetFinalDrawCallback(DrawCallBack* cb) { m_finalDrawCallback = cb; }
		DrawCallBack* GetFinalDrawCallback() { return m_finalDrawCallback.Get(); }
		const DrawCallBack* GetFinalDrawCallback() const { return m_finalDrawCallback.Get(); }

		virtual void ResizeGLObjectBuffers(unsigned int max) override;
		virtual void ReleaseGLObjects(CMRState* state = 0) const override;


	public:

		CMRCallback* GetUpdateCallback()
		{
			//TODO:  is not implemented
			throw std::logic_error("The method or operation is not implemented.");
		}

		void Accept(CMRNodeVisitor& nv)
		{
			//TODO: CMRCamera is not implemented
			throw std::logic_error("The method or operation is not implemented.");
		}

		void SetView(CMRViewBase* param1)
		{
			//TODO: CMRCamera is not implemented
			throw std::logic_error("The method or operation is not implemented.");
		}

	public:
		virtual bool ComputeLocalToWorldMatrix(CMRMatrix& matrix, CMRNodeVisitor* nv) const;

		virtual bool ComputeWorldToLocalMatrix(CMRMatrix& matrix, CMRNodeVisitor* nv) const;

		virtual void InheritCullSettings(const CMRCullSettings& settings, unsigned int inheritanceMask);



	protected:
		virtual ~Camera();

	protected:

		CMRView* m_pView;
		GLbitfield m_clearMask;
		CMRVec4 m_clearColor;
		CMRVec4 m_clearAccum;
		double m_clearDepth;
		int m_clearStencil;
		TransformOrder m_transformOrder;
		ProjectionResizePolicy m_projectionResizePolicy;
		CMRMatrixd m_projectionMatrix;
		CMRMatrixd m_viewMatrix;
		RenderOrder m_renderOrder;
		int m_renderOrderNum;
		GLenum m_drawBuffer;
		GLenum m_readBuffer;
		SmartPtr<CMRGraphicsContext> m_graphicsContext;
		SmartPtr<CMRGraphicsOperation> m_render;
	};
}
#endif // CMRCamera_h__
