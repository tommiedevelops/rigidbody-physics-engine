#ifndef SCENE_H
#define SCENE_H

#include "glm/glm.hpp"

#include "Entity.h"

#include <vector>


// This is where I implement ECS

class Scene
{
public:
	Scene()  = default;
	~Scene() = default;

	Entity CreateEntity();

	entt::registry& GetRegistry() { return m_registry;  }
	const entt::registry& GetRegistry() const { return m_registry; }

	/*
	template <typename T>
	std::array<T> GetAllEntitiesWith<T>();

	template<typename T>
	
	*/

private:
	entt::registry m_registry; // can't copy this
};

#endif
