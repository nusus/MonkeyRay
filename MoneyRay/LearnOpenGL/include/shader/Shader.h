#pragma once
#ifndef Shader_h__
#define Shader_h__

// GLEW
#define GLEW_STATIC
#include <GL/glew.h>
// GLFW
#include <GLFW/glfw3.h>

#include <string>
#include <fstream>
#include <sstream>
#include <cassert>

namespace LOGL
{
	template<GLuint ShaderType>
	class Shader
	{
	public:
		Shader()
			:m_Shader(0)
		{

		}

		Shader(const std::string& path)
			:m_Shader(0)
		{
			Init(path);
		}

		~Shader()
		{
			if (m_Shader != 0)
			{
				DeleteShader();
			}
		}

		GLuint GetShader() const
		{
			return m_Shader;
		}

		void DeleteShader()
		{
			glDeleteShader(m_Shader);
			m_Shader = 0;
		}

		void Init(const std::string& path)
		{
			//read shader file
			std::string shaderCode;
			std::ifstream shaderFile;
			shaderFile.exceptions(std::ifstream::badbit);
			try
			{
				shaderFile.open(path);
				std::stringstream shaderStream;
				shaderStream << shaderFile.rdbuf();
				shaderFile.close();
				shaderCode = shaderStream.str();
			}
			catch (std::ifstream::failure e)
			{
				std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ\n" << std::endl;
			}

			//compile shader
			GLint success;
			GLchar infoLog[512];
			m_Shader = glCreateShader(ShaderType);
			const char* szShaderCode = shaderCode.c_str();
			glShaderSource(m_Shader, 1, &szShaderCode, NULL);
			glCompileShader(m_Shader);
			glGetShaderiv(m_Shader, GL_COMPILE_STATUS, &success);
			if (!success)
			{
				glGetShaderInfoLog(m_Shader, 512, NULL, infoLog);
				std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
				assert(false);
			}
		}
		void InitTest(const std::string& path)
		{
			//compile shader
			GLint success;
			GLchar infoLog[512];
			m_Shader = glCreateShader(ShaderType);
			char* szShaderCode;
			if (ShaderType == GL_VERTEX_SHADER)
			{
				szShaderCode = "#version 330 core\n"
					"layout (location = 0) in vec3 position;\n"
					"void main()\n"
					"{\n"
					"gl_Position = vec4(position.x, position.y, position.z, 1.0);\n"
					"}\0";
			}
			if (ShaderType == GL_FRAGMENT_SHADER)
			{
				szShaderCode = "#version 330 core\n"
					"out vec4 color;\n"
					"void main()\n"
					"{\n"
					"color = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
					"}\n\0";
			}		
			glShaderSource(m_Shader, 1, &szShaderCode, NULL);
			glCompileShader(m_Shader);
			glGetShaderiv(m_Shader, GL_COMPILE_STATUS, &success);
			if (!success)
			{
				glGetShaderInfoLog(m_Shader, 512, NULL, infoLog);
				std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
				assert(false);
			}
		}

		bool IsReady() const 
		{
			return m_Shader != 0;
		}

	protected:
		GLuint m_Shader;
	};

	class VertexShader : public Shader<GL_VERTEX_SHADER>
	{
	public:
		VertexShader()
			:Shader()
		{}

		VertexShader(const std::string& path)
			:Shader(path)
		{

		}
	};

	class FragmentShader : public Shader<GL_FRAGMENT_SHADER>
	{
	public:
		FragmentShader()
			:Shader()
		{}

		FragmentShader(const std::string& path)
			:Shader(path)
		{}
	};
}
#endif // Shader_h__