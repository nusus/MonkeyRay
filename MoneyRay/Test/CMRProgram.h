#ifndef CMRProgram_h__
#define CMRProgram_h__
#include "CGlobalInclude.h"
#include <iostream>
#include <vector>
#include "CMRShader.h"
namespace MR
{
	class CMRProgram
	{
	public:
		CMRProgram()
			:m_bReady(false),
			m_programObject(0)
		{

		}

		~CMRProgram()
		{
			for (auto pShader : m_pShaders)
			{
				if (pShader)
				{
					delete pShader;
				}
			}
			DestroyProgram();
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
				std::cerr << "Error : create program failed" << std::endl;
				exit(1);
			}
			for (auto shader : m_pShaders)
			{
				if (!shader->IsCompiled())
				{
					shader->CompileShader();
				}
				glAttachShader(m_programObject, shader->GetShaderObject());
			}

			glLinkProgram(m_programObject);

			GLint linkStatus;
			glGetProgramiv(m_programObject, GL_LINK_STATUS, &linkStatus);
			if (GL_TRUE != linkStatus)
			{
				std::cerr << "Error : link shader program failed " << std::endl;
				GLint logLen;
				glGetProgramiv(m_programObject, GL_INFO_LOG_LENGTH, &logLen);
				if (logLen > 0)
				{
					char* szLog = (char*)malloc(sizeof(char) * logLen);
					GLsizei written;
					glGetProgramInfoLog(m_programObject, logLen, &written, szLog);
					std::cerr << "Program log : " << std::endl;
					std::cerr << szLog << std::endl;
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
			m_pShaders.push_back(shader);
		}

		void Uniformli(const std::string& sampler_name, unsigned int binding_point)
		{
			//UseProgram();
			GLint tex_obj_loc = glGetUniformLocation(m_programObject, sampler_name.c_str());
			glUniform1i(tex_obj_loc, binding_point);
		}

		void UniformMatrix4fv(const std::string& uniform_name, const vmath::mat4& matrix)
		{
			//UseProgram();
			GLint uni_matrix_loc = glGetUniformLocation(m_programObject, uniform_name.c_str());
			glUniformMatrix4fv(uni_matrix_loc, 1, GL_FALSE, matrix);
		}
	protected:
		bool m_bReady;
		GLuint m_programObject;
		std::vector<CMRShader*> m_pShaders;
	};
}
#endif // CMRProgram_h__
