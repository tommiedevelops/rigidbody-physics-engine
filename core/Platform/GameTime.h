#pragma once

#include <time.h>

namespace PhysicsEngine
{
	struct GameTime
	{
	private:
		float m_DeltaTime; // seconds
		float m_TotalTime; // seconds
		clock_t m_LastTime; // clock cycles
	public:
		GameTime();
		~GameTime() = default;

		void Update();
		float GetDeltaTime();
		float GetFPS();
	};
};
