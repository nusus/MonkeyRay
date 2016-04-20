#ifndef CMRRenderStage_h__
#define CMRRenderStage_h__

#include "CMRRenderBin.h"
namespace MR
{
	class CMRRenderStage : public CMRRenderBin
	{
	public:
		CMRRenderStage();
	public:
		void Reset();

		virtual void Draw() const override;

		void Init(CMRStateGraph* pStateGraph);

		void Apply(CMRStateGraphNode& node);

		bool IsInit() const;
	protected:
		bool m_bInitialized;

	protected:
		typedef vector<const CMRShader*> ShaderStack;
		ShaderStack m_shaderStack;
	};
}
#endif // CMRRenderStage_h__
