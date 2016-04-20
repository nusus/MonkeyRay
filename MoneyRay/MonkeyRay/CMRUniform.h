#ifndef CMRUniform_h__
#define CMRUniform_h__

#include "CMRRef.h"
#include "CMRProgram.h"
namespace MR
{
	class CMRUniformRef : public CMRRef
	{
	public:
		void Apply(const CMRProgram* pProgram);

		virtual void ApplyImpl(GLint uniformLocation) = 0;
	protected:
		string m_strUniformName;
	};

	template<typename T, const size_t N, const size_t count = 1 >
	class CMRUniformBase : public CMRUniformRef
	{
	public:
		typedef T value_type[N * count];
	public:
		explicit CMRUniformBase(const string& strName);
		CMRUniformBase(const string& strName, value_type val);

		void SetData(value_type val);

		T* GetData() const;
	protected:
		
		value_type m_val;
	};

	template<typename T, const size_t N, void M(GLint, GLsizei, const T*), const size_t count = 1 >
	class CMRUniformfi : public CMRUniformBase<T, N, count>
	{

	public:

		CMRUniformfi(const string& strName);

		CMRUniformfi(const string& strName, value_type val);
		virtual void ApplyImpl(GLint uni_loc) override;
	};


	template<typename T, const size_t N, void M(GLint, GLsizei, GLboolean, const T*), const size_t count = 1 >
	class CMRUniformMatrix : public CMRUniformBase<T, N, count>
	{
	public:
		CMRUniformMatrix(const string& strName);

		CMRUniformMatrix(const string& strName, value_type val);

		virtual void ApplyImpl(GLint uni_loc) override;
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
	typedef CMRUniformMatrix<GLfloat, 16, aux_glUniformMatrix4fv> CMRUniformMatrix4fv;
}
#endif // CMRUniform_h__
