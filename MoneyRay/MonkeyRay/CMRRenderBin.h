#ifndef CMRRenderBin_h__
#define CMRRenderBin_h__
#include "CMRPrerequisites.h"
#include "CMRObject.h"
#include "CMRRenderLeaf.h"
#include "CMRShaderGraph.h"
#include "CMRProgram.h"
#include "..\Test\vmath.h"
namespace MR
{
	class CMRRenderBin : public CMRObject
	{
	public:
		typedef vector<CMRRenderLeaf*> RenderLeafList;
		typedef vector<CMRShaderGraph*> ShaderGraphList;
		typedef map<int, SmartPtr<CMRRenderBin> > RenderBinList;
	public:
	protected:
		int m_nBinNum;
		CMRRenderStage* m_pStage;
		RenderLeafList m_renderLeafList;

		SmartPtr<CMRProgram> m_spProgram;
	};
}
#endif // CMRRenderBin_h__
