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
		typedef vector<vmath::mat4> MatrixStack;
	public:

		CMRState()
			:m_spProgram(new CMRProgram)
		{}

		void PushStateSet(const CMRStateSet& stateSet)
		{
			m_mvpMatrix.push_back(stateSet.GetMatrix());
			m_shaderSet.insert(stateSet.GetShader());
		}

		void PopStateSet()
		{
			m_mvpMatrix.pop_back();
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
			vmath::mat4 mvpMatrixRet = vmath::mat4::identity();
			for (auto curMatrix : m_mvpMatrix)
			{
				mvpMatrixRet *= curMatrix;
			}
			CMRUniformMatrix4fv mvp_uniform("uni_mvp_matrix", mvpMatrixRet);
			m_spProgram->ApplyUniform(mvp_uniform);
			
		}

		void PopState()
		{
			m_spProgram = new CMRProgram;
		}
	protected:
		typedef CMRShader::ShaderSet ShaderSet;
		MatrixStack m_mvpMatrix;
		ShaderSet m_shaderSet;
		SmartPtr<CMRProgram> m_spProgram;
	};
}
#endif // CMRState_h__
