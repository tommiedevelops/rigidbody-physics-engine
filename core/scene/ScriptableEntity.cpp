#include "ScriptableEntity.h"

#include "AssetManager.h"
#include "Scene.h"
#include "Mesh.h"
#include "Texture.h"
#include "Material.h"

namespace PhysicsEngine
{	

	std::shared_ptr<Mesh>     ScriptableEntity::LoadMesh(const std::string& path)
	{
		if (!m_Scene) return nullptr;
		return m_Scene->GetAssetsRef()->LoadMesh(path);
	}

	std::shared_ptr<Shader>   ScriptableEntity::LoadShader(const std::string& vertexPath, const std::string& fragmentPath)
	{
		if (!m_Scene) return nullptr;
		return m_Scene->GetAssetsRef()->LoadShader(vertexPath, fragmentPath);
	}

	std::shared_ptr<Texture>  ScriptableEntity::LoadTexture(const std::string& path)
	{
		if (!m_Scene) return nullptr;
		return m_Scene->GetAssetsRef()->LoadTexture(path);
	}

	std::shared_ptr<Material> ScriptableEntity::CreateMaterial(const std::string& name, std::shared_ptr<Shader> shader, std::shared_ptr<Texture> texture)
	{
		if (!m_Scene) return nullptr;
		return m_Scene->GetAssetsRef()->CreateMaterial(name, shader, texture);
	}
	std::unique_ptr<Material> ScriptableEntity::CreateMaterial(std::shared_ptr<Shader> shader, std::shared_ptr<Texture> texture)
	{	
		if (!m_Scene) return nullptr;
		return m_Scene->GetAssetsRef()->CreateMaterial(shader, texture);
	}


	std::shared_ptr<Material> ScriptableEntity::GetMaterial(const std::string& name)
	{
		if (!m_Scene) return nullptr;
		return m_Scene->GetAssetsRef()->GetMaterial(name);
	}

}