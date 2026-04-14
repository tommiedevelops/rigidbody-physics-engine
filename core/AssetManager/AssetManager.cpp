#include "AssetManager.h"
#include "Mesh.h"
#include "Shader.h"
#include "Texture.h"
#include "Material.h"

#include <iostream>
#include <string>

namespace PhysicsEngine
{
	std::shared_ptr<Mesh> 
	AssetManager::LoadMesh(const std::string& path)
	{
		// Check if already imported
		auto it{ m_Meshes.find(path) };
		if (it != m_Meshes.end())
			return it->second; // return cached mesh

		auto mesh{ std::make_shared<Mesh>(path) };
		m_Meshes.emplace(path, mesh);

		return mesh;
	}

	std::shared_ptr<Shader> 
	AssetManager::LoadShader(const std::string& vertexPath, const std::string& fragmentPath)
	{
		auto it{ m_Shaders.find(vertexPath + fragmentPath) };
		
		if (it != m_Shaders.end())
			return it->second; // return cached mesh

		auto shader{ std::make_shared<Shader>(vertexPath, fragmentPath) };
		m_Shaders.emplace(vertexPath + fragmentPath, shader);

		return shader;
	}

	std::shared_ptr<Texture> 
	AssetManager::LoadTexture(const std::string& path)
	{
		auto it{ m_Textures.find(path) };

		if (it != m_Textures.end())
			return it->second; // return cached mesh

		auto texture{ std::make_shared<Texture>(path) };
		m_Textures.emplace(path, texture);

		return texture;
	}
	std::shared_ptr<Material> 
	AssetManager::CreateMaterial(const std::string& name, std::shared_ptr<Shader> shader, std::shared_ptr<Texture> texture)
	{
		auto it{ m_Materials.find(name) };

		if (it != m_Materials.end())
			return it->second;
		
		auto material{ std::make_shared<Material>(shader, texture) };
		m_Materials.emplace(name, material);

		return material;
	}
	std::unique_ptr<Material> 
	AssetManager::CreateMaterial(std::shared_ptr<Shader> shader, std::shared_ptr<Texture> texture)
	{
		auto material{ std::make_unique<Material>(shader, texture) };
		return material;
	}

	std::shared_ptr<Material>
	AssetManager::GetMaterial(const std::string& name)
	{
		return std::shared_ptr<Material>();
	}
}