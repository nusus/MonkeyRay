#pragma once
#ifndef ShaderProgram_h__
#define ShaderProgram_h__
#include "Shader.h"
#include <iostream>

namespace LOGL
{
	class ShaderProgram
	{
	public:
		ShaderProgram();

		ShaderProgram(const std::string& vertexShader, const std::string& fragmentShader);

		void AddVertexShader(const std::string& path);

		void AddFragmentShader(const std::string& path);

		GLuint GetProgram() const;

		void CompileProgram();

		void Use();

		bool IsReady() const;
		
	protected:
		VertexShader m_VertexShader;
		FragmentShader m_FragmentShader;
		
		GLuint m_Program;
	private:
	};
}
#endif // ShaderProgram_h__