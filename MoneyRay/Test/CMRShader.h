#ifndef CMRShader_h__
#define CMRShader_h__
#include "CGlobalInclude.h"
#include "CMRImageLoader.h"

#include <fstream>
namespace MR
{
	class CMRShader
	{
	public:
		enum ShaderType
		{
			VERTEX = GL_VERTEX_SHADER,
			TESSCONTROL = GL_TESS_CONTROL_SHADER,
			TESSEVALUATION = GL_TESS_EVALUATION_SHADER,
			GEOMETRY = GL_GEOMETRY_SHADER,
			FRAGMENT = GL_FRAGMENT_SHADER,
			COMPUTE = GL_COMPUTE_SHADER,
			UNDEFINED = -1
		};
	public:
		CMRShader(ShaderType type, const std::string& strFileName)
			:m_bIsCompiled(false),
			m_shaderType(type),
			m_strFullPath(MR::CMRConfig::Instance()->s_strShaderDir + strFileName),
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

		std::string GetFileName() const
		{
			return GetFileNameAux(m_strFullPath);
		}

		ShaderType GetShaderType() const
		{
			return m_shaderType;
		}		
		
		static std::string ReadShader(const std::string& strShaderName)
		{
			std::ifstream in(strShaderName.c_str(), std::ios_base::in | std::ios_base::binary);
			if (!in.is_open())
			{
				return std::string();
			}
			std::istreambuf_iterator<char> beg(in), end;
			std::string ret(beg, end);

			std::cout << "read from " << strShaderName << " " << ret.size() << " characters" << std::endl;
			in.close();
			return ret;
		}

		void CreateShader()
		{
			m_shaderObject = glCreateShader(m_shaderType);
			if (0 == m_shaderObject)
			{
				std::cerr << "Error : Create " << m_strFullPath << " shader failed" << std::endl;
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
			std::string strShaderSource = ReadShader(m_strFullPath);
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
					std::cerr << m_strFullPath << " shader compile log : " << std::endl;
					std::cerr << szLog << std::endl;
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

	protected:
		bool m_bIsCompiled;
		ShaderType m_shaderType;
		std::string m_strFullPath;
		GLuint m_shaderObject;
		bool m_bValid;
	private:
	};
}
#endif // CMRShader_h__
