#ifndef CMRProgram_h__
#define CMRProgram_h__

#include "CMRRef.h"
#include "CMRShader.h"
#include "SmartPtr.h"
#include <utility>

namespace MR
{
	class CMRUniformRef;
	class CMRProgram : public CMRRef
	{
	public:
		typedef CMRShader::ShaderSet  Shaders;


	public:
		CMRProgram();

		virtual ~CMRProgram();

		void CompileAndAttachAllShaders(GLuint programObject);

		bool InitProgram();

		void UseProgram();

		bool IsReady() const;

		void DestroyProgram();

		GLuint GetProgramObject() const;

		void AddShader(CMRShader* shader);

		void SetShaderSet(const CMRShader::ShaderSet& shaderSet);

		void Accept(CMRUniformRef& uniform);

		void ClearShaderSet();


	protected:
		bool m_bReady;
		GLuint m_programObject;
		Shaders m_shaders;
	};
}
#endif // CMRProgram_h__
