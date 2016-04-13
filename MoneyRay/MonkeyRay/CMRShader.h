#ifndef CMRShader_h__
#define CMRShader_h__

#include "CMRPrerequisites.h"
#include "CMRRef.h"
#include "CMRFile.h"
namespace MR
{
	class CMRShader : public CMRRef
	{
	public:
		struct ShaderSort 
		{
			bool operator()(const SmartPtr<CMRShader>& lhs, const SmartPtr<CMRShader> rhs)
			{
				if (lhs->GetFileName() == rhs->GetFileName() || lhs->GetShaderType() == rhs->GetShaderType())
				{
					return false;
				}
				return lhs->GetShaderIndex() < rhs->GetShaderIndex();
			}
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
		CMRShader(ShaderType type, const string& strFileName)
			:m_bIsCompiled(false),
			m_shaderType(type),
			m_strFullPath(CMRConfig::Instance()->s_strShaderDir + strFileName),
			m_bValid(false)
		{

		}

		~CMRShader()
		{
			DestroyShader();
		}

		bool IsCompiled() const
		{
			return m_bIsCompiled;
		}

		string GetFileName() const
		{
			return CMRFile::GetFileNameAux(m_strFullPath);
		}

		ShaderType GetShaderType() const
		{
			return m_shaderType;
		}

		string ReadShader(const string& strShaderName)
		{
			return CMRFile::ReadFile(strShaderName);
		}

		void CreateShader()
		{
			m_shaderObject = glCreateShader(m_shaderType);
			if (0 == m_shaderObject)
			{
				CMR_STD_ERROR << "Error : Create " << m_strFullPath << " shader failed" << CMR_STD_ENDL;
				exit(1);
			}
			m_bValid = true;
		}

		bool IsValid() const
		{
			return m_bValid;
		}

		void CompileShader()
		{
			if (!IsValid())
			{
				CreateShader();
			}
			string strShaderSource = ReadShader(m_strFullPath);
			const GLchar* szShaderSourceArray[1] = { strShaderSource.c_str() };
			glShaderSource(m_shaderObject, 1, szShaderSourceArray, NULL);
			glCompileShader(m_shaderObject);

			GLint compileResult;
			glGetShaderiv(m_shaderObject, GL_COMPILE_STATUS, &compileResult);
			if (GL_TRUE != compileResult)
			{
				GLint logLen;
				glGetShaderiv(m_shaderObject, GL_INFO_LOG_LENGTH, &logLen);
				if (logLen > 0)
				{
					char* szLog = (char*)malloc(sizeof(char) * logLen);
					GLsizei written;
					glGetShaderInfoLog(m_shaderObject, logLen, &written, szLog);
					CMR_STD_ERROR << m_strFullPath << " shader compile log : " << CMR_STD_ENDL;
					CMR_STD_ERROR << szLog << CMR_STD_ENDL;
					free(szLog);
				}
			}
			else
			{
				m_bIsCompiled = true;
			}

		}

		GLuint GetShaderObject() const
		{
			return m_shaderObject;
		}

		void DestroyShader()
		{
			glDeleteShader(m_shaderObject);
			m_shaderObject = 0;
			m_bValid = false;
		}

		int GetShaderIndex() const
		{
			if (GetShaderType() == VERTEX)
			{
				return 0;
			}
			if (GetShaderType() == TESSCONTROL)
			{
				return 1;
			}
			if (GetShaderType() == TESSEVALUATION)
			{
				return 2;
			}
			if (GetShaderType() == GEOMETRY)
			{
				return 3;
			}
			if (GetShaderType() == FRAGMENT)
			{
				return 4;
			}
			if (GetShaderType() == COMPUTE)
			{
				return 5;
			}
		}

	protected:
		bool m_bIsCompiled;
		ShaderType m_shaderType;
		string m_strFullPath;
		GLuint m_shaderObject;
		bool m_bValid;
	};
}
#endif // CMRShader_h__
