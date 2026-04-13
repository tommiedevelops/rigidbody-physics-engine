#include "PhysicsEngine.h"

#include "GravityForceGenerator.h"

#include <iostream>

#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>

#define MODELS_DIR   "../Assets/models/"
#define TEXTURES_DIR "../Assets/textures/"
#define SHADERS_DIR  "../Assets/shaders/"

using namespace PhysicsEngine;

class Cube2Script : public PhysicsEngine::ScriptableEntity 
{
	void OnCreate() override
	{
	}
	void OnStart() override
	{
		using namespace PhysicsEngine;
		auto& tr{ GetComponent<TransformComponent>() };
		tr.m_Position.y = 50.0f;

		auto& rb{ AddComponent<RigidbodyComponent>() };
		rb.SetMass(1.0f);
		AddComponent<ForceGeneratorComponent>().Bind<GravityForceGenerator>();
	}

	void OnUpdate(float dt) override
	{
		auto& tr{ GetComponent <PhysicsEngine::TransformComponent>() };
		std::cout << tr.m_Position.y << '\n';
	}
	void OnDestroy() override
	{
	}
};

class PlayerMoveScript : public PhysicsEngine::ScriptableEntity
{

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
		using namespace PhysicsEngine;

		m_LastMousePos = Input::GetMousePosition();

		auto& transform{ GetComponent<TransformComponent>() };
		transform.m_Position = glm::vec3(0.0f, 10.0f, -20.0f);

		Input::SetCursorEnabled(false);
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

class TestScene : public PhysicsEngine::Scene
{
	void SetUp() override
	{
		light.position = glm::vec3(1.0f, 3.0f, 0.0f); // fix lights?
		light.color = glm::vec3(0.5f, 0.3f, 0.9f);

		auto e{ CreateEntity() };
		Mesh* m{ m_AssetsRef->LoadMesh(MODELS_DIR "cube.obj").get() };
		e.AddComponent<MeshComponent>(m);

		Shader* s
		{
			m_AssetsRef->LoadShader( SHADERS_DIR "shader.vert", SHADERS_DIR "shader.frag" ).get(),
		};

		Material* mat{ m_AssetsRef->CreateMaterial("default", s, nullptr).get() };

		e.AddComponent<MaterialComponent>(mat);

		auto player{ CreateEntity() };
		player.AddComponent<CameraComponent>();
		player.AddComponent<ScriptComponent>().Bind<PlayerMoveScript>();
		SetMainCamera(player);
	}
};

class Test2Scene : public PhysicsEngine::Scene
{
	void SetUp() override
	{
		light.position = glm::vec3(1.0f, 3.0f, 0.0f); // fix lights?
		light.color = glm::vec3(1.0f);

		auto e{ CreateEntity() };
		Mesh* m{ m_AssetsRef->LoadMesh(MODELS_DIR "cube.obj").get() };
		e.AddComponent<MeshComponent>(m);

		Shader* s
		{
			m_AssetsRef->LoadShader( SHADERS_DIR "shader.vert", SHADERS_DIR "shader.frag" ).get(),
		};

		Material* mat{ m_AssetsRef->CreateMaterial("default", s, nullptr).get() };
		mat->albedo = glm::vec4(0, 1, 0, 1);

		e.AddComponent<MaterialComponent>(mat);

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
	sceneLayer->RegisterScene("Test2", []() { return std::make_unique<Test2Scene>(); });

	sceneLayer->SetActiveScene("Test2");

	app.PushLayer(sceneLayer);

	app.Run();
}
