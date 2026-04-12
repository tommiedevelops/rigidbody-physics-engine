#pragma once
#include <string>
#include <glm/glm.hpp>

namespace PhysicsEngine
{
	class Shader
	{
	private:
		unsigned int m_ID;
	public:
		Shader(const std::string vertexPath,const std::string fragmentPath);

		void Bind(); // activate the shader

		void SetBoolUniform(const std::string& name, bool value) const;
		void SetIntUniform(const std::string& name, int value) const;
		void SetFloatUniform(const std::string& name, float value) const;
		void SetVec3Uniform(const std::string& name, glm::vec3 value) const;

		unsigned int GetID() { return m_ID; }
	};
}
