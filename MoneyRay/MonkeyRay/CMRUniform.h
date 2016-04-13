#ifndef CMRUniform_h__
#define CMRUniform_h__
#include "CMRPrerequisites.h"
#include "CMRRef.h"
#include "CMRProgram.h"
namespace MR
{

	class CMRUniformBase : public CMRRef
	{
		virtual void Apply(CMRProgram* pProgram) = 0;
	};

	template<typename T, const size_t N, void M(GLint, GLsizei, const T*), const size_t count = 1 >
	class CMRUniformfi : public CMRUniformBase
	{
	public:
		typedef T value_type[N * count];
	public:
		CMRUniformfi(const string& strName, value_type val) :
			m_strUniformName(strName)
		{
			memcpy(m_val, val, sizeof(T) * N * count);
		}

		virtual void Apply(CMRProgram* pProgram) override
		{
			GLint uni_loc = glGetUniformLocation(pProgram->GetProgramObject(), m_strUniformName.c_str());
			M(uni_loc, count, m_val);
		}
	protected:
		string m_strUniformName;
		value_type m_val;
	};


	template<typename T, const size_t N, void M(GLint, GLsizei, GLboolean, const T*), const size_t count = 1 >
	class CMRUniformMatrix : public CMRUniformBase
	{
	public:
		typedef T value_type[N * N * count];
	public:
		CMRUniformMatrix(const string& strName, value_type val) :
			m_strUniformName(strName)
		{
			memcpy(m_val, val, sizeof(T) * N * N * count);
		}

		virtual void Apply(CMRProgram* pProgram) override
		{
			//here we send the uniform matrix data to the OpenGL program without transpose.  
			GLint uni_loc = glGetUniformLocation(pProgram->GetProgramObject(), m_strUniformName.c_str());
			M(uni_loc, count, false, m_val);
		}
	protected:
		string m_strUniformName;
		value_type m_val;
	};


	void aux_glUniform1fv(GLint location, GLsizei count, const GLfloat* value)
	{
		glUniform1fv(location, count, value);
	}
	typedef CMRUniformfi<GLfloat, 1, aux_glUniform1fv> CMRUniform1fv;

	void aux_glUniform2fv(GLint location, GLsizei count, const GLfloat* value)
	{
		glUniform2fv(location, count, value);
	}
	typedef CMRUniformfi<GLfloat, 2, aux_glUniform2fv> CMRUniform2fv;

	void aux_glUniform3fv(GLint location, GLsizei count, const GLfloat* value)
	{
		glUniform3fv(location, count, value);
	}
	typedef CMRUniformfi<GLfloat, 3, aux_glUniform3fv> CMRUniform3fv;

	void aux_glUniform1iv(GLint location, GLsizei count, const GLint* value)
	{
		glUniform1iv(location, count, value);
	}
	typedef CMRUniformfi<GLint, 1, aux_glUniform1iv> CMRUniform1iv;

	void aux_glUniformMatrix4fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat* value)
	{
		glUniformMatrix4fv(location, count, transpose, value);
	}
	typedef CMRUniformMatrix<GLfloat, 4, aux_glUniformMatrix4fv> CMRUniformMatrix4fv;
}
#endif // CMRUniform_h__
