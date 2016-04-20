#ifndef CMRShader_h__
#define CMRShader_h__

#include "CMRRef.h"
#include "CMRFile.h"
#include "SmartPtr.h"
namespace MR
{
	class CMRShader : public CMRRef
	{
	public:
		struct ShaderSort 
		{
			bool operator()(const SmartPtr<CMRShader>& lhs, const SmartPtr<CMRShader> rhs);
		};

		typedef set<SmartPtr<CMRShader>, ShaderSort> ShaderSet;
	public:
		enum ShaderType
		{
			VERTEX			= GL_VERTEX_SHADER,
			TESSCONTROL		= GL_TESS_CONTROL_SHADER,
			TESSEVALUATION	= GL_TESS_EVALUATION_SHADER,
			GEOMETRY		= GL_GEOMETRY_SHADER,
			FRAGMENT		= GL_FRAGMENT_SHADER,
			COMPUTE			= GL_COMPUTE_SHADER,
			UNDEFINED		= -1
		};
	public:
		CMRShader(ShaderType type, const string& strFileName);

		~CMRShader();

		bool IsCompiled() const;

		string GetFileName() const;

		ShaderType GetShaderType() const;

		string ReadShader(const string& strShaderName);

		void CreateShader();

		bool IsValid() const;

		void CompileShader();

		GLuint GetShaderObject() const;

		void DestroyShader();

		int GetShaderIndex() const;

	protected:
		bool m_bIsCompiled;
		ShaderType m_shaderType;
		string m_strFullPath;
		GLuint m_shaderObject;
		bool m_bValid;
	};
}
#endif // CMRShader_h__
