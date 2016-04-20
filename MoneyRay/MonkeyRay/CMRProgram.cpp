#include "CMRProgram.h"
#include "CMRUniform.h"

using namespace MR;

MR::CMRProgram::CMRProgram() :m_bReady(false),
m_programObject(0),
m_shaders()
{

}

MR::CMRProgram::~CMRProgram()
{
	DestroyProgram();
}

void MR::CMRProgram::CompileAndAttachAllShaders(GLuint programObject)
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

bool MR::CMRProgram::InitProgram()
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

void MR::CMRProgram::UseProgram()
{
	glUseProgram(m_programObject);
}

bool MR::CMRProgram::IsReady() const
{
	return m_bReady;
}

void MR::CMRProgram::DestroyProgram()
{
	glDeleteProgram(m_programObject);
	glUseProgram(0);
}

GLuint MR::CMRProgram::GetProgramObject() const
{
	return m_programObject;
}

void MR::CMRProgram::AddShader(CMRShader* shader)
{
	m_shaders.insert(shader);
}

void MR::CMRProgram::SetShaderSet(const CMRShader::ShaderSet& shaderSet)
{
	m_shaders = shaderSet;
}

void MR::CMRProgram::Accept(CMRUniformRef& uniform)
{
	uniform.Apply(this);
}
