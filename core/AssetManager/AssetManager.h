#pragma once

#include <vector>
#include <string>
#include <memory>
#include <unordered_map>

namespace PhysicsEngine
{
	class Mesh;
	class Shader;
	class Texture;
	class Material;

	class AssetManager
	{
	private:
		std::unordered_map<std::string, std::shared_ptr<Mesh>>     m_Meshes;
		std::unordered_map<std::string, std::shared_ptr<Shader>>   m_Shaders;
		std::unordered_map<std::string, std::shared_ptr<Texture>>  m_Textures;
		std::unordered_map<std::string, std::shared_ptr<Material>> m_Materials;
	public:
		std::shared_ptr<Mesh>     LoadMesh(const std::string& path);
		std::shared_ptr<Shader>   LoadShader(const std::string& vertexPath, const std::string& fragmentPath);
		std::shared_ptr<Texture>  LoadTexture(const std::string& path);
		std::shared_ptr<Material> CreateMaterial(const std::string& name, std::shared_ptr<Shader> shader, std::shared_ptr<Texture> texture);
		std::unique_ptr<Material> CreateMaterial(std::shared_ptr<Shader> shader, std::shared_ptr<Texture> texture);
		std::shared_ptr<Material> GetMaterial(const std::string& name);
	};
}