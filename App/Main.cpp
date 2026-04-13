#include "PhysicsEngine.h"

#include "GravityForceGenerator.h"

#include <iostream>

#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>

#define MODELS_DIR   "../Assets/models/"
#define TEXTURES_DIR "../Assets/textures/"
#define SHADERS_DIR  "../Assets/shaders/"

using namespace PhysicsEngine;

#include "debug.h"

class PlayerMoveScript : public ScriptableEntity
{

	// ai gen
	void LookAt(TransformComponent& tr, glm::vec3 worldSpaceTarget)
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
	void SyncYawPitch(const glm::quat& rotation) 
	{
		// Extract world space yaw from the forward vector
		glm::vec3 forward = rotation * glm::vec3(0, 0, -1);
		m_Yaw = glm::degrees(atan2(forward.x, -forward.z));

		// Extract local pitch from the forward vector
		m_Pitch = glm::degrees(asin(-forward.y));
	}

	glm::vec2 moveDir{ 0.0f };
	glm::vec2 m_LastMousePos{ 0.0f };
	float m_Sensitivity{ 5.0f };

	float m_Yaw{ 0.0f };
	float m_Pitch{ 0.0f };

	glm::vec3 getForward(const glm::quat& q) {
		return q * glm::vec3(0.0f, 0.0f, -1.0f);
	}

	glm::vec3 getRight(const glm::quat& q) {
		return q * glm::vec3(1.0f, 0.0f, 0.0f);
	}

	glm::vec3 getUp(const glm::quat& q) {
		return q * glm::vec3(0.0f, 1.0f, 0.0f);
	}

	void OnCreate() override
	{
	}
	void OnStart() override
	{
		m_LastMousePos = Input::GetMousePosition();

		auto& transform{ GetComponent<TransformComponent>() };
		transform.m_Position = glm::vec3(0.0f, 10.0f, -20.0f);

		Input::SetCursorEnabled(false);

		Entity targetEntity = m_Scene->GetEntity("target");
		if (targetEntity.IsNull()) throw std::logic_error("couldnt find target");

		auto targetPos{ targetEntity.GetComponent<TransformComponent>().m_Position };

		LookAt(transform, targetPos);
		SyncYawPitch(transform.m_Rotation);

	}
	void OnUpdate(float dt) override
	{
		using namespace PhysicsEngine;
		auto& transform{ GetComponent<TransformComponent>() };

		// Handle Mouse
		m_Sensitivity = 1.0f;
		glm::vec2 mousePos = Input::GetMousePosition();
		glm::vec2 deltaMousePos = (mousePos - m_LastMousePos) * m_Sensitivity;
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
		glm::vec3 deltaHeight = flight*flightSpeed * up * dt;

		float speed = 10.0f;
		auto forward{ getForward(transform.m_Rotation) };
		auto right{ getRight(transform.m_Rotation) };

		glm::vec3 deltaPos = (moveDir.y * forward + moveDir.x * right) * speed * dt;

		transform.m_Position += (deltaPos + deltaHeight);
	}

	void OnDestroy() override
	{
	}

	void OnEvent(PhysicsEngine::Event& e)
	{


	}
};

class CubeScript : public PhysicsEngine::ScriptableEntity
{
	float theta{ 0.0f };

	void OnCreate() override
	{
		using namespace PhysicsEngine;
	}
	void OnStart() override
	{
	}

	void OnEvent(PhysicsEngine::Event& e)
	{
		
	}

	void OnUpdate(float dt) override
	{
		auto& transform = GetComponent<PhysicsEngine::TransformComponent>();

		theta += dt * 2.0f;
		transform.m_Position.y = 10.0f * sinf(theta);
	}

	void OnDestroy() override
	{
		std::cout << "Destroyed\n";
	}
};

class TestScene : public Scene
{
	void SetUp() override
	{
		light.position = glm::vec3(0.0f, 100.0f, 10.0f); // fix lights?
		light.color = glm::vec3(1.0f, 1.0f, 1.0f);

		// --- PHYSICS TEST ---
		auto physicsTestEntity{ CreateEntity() };
		Mesh* m{ m_AssetsRef->LoadMesh(MODELS_DIR "sphere.obj").get() };
		physicsTestEntity.AddComponent<MeshComponent>(m);
		physicsTestEntity.AddComponent<NameComponent>("target");
		physicsTestEntity.GetComponent<TransformComponent>().m_Position = glm::vec3(0.0, 10.0f, 0.0f);
		auto& rb = physicsTestEntity.AddComponent<RigidbodyComponent>();
		physicsTestEntity.AddComponent<ForceGeneratorComponent>().Bind<GravityForceGenerator>();
		physicsTestEntity.AddComponent<ColliderComponent>().AddPrimitive<SphereCollider>(1.0f);

		rb.m_InverseMass = 1.0f;
	
		Shader* s
		{
			m_AssetsRef->LoadShader( SHADERS_DIR "shader.vert", SHADERS_DIR "shader.frag" ).get(),
		};

		Material* mat{ m_AssetsRef->CreateMaterial("default", s, nullptr).get() };

		physicsTestEntity.AddComponent<MaterialComponent>(mat);

		// --- FLOOR ---
		auto floorEntity{ CreateEntity() };
		floorEntity.AddComponent<MeshComponent>(m_AssetsRef->LoadMesh(MODELS_DIR "quad.obj").get());

		Material* floorMat{ m_AssetsRef->CreateMaterial("floor", s, nullptr).get()};
		floorMat->albedo = glm::vec4(0.5, 0.0, 0.5, 1.0);
		floorEntity.AddComponent<MaterialComponent>(floorMat);

		floorEntity.GetComponent<TransformComponent>().m_Position = glm::vec3(0);

		float floorLength{ 50.0f };
		floorEntity.GetComponent<TransformComponent>().m_Scale = glm::vec3(floorLength, 0.0f, floorLength);

		floorEntity.AddComponent<ColliderComponent>().AddPrimitive<PlaneCollider>(glm::vec3(0.0f,1.0f,0.0f), 0.0f);


		// --- PLAYER ---
		auto player{ CreateEntity() };
		player.AddComponent<CameraComponent>();
		player.AddComponent<ScriptComponent>().Bind<PlayerMoveScript>();
		SetMainCamera(player);
	}
};

int main()
{
	using namespace PhysicsEngine;

	WindowProperties props{};
	App app{props};

	auto sceneLayer = std::make_shared<SceneLayer>();
	sceneLayer->SetAssetsRef(app.GetAssetsRef());

	sceneLayer->RegisterScene("Test", []() { return std::make_unique<TestScene>(); });

	sceneLayer->SetActiveScene("Test");

	app.PushLayer(sceneLayer);

	app.Run();
}
