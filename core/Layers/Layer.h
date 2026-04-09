#pragma once

namespace PhysicsEngine
{
	class Event;

	class Layer
	{
	public:
		virtual ~Layer() = default;

		virtual void OnAttach() = 0;
		virtual void OnDetach() = 0;
		virtual void OnUpdate(float dt) = 0;
		virtual void OnRender() = 0;
		virtual void OnEvent(Event& e) = 0;
	};
}