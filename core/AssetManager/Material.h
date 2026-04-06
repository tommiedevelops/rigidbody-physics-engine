#pragma once

#include "texture.h"
#include "shader.h"

namespace PhysicsEngine
{
	class Material
	{
		float albedo;
		float diffuse;
		float specular;

		Texture* tex;
		Shader*  shader;

	};
}
