#include "CMRUniform.h"

using namespace MR;

CMRUniformRef& MR::CMRUniformRef::operator=(const CMRUniformRef& rhs)
{
	if (this == &rhs)
	{
		return *this;
	}
	m_strUniformName = rhs.m_strUniformName;
	return *this;
}

MR::CMRUniformRef::CMRUniformRef(const string& name) :
	m_strUniformName(name)
{

}

MR::CMRUniformRef::CMRUniformRef(const CMRUniformRef& rhs) :m_strUniformName(rhs.m_strUniformName)
{

}

void MR::CMRUniformRef::Apply(const CMRProgram* pProgram)
{
	GLint uni_loc = glGetUniformLocation(pProgram->GetProgramObject(), m_strUniformName.c_str());
	ApplyImpl(uni_loc);
}

 void MR::aux_glUniform1fv(GLint location, GLsizei count, const GLfloat* value)
 {
	 glUniform1fv(location, count, value);
 }

 void MR::aux_glUniform2fv(GLint location, GLsizei count, const GLfloat* value)
 {
	 glUniform2fv(location, count, value);
 }

 void MR::aux_glUniform3fv(GLint location, GLsizei count, const GLfloat* value)
 {
	 glUniform3fv(location, count, value);
 }

 void MR::aux_glUniform1iv(GLint location, GLsizei count, const GLint* value)
 {
	 glUniform1iv(location, count, value);
 }

 void MR::aux_glUniformMatrix4fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat* value)
 {
	 glUniformMatrix4fv(location, count, transpose, value);
 }
