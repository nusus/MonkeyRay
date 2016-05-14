#ifndef CMRUniform_h__
#define CMRUniform_h__

#include "CMRRef.h"
#include "CMRProgram.h"
namespace MR
{
	extern void aux_glUniform1fv(GLint location, GLsizei count, const GLfloat* value);
	extern void aux_glUniform2fv(GLint location, GLsizei count, const GLfloat* value);
	extern void aux_glUniform3fv(GLint location, GLsizei count, const GLfloat* value);
	extern void aux_glUniform1iv(GLint location, GLsizei count, const GLint* value);
	extern void aux_glUniformMatrix4fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat* value);

	class CMRUniformRef : public CMRRef
	{
	public:
		explicit CMRUniformRef(const string& name);
		CMRUniformRef(const CMRUniformRef& rhs);
		CMRUniformRef& operator=(const CMRUniformRef& rhs);

	public:
		void Apply(const CMRProgram* pProgram);

		virtual void ApplyImpl(GLint uniformLocation) = 0;

		void SetUniformName(const string& name) { m_strUniformName = name; }
		string GetUniformName() const { return m_strUniformName; }

		virtual void Update() {}

	protected:
		virtual ~CMRUniformRef() {}


	protected:
		string m_strUniformName;
	};

	template<typename T, const size_t N, const size_t count = 1 >
	class CMRUniformBase : public CMRUniformRef
	{
	public:
		typedef T value_type[N * count];


	public:
		explicit CMRUniformBase(const string& strName)
			:CMRUniformRef(strName)
		{
			SetData(0);
		}
		CMRUniformBase(const string& strName, value_type val)
			:CMRUniformRef(strName)
		{
			SetData(val);
		}
		CMRUniformBase(const CMRUniformBase& rhs) :
			CMRUniformRef(rhs)
		{
			SetData(rhs.m_val);
		}
		CMRUniformBase& operator=(const CMRUniformBase& rhs)
		{
			if (this == &rhs)
			{
				return *this;
			}
			CMRUniformRef::operator=(rhs);
			SetData(rhs.m_val);
		}


	public:
		void SetData(value_type val)
		{
			memcpy(m_val, val, sizeof(T) * N * count);
		}

		T* GetData() const
		{
			return &m_val[0];
		}

	protected:
		virtual ~CMRUniformBase() {}


	protected:	
		value_type m_val;
	};

	template<typename T, const size_t N, void M(GLint, GLsizei, const T*), const size_t count = 1 >
	class CMRUniformfi : public CMRUniformBase<T, N, count>
	{
	public:
		explicit CMRUniformfi(const string& strName):
			CMRUniformBase(strName)
		{}
		CMRUniformfi(const string& strName, value_type val):
			CMRUniformBase(strName, val)
		{}


	public:
		virtual void ApplyImpl(GLint uni_loc) override
		{
			M(uni_loc, count, m_val);
		}

	protected:
		virtual ~CMRUniformfi() {}
	};


	template<typename T, const size_t N, void M(GLint, GLsizei, GLboolean, const T*), const size_t count = 1 >
	class CMRUniformMatrix : public CMRUniformBase<T, N, count>
	{
	public:
		explicit CMRUniformMatrix(const string& strName):
			CMRUniformBase(strName)
		{}

		CMRUniformMatrix(const string& strName, value_type val):
			CMRUniformBase(strName, val)
		{}


	public:
		virtual void ApplyImpl(GLint uni_loc) override
		{
			M(uni_loc, count, false, m_val);
		}

	protected:
		virtual ~CMRUniformMatrix() {}
	};

	typedef CMRUniformfi<GLfloat, 1, aux_glUniform1fv> CMRUniform1fv;
	typedef CMRUniformfi<GLfloat, 2, aux_glUniform2fv> CMRUniform2fv;
	typedef CMRUniformfi<GLfloat, 3, aux_glUniform3fv> CMRUniform3fv;
	typedef CMRUniformfi<GLint, 1, aux_glUniform1iv> CMRUniform1iv;
	typedef CMRUniformMatrix<GLfloat, 16, aux_glUniformMatrix4fv> CMRUniformMatrix4fv;

}
#endif // CMRUniform_h__
