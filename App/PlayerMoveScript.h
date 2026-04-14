#pragma once

#include "PhysicsEngine.h"

namespace Talk
{
	using namespace PhysicsEngine;
	class PlayerMoveScript : public ScriptableEntity
	{
	public:
		void OnCreate() override;
		void OnStart() override;
		void OnUpdate(float dt) override;
		void OnDestroy() override;
	private:
		void LookAt(TransformComponent& tr, glm::vec3 worldSpaceTarget);
		void SyncYawPitch(const glm::quat& rotation);

		glm::vec2 moveDir{ 0.0f };
		glm::vec2 m_LastMousePos{ 0.0f };
		float m_Sensitivity{ 5.0f };

		float m_Yaw{ 0.0f };
		float m_Pitch{ 0.0f };

	};
}