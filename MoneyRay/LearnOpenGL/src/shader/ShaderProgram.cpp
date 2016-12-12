#include "shader/ShaderProgram.h"



LOGL::ShaderProgram::ShaderProgram(const std::string& vertexShader, const std::string& fragmentShader) :m_VertexShader(vertexShader),
m_FragmentShader(fragmentShader),
m_Program(0)
{

}

LOGL::ShaderProgram::ShaderProgram() :m_VertexShader(),
m_FragmentShader(),
m_Program(0)
{

}

void LOGL::ShaderProgram::AddVertexShader(const std::string& path)
{
	m_VertexShader.Init(path);
}

void LOGL::ShaderProgram::AddFragmentShader(const std::string& path)
{
	m_FragmentShader.Init(path);
}

GLuint LOGL::ShaderProgram::GetProgram() const
{
	return m_Program;
}

void LOGL::ShaderProgram::CompileProgram()
{
	//make sure vertex shader and fragment shader are both ready!
	if (!(m_VertexShader.IsReady() && m_FragmentShader.IsReady()))
	{
		return;
	}
	//create and compile vertex shader and fragment shader
	m_Program = glCreateProgram();
	glAttachShader(m_Program, m_VertexShader.GetShader());
	glAttachShader(m_Program, m_FragmentShader.GetShader());
	glLinkProgram(m_Program);

	//check program
	GLint success;
	GLchar infoLog[512];
	glGetProgramiv(m_Program, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(m_Program, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
		assert(false);
	}
	m_VertexShader.DeleteShader();
	m_FragmentShader.DeleteShader();
}

void LOGL::ShaderProgram::Use()
{
	if (!IsReady())
	{
		CompileProgram();
	}
	glUseProgram(m_Program);
}

bool LOGL::ShaderProgram::IsReady() const
{
	return m_Program != 0;
}
