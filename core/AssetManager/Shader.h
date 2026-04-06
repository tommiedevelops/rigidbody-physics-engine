#pragma once
#include <string>

namespace PhysicsEngine
{
	class Shader
	{
	private:
		unsigned int m_ID;
		std::string  m_Name;
	public:
		Shader(
			std::string vertexPath,
			std::string fragmentPath,
			std::string shaderName
		);

		void use(); // activate the shader

		void setBoolUniform(const std::string& name, bool value) const;
		void setIntUniform(const std::string& name, int value) const;
		void setFloatUniform(const std::string& name, float value) const;

	};
}
