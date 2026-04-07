#pragma once
#include <string>
#include <glm/glm.hpp>

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

		void Bind(); // activate the shader

		void SetBoolUniform(const std::string& name, bool value) const;
		void SetIntUniform(const std::string& name, int value) const;
		void SetFloatUniform(const std::string& name, float value) const;
		void SetVec3Uniform(const std::string& name, glm::vec3 value) const;

		std::string& GetName()
		{
			return m_Name;
		}
		unsigned int GetID() { return m_ID; }
	};
}
