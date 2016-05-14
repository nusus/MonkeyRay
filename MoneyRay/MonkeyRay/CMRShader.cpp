#include "CMRShader.h"

using namespace MR;

MR::CMRShader::CMRShader(ShaderType type, const string& strFileName) :m_bIsCompiled(false),
m_shaderType(type),
m_strFullPath(CMRConfig::Instance()->s_strShaderDir + strFileName),
m_bValid(false)
{

}

MR::CMRShader::~CMRShader()
{
	DestroyShader();
}

bool MR::CMRShader::IsCompiled() const
{
	return m_bIsCompiled;
}

MR::string MR::CMRShader::GetFileName() const
{
	return CMRFile::GetFileNameAux(m_strFullPath);
}

MR::CMRShader::ShaderType MR::CMRShader::GetShaderType() const
{
	return m_shaderType;
}

MR::string MR::CMRShader::ReadShader(const string& strShaderName)
{
	return CMRFile::ReadFile(strShaderName);
}

void MR::CMRShader::CreateShader()
{
	m_shaderObject = glCreateShader(m_shaderType);
	if (0 == m_shaderObject)
	{
		CMR_STD_ERROR << "Error : Create " << m_strFullPath << " shader failed" << CMR_STD_ENDL;
		assert(false);
	}
	m_bValid = true;
}

bool MR::CMRShader::IsValid() const
{
	return m_bValid;
}

void MR::CMRShader::CompileShader()
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
		assert(false);
	}
	else
	{
		m_bIsCompiled = true;
	}
}

GLuint MR::CMRShader::GetShaderObject() const
{
	return m_shaderObject;
}

void MR::CMRShader::DestroyShader()
{
	if (m_shaderObject != 0)
	{
		glDeleteShader(m_shaderObject);
	}
	m_shaderObject = 0;
	m_bValid = false;
	m_bIsCompiled = false;
}

int MR::CMRShader::GetShaderIndex() const
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
	return -1;
}

bool MR::CMRShader::ShaderSort::operator()(const SmartPtr<CMRShader>& lhs, const SmartPtr<CMRShader> rhs)
{
	if (lhs->GetFileName() == rhs->GetFileName() || lhs->GetShaderType() == rhs->GetShaderType())
	{
		return false;
	}
	return lhs->GetShaderIndex() < rhs->GetShaderIndex();
}
