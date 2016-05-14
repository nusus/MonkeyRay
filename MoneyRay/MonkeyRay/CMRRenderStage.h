#ifndef CMRRenderStage_h__
#define CMRRenderStage_h__

#include "CMRRenderBin.h"
#include "CMRStateGraph.h"
#include "CMRScene.h"
namespace MR
{
	class CMRRenderStage : public CMRRenderBin
	{
	public:
		typedef vector<const CMRShader*> ShaderStack;


	public:
		CMRRenderStage();


	public:
		void Reset();

		virtual void Draw() const override;

		void Init(CMRStateGraph* pStateGraph);

		void Apply(CMRStateGraphNode& node);

		bool IsInit() const;


	protected:
		CMRRenderStage(const CMRRenderStage&) = delete;
		CMRRenderStage& operator=(const CMRRenderStage&) = delete;
		virtual ~CMRRenderStage() {}

	protected:
		bool m_bInitialized;
		ShaderStack m_shaderStack;
	};
}
#endif // CMRRenderStage_h__
