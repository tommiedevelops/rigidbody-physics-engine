#ifndef ENTITY_H
#define ENTITY_H

class Entity
{
public:
	template <typename T>
	T& GetComponent();

	template <typename T>
	void AddComponent(T& t);
};

#endif