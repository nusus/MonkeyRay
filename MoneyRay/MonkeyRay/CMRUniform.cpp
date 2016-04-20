#include "CMRUniform.h"

using namespace MR;

void MR::CMRUniformRef::Apply(const CMRProgram* pProgram)
{
	GLint uni_loc = glGetUniformLocation(pProgram->GetProgramObject(), m_strUniformName.c_str());
	ApplyImpl(uni_loc);
}

template<typename T, const size_t N, const size_t count /*= 1 */>
T* MR::CMRUniformBase<T, N, count>::GetData() const
{
	return &m_val[0];
}

template<typename T, const size_t N, const size_t count /*= 1 */>
void MR::CMRUniformBase<T, N, count>::SetData(value_type val)
{
	memcpy(m_val, val, sizeof(T) * N * count);
}

template<typename T, const size_t N, const size_t count /*= 1 */>
MR::CMRUniformBase<T, N, count>::CMRUniformBase(const string& strName, value_type val) :
	m_strUniformName(strName)
{
	memcpy(m_val, val, sizeof(T) * N * count);
}

template<typename T, const size_t N, const size_t count /*= 1 */>
MR::CMRUniformBase<T, N, count>::CMRUniformBase(const string& strName) :
	m_strUniformName(strName)
{
	memset(m_val, 0, sizeof(T) * N * count);
}

template<typename T, const size_t N, void M(GLint, GLsizei, const T*), const size_t count /*= 1 */>
void MR::CMRUniformfi<T, N, M, count>::ApplyImpl( GLint uni_loc )
{
	M(uni_loc, count, m_val);
}

template<typename T, const size_t N, void M(GLint, GLsizei, const T*), const size_t count /*= 1 */ >
 MR::CMRUniformfi<T, N, M, count>::CMRUniformfi( const string& strName, value_type val ) :
			CMRUniformBase(strName, val)
{

}

template<typename T, const size_t N, void M(GLint, GLsizei, const T*), const size_t count /*= 1 */ >
 MR::CMRUniformfi<T, N, M, count>::CMRUniformfi( const string& strName ) :CMRUniformBase(strName)
{

}

template<typename T, const size_t N, void M(GLint, GLsizei, GLboolean, const T*), const size_t count /*= 1 */ >
void MR::CMRUniformMatrix<T, N, M, count>::ApplyImpl( GLint uni_loc )
{
	M(uni_loc, count, false, m_val);
}

template<typename T, const size_t N, void M(GLint, GLsizei, GLboolean, const T*), const size_t count /*= 1 */ >
 MR::CMRUniformMatrix<T, N, M, count>::CMRUniformMatrix( const string& strName, value_type val ) :CMRUniformBase(strName, val)
{

}

template<typename T, const size_t N, void M(GLint, GLsizei, GLboolean, const T*), const size_t count /*= 1 */ >
 MR::CMRUniformMatrix<T, N, M, count>::CMRUniformMatrix( const string& strName ) :CMRUniformBase(strName)
{
}
