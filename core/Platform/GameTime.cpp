#include "GameTime.h"

namespace PhysicsEngine
{

	GameTime::GameTime()
		: m_DeltaTime { 0.0f }
		, m_TotalTime { 0.0f }
		, m_LastTime{ clock() }
	{}

	void GameTime::Update()
	{
		clock_t currTime{ clock() };
		m_DeltaTime = static_cast<float>((currTime - m_LastTime)) / CLOCKS_PER_SEC;
		m_LastTime = currTime;
		m_TotalTime += m_DeltaTime;
	}

	float GameTime::GetDeltaTime()
	{
		return m_DeltaTime;
	}

	float GameTime::GetFPS()
	{
		return 1.0f / m_DeltaTime;
	}
}