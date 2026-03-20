#include <vector>

#ifndef SCENE_H
#define SCENE_H

class Material
{
	
};

class Mesh
{

};

class Transform
{
private:
	float position;
	float rotation;
	float scale;
};

class GameObject
{
	enum Authority
	{
		DYNAMIC, // physics engine responsible for update
		KINEMATIC, // gameplay responsible for update
		STATIC // gameplay responsible for update (once)
	};

private:
	Transform m_transform;
	Mesh m_mesh;
	Material m_material;
};

class Camera
{
private:
	Transform m_transform;
};

class Light
{
private:
	Transform m_transform;
};

class Scene
{
private:
	std::vector<GameObject> m_gameObjects;
	Camera m_camera;
	Light m_light;
};
#endif
