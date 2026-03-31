#pragma once
#include <string>

namespace PhysicsEngine
{
	class Shader
	{
	private:
		unsigned int m_ID;
	public:

		Shader(const char* vertexPath, const char* fragmentPath);

		void use(); // activate the shader

		void setBoolUniform(const std::string& name, bool value) const;
		void setIntUniform(const std::string& name, int value) const;
		void setFloatUniform(const std::string& name, float value) const;

	};
}
