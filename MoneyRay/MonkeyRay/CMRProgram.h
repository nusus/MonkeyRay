#ifndef CMRProgram_h__
#define CMRProgram_h__
#include "CMRPrerequisites.h"
#include "CMRShader.h"
#include "SmartPtr.h"
#include <utility>
#include "CMRUniform.h"
namespace MR
{
	class CMRProgram : public CMRRef
	{
	public:
		CMRProgram()
			:m_bReady(false),
			m_programObject(0),
			m_shaders()
		{

		}

		~CMRProgram()
		{
			DestroyProgram();
		}

		void CompileAndAttachAllShaders(GLuint programObject)
		{
			for (auto shader : m_shaders)
			{
				if (shader.Valid() && !shader->IsCompiled())
				{
					shader->CompileShader();
					glAttachShader(programObject, shader->GetShaderObject());
				}
			}
		}

		bool InitProgram()
		{
			if (IsReady())
			{
				return true;
			}
			if (m_programObject == 0)
			{
				m_programObject = glCreateProgram();
			}

			if (!m_programObject)
			{
				CMR_STD_ERROR << "Error : create program failed" << CMR_STD_ENDL;
				exit(1);
			}
			CompileAndAttachAllShaders(m_programObject);

			glLinkProgram(m_programObject);

			GLint linkStatus;
			glGetProgramiv(m_programObject, GL_LINK_STATUS, &linkStatus);
			if (GL_TRUE != linkStatus)
			{
				CMR_STD_ERROR << "Error : link shader program failed " << CMR_STD_ENDL;
				GLint logLen;
				glGetProgramiv(m_programObject, GL_INFO_LOG_LENGTH, &logLen);
				if (logLen > 0)
				{
					char* szLog = (char*)malloc(sizeof(char) * logLen);
					GLsizei written;
					glGetProgramInfoLog(m_programObject, logLen, &written, szLog);
					CMR_STD_ERROR << "Program log : " << CMR_STD_ENDL;
					CMR_STD_ERROR << szLog << CMR_STD_ENDL;
				}
			}
			else
			{
				m_bReady = true;
			}
			return m_bReady;
		}

		void UseProgram()
		{
			glUseProgram(m_programObject);
		}

		bool IsReady() const
		{
			return m_bReady;
		}

		void DestroyProgram()
		{
			m_programObject = 0;
			glDeleteProgram(m_programObject);
			glUseProgram(0);

		}

		GLuint GetProgramObject() const
		{
			return m_programObject;
		}

		void AddShader(CMRShader* shader)
		{
			m_shaders.insert(shader);
		}

		void SetShaderSet(const CMRShader::ShaderSet& shaderSet)
		{
			m_shaders = shaderSet;
		}

		void Uniformli(const string& sampler_name, unsigned int binding_point)
		{
			//UseProgram();
			GLint tex_obj_loc = glGetUniformLocation(m_programObject, sampler_name.c_str());
			glUniform1i(tex_obj_loc, binding_point);
		}

		void UniformMatrix4fv(const string& uniform_name, const vmath::mat4& matrix)
		{
			//UseProgram();
			GLint uni_matrix_loc = glGetUniformLocation(m_programObject, uniform_name.c_str());
			glUniformMatrix4fv(uni_matrix_loc, 1, GL_FALSE, matrix);
		}


		void ApplyUniform(CMRUniformBase& uniform)
		{
			uniform.Apply(this);
		}
	protected:
		bool m_bReady;
		GLuint m_programObject;
		typedef CMRShader::ShaderSet  Shaders;
		Shaders m_shaders;
	};
}
#endif // CMRProgram_h__
