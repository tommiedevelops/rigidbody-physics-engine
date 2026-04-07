#include "shader.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <filesystem>
#include <glm/glm.hpp>

#include <GLAD/glad.h>

namespace PhysicsEngine
{
	void Shader::Bind()
	{
		glUseProgram(m_ID);
	}

	void Shader::SetBoolUniform(const std::string& name, bool value) const
	{
		glUniform1i(glGetUniformLocation(m_ID, name.c_str()), (int)value);
	}

	void Shader::SetIntUniform(const std::string& name, int value) const
	{
		glUniform1i(glGetUniformLocation(m_ID, name.c_str()), value);
	}

	void Shader::SetFloatUniform(const std::string& name, float value) const
	{
		glUniform1f(glGetUniformLocation(m_ID, name.c_str()), value);
	}

	void Shader::SetVec3Uniform(const std::string& name, glm::vec3 value) const
	{
		glUniform3f(glGetUniformLocation(m_ID, name.c_str()), value.x, value.y, value.z);
	}

	/* Constructor */
	Shader::Shader(
		std::string vertexPath,
		std::string fragmentPath,
		std::string shaderName
	)
		: m_ID    { glCreateProgram() }
		, m_Name  { shaderName }
	{
		std::string vertexCode;
		std::string fragmentCode;

		std::ifstream vShaderFile;
		std::ifstream fShaderFile;

		vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
		fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

		try
		{
			vShaderFile.open(vertexPath.c_str());
			fShaderFile.open(fragmentPath.c_str());

			std::stringstream vShaderStream, fShaderStream;

			vShaderStream << vShaderFile.rdbuf();
			fShaderStream << fShaderFile.rdbuf();

			vShaderFile.close();
			fShaderFile.close();

			vertexCode = vShaderStream.str();
			fragmentCode = fShaderStream.str();
		}
		catch (std::ifstream::failure e)
		{
			std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
			std::cout << "CWD = " << std::filesystem::current_path() << std::endl;
		}

		const char* vShaderCode = vertexCode.c_str();
		const char* fShaderCode = fragmentCode.c_str();

		// shader compilation

		int success;
		char infoLog[512];

		// compile vertex shader
		unsigned int vertShader{ glCreateShader(GL_VERTEX_SHADER) };

		glShaderSource(vertShader, 1, &vShaderCode, NULL);
		glCompileShader(vertShader);

		glGetShaderiv(vertShader, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(vertShader, 512, NULL, infoLog);
			std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED" << infoLog << std::endl;
		}

		// compile fragment shader

		unsigned int fragShader{ glCreateShader(GL_FRAGMENT_SHADER) };

		glShaderSource(fragShader, 1, &fShaderCode, NULL);
		glCompileShader(fragShader);

		glGetShaderiv(fragShader, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(fragShader, 512, NULL, infoLog);
			std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED" << infoLog << std::endl;
		}

		// Link Shaders
		glAttachShader(m_ID, vertShader);
		glAttachShader(m_ID, fragShader);
		glLinkProgram(m_ID);
		glGetProgramiv(m_ID, GL_LINK_STATUS, &success);

		if (!success)
		{
			glGetProgramInfoLog(m_ID, 512, NULL, infoLog);
			std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n";
		}

		glDeleteShader(vertShader);
		glDeleteShader(fragShader);
	}
}