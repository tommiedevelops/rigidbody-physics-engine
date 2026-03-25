#include "scene/scene.h"
#include "renderer/renderer.h"
#include "physics/physics_world.h"
#include "app/window.h"

struct VTable
{
	// fptrs to callbacks
};

class App
{
public:
	App();
	void Run();
private:
	Window         m_Window;
	Scene          m_Scene;
	PhysicsWorld   m_PhysicsWorld;
	Renderer       m_Renderer;
	VTable         m_VTable;
};
