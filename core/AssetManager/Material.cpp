#include "Material.h"

namespace PhysicsEngine
{
	Material::Material(std::string materialName, Shader* shader, Texture* texture)
		: m_Name    { materialName }
		, m_Texture { texture      }
		, m_Shader  { shader       }
	{ }

	std::string& Material::GetName()
	{
		return m_Name;
	}
}