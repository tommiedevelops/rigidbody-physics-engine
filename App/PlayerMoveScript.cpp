#include "PlayerMoveScript.h"

namespace Talk
{
	using namespace PhysicsEngine;
	void PlayerMoveScript::OnCreate()
	{

	}

	void PlayerMoveScript::LookAt(TransformComponent& tr, glm::vec3 worldSpaceTarget)
	{
		auto direction = glm::normalize(worldSpaceTarget - tr.m_Position);
		glm::vec3 forward = glm::normalize(tr.m_Rotation * glm::vec3(0, 0, -1));

		glm::vec3 axis = glm::cross(forward, direction);

		float dot = glm::dot(forward, direction);
		// already facing target
		if (dot >= 0.9999f) return;

		// opposite direction — rotate 180 around world up
		if (dot <= -0.9999f) {
			tr.m_Rotation = glm::angleAxis(glm::pi<float>(), glm::vec3(0, 1, 0)) * tr.m_Rotation;
			return;
		}
		// angle between the two vectors
		float angle = glm::acos(dot);

		glm::quat rotation = glm::angleAxis(angle, glm::normalize(axis));

		tr.m_Rotation = glm::normalize(rotation * tr.m_Rotation);
	}

	// ai gen
	void PlayerMoveScript::SyncYawPitch(const glm::quat& rotation)
	{
		// Extract world space yaw from the forward vector
		glm::vec3 forward = rotation * glm::vec3(0, 0, -1);
		m_Yaw = glm::degrees(atan2(forward.x, -forward.z));

		// Extract local pitch from the forward vector
		m_Pitch = glm::degrees(asin(-forward.y));
	}

	glm::vec3 getForward(const glm::quat& q) {
		return q * glm::vec3(0.0f, 0.0f, -1.0f);
	}

	glm::vec3 getRight(const glm::quat& q) {
		return q * glm::vec3(1.0f, 0.0f, 0.0f);
	}

	glm::vec3 getUp(const glm::quat& q) {
		return q * glm::vec3(0.0f, 1.0f, 0.0f);
	}

	void PlayerMoveScript::OnStart()
	{
		m_LastMousePos = Input::GetMousePosition().value_or(m_LastMousePos);

		auto& transform{ GetComponent<TransformComponent>() };
		transform.m_Position = glm::vec3(0.0f, 10.0f, -20.0f);

		Input::SetCursorEnabled(false);

		Entity targetEntity = m_Scene->GetEntity("target");
		if (targetEntity.IsNull()) throw std::logic_error("couldnt find target");

		auto targetPos{ targetEntity.GetComponent<TransformComponent>().m_Position };

		LookAt(transform, targetPos);
		SyncYawPitch(transform.m_Rotation);

	}

	void PlayerMoveScript::OnUpdate(float dt)
	{
		using namespace PhysicsEngine;
		auto& transform{ GetComponent<TransformComponent>() };

		// Handle Mouse
		m_Sensitivity = 1.0f;
		glm::vec2 mousePos = Input::GetMousePosition().value_or(m_LastMousePos);

		// Handles the case wehre jump is too far 
		float tolerance = 500.0f;
		glm::vec2 deltaMousePos = (mousePos - m_LastMousePos);
		bool mouseJumpedTooFar = glm::dot(deltaMousePos, deltaMousePos) > tolerance;
		deltaMousePos = mouseJumpedTooFar ? glm::vec2(0.0f, 0.0f) : deltaMousePos * m_Sensitivity;

		m_LastMousePos = mousePos;

		m_Yaw += deltaMousePos.x;
		m_Pitch += deltaMousePos.y;
		m_Pitch = glm::clamp(m_Pitch, -89.0f, 89.0f);

		// Rebuild from world Y yaw, local X pitch
		glm::quat yawQ = glm::angleAxis(glm::radians(-m_Yaw), glm::vec3(0, 1, 0)); // world up
		glm::quat pitchQ = glm::angleAxis(glm::radians(-m_Pitch), glm::vec3(1, 0, 0)); // local right

		transform.m_Rotation = yawQ * pitchQ;

		// Handle movement
		glm::vec2 moveDir(0.0f);
		if (Input::IsKeyDown(GLFW_KEY_W)) moveDir.y += 1.0f;
		if (Input::IsKeyDown(GLFW_KEY_S)) moveDir.y -= 1.0f;
		if (Input::IsKeyDown(GLFW_KEY_A)) moveDir.x -= 1.0f;
		if (Input::IsKeyDown(GLFW_KEY_D)) moveDir.x += 1.0f;

		float flight = 0.0f;
		if (Input::IsKeyDown(GLFW_KEY_SPACE))
			flight += 1.0f;
		if (Input::IsKeyDown(GLFW_KEY_LEFT_SHIFT))
			flight -= 1.0f;

		float flightSpeed = 5.0f;
		auto up{ getUp(transform.m_Rotation) };
		glm::vec3 deltaHeight = flight * flightSpeed * up * dt;

		float speed = 10.0f;
		auto forward{ getForward(transform.m_Rotation) };
		auto right{ getRight(transform.m_Rotation) };

		glm::vec3 deltaPos = (moveDir.y * forward + moveDir.x * right) * speed * dt;

		transform.m_Position += (deltaPos + deltaHeight);
	}

	void PlayerMoveScript::OnDestroy()
	{

	}

}
