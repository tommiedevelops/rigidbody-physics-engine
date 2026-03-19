#include "scene/scene.h"
#include "renderer/renderer.h"
#include "physics/physics_world.h"

class App
{
private:
	Scene          m_scene;
	PhysicsWorld   m_physicsWorld;
	Renderer       m_renderer;

public:

	void update() // call from main loop
	{

	}

	// callbacks for the user to overwrite

};


/*
int main()
{
	// handle input / events
	// update gameplay / scripts/ AI
	// push gameplay driven changes into physics
	// step physics 
	// pull physics results back into scene transforms
	// render
}
*/