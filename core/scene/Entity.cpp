#include "Entity.h"
#include <iostream>

template <typename T>
T& Entity::GetComponent()
{
	// NOOP
	throw std::logic_error("not implemented");
	return nullptr;
}

template <typename T>
void Entity::AddComponent(T& t)
{
	throw std::logic_error("not implemented");
};
