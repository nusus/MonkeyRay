#ifndef CMRState_h__
#define CMRState_h__
#include "CMRRef.h"
#include "CMRShader.h"
#include "vmath.h"
#include "CMRStateSet.h"
#include "CMRProgram.h"
namespace MR
{
	class CMRState : public CMRRef
	{
	public:	
		typedef stack<vmath::mat4> MatrixStack;
	public:

		void PushStateSet(const CMRStateSet& stateSet)
		{
			m_mvpMatrix.push(stateSet.GetMatrix());
			m_shaderSet.insert(stateSet.GetShader());
		}

		void PopStateSet()
		{
			m_mvpMatrix.pop();
			m_shaderSet.erase(m_shaderSet.end());

		}

		void ApplyState()
		{
			m_spProgram->SetShaderSet(m_shaderSet);
			m_spProgram->InitProgram();
			if (m_spProgram->IsReady())
			{
				m_spProgram->UseProgram();
			}
			
		}

		void PopState()
		{

		}
	protected:
		typedef CMRShader::ShaderSet ShaderSet;
		MatrixStack m_mvpMatrix;
		ShaderSet m_shaderSet;
		SmartPtr<CMRProgram> m_spProgram;
	};
}
#endif // CMRState_h__
