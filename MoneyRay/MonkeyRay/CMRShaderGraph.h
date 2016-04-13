#ifndef CMRShaderGraph_h__
#define CMRShaderGraph_h__
#include "CMRShaderGraphNode.h"
namespace MR
{
	class CMRShaderGraph : public CMRShaderGraphNode
	{
	public:
		CMRShaderGraph() :
			CMRShaderGraphNode(nullptr, nullptr)
		{

		}
		CMRShaderGraphNode* PushShaderSet(const CMRShader::ShaderSet& shaderSet)
		{
			typedef CMRShader::ShaderSet ShaderSet;
			CMRShaderGraphNode* pCurrentNode = this;
			for (
				ShaderSet::iterator itr = shaderSet.begin();
				itr != shaderSet.end();
				++ itr)
			{
				if ((*itr).Valid() )
				{
					pCurrentNode = pCurrentNode->AddChild((*itr).Get());
				}
			}
			return pCurrentNode;
		}
	protected:
	private:
	};
}
#endif // CMRShaderGraph_h__
