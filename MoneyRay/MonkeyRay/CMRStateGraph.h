#ifndef CMRStateGraph_h__
#define CMRStateGraph_h__
#include "CMRStateGraphNode.h"
#include "CMRCamera.h"
namespace MR
{
	class CMRStateGraph : public CMRStateGraphNode
	{
	public:
		typedef vector<vmath::mat4>  MatrixStack;


	public:
		CMRStateGraph();

	public:
		void Init(CMRNode* pNode);

		bool IsInit() const;

		virtual void Apply(CMRNode& node) override;

		virtual void Apply(CMRDrawable& node) override;

		virtual void Apply(CMRCamera& node) override;

		CMRStateGraphNode* PushShaderSet(const CMRShader::ShaderSet& shaderSet);

		void Reset();

		void PushMatrixStack(const vmath::mat4& matrix);
		void PopMatrixStack();
	protected:
		CMRStateGraph(const CMRStateGraph&) = delete;
		CMRStateGraph& operator=(const CMRStateGraph&) = delete;
		virtual ~CMRStateGraph();


	protected:
		struct GetMVPWMatrixOp
		{
			vmath::mat4 operator()(const vmath::mat4& lhs, const vmath::mat4& rhs);
		};
		vmath::mat4 _GetMVPWMatrix() const;



	protected:
		bool m_bInitialized;
		MatrixStack m_mvpwStack;
	};
}
#endif // CMRStateGraph_h__
