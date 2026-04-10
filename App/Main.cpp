#include "PhysicsEngine.h"

#include <iostream>

#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>

#define MODELS_DIR   "../Assets/models/"
#define TEXTURES_DIR "../Assets/textures/"
#define SHADERS_DIR  "../Assets/shaders/"

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

		Input::SetCursorEnabled(false);
	}
	void OnUpdate(float dt) override
	{
		using namespace PhysicsEngine;
		auto& transform{ GetComponent<TransformComponent>() };


		// Handle Mouse

		glm::vec2 mousePos = Input::GetMousePosition();
		glm::vec2 deltaMousePos = (mousePos - m_LastMousePos) * m_Sensitivity * dt;
		m_LastMousePos = mousePos;

		m_Yaw += deltaMousePos.x;
		m_Pitch += deltaMousePos.y;

		// clamp pitch to avoid flipping
		m_Pitch = glm::clamp(m_Pitch, -89.0f, 89.0f);

		glm::quat yawQ = glm::angleAxis(glm::radians(-deltaMousePos.x * m_Sensitivity),
			transform.rotation * glm::vec3(0, 1, 0)); // local up

		glm::quat pitchQ = glm::angleAxis(glm::radians(-deltaMousePos.y * m_Sensitivity),
			transform.rotation * glm::vec3(1, 0, 0)); // local right

		transform.rotation = yawQ * pitchQ * transform.rotation;

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
		auto up{ getUp(transform.rotation) };
		glm::vec3 deltaHeight = flight*flightSpeed * up * dt;

		float speed = 10.0f;
		auto forward{ getForward(transform.rotation) };
		auto right{ getRight(transform.rotation) };

		glm::vec3 deltaPos = (moveDir.y * forward + moveDir.x * right) * speed * dt;

		transform.position += (deltaPos + deltaHeight);
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
		std::cout << "Created\n";
	}
	void OnStart() override
	{
		std::cout << "Started\n";
	}

	void OnEvent(PhysicsEngine::Event& e)
	{
		
	}

	void OnUpdate(float dt) override
	{
		auto& transform = GetComponent<PhysicsEngine::TransformComponent>();

		theta += 2.0f * dt;

		glm::vec3 yAxis(0.0f, 1.0f, 1.0f);
		glm::quat q = glm::normalize(glm::angleAxis(theta, yAxis));

		transform.rotation = q;
	}
	void OnDestroy() override
	{
		std::cout << "Destroyed\n";
	}
};

int main()
{
	using namespace PhysicsEngine;

	WindowProperties props{};
	App app{props};

	auto& assets = app.GetAssetsRef();
	assets.AddMesh(MODELS_DIR "bunny/bunny.obj", "bunny");
	assets.AddMesh(MODELS_DIR "cube.obj", "cube");

	assets.AddShader(SHADERS_DIR "shader.vert", SHADERS_DIR "shader.frag", "default");

	assets.CreateMaterial("m1", assets.GetShader("default"), nullptr);

	auto m = assets.GetMaterial("m1");
	m->albedo = glm::vec4(0.1, 0.4, 0.4, 1.0);
	m->ambientStrength = 0.9f;
	m->diffuse = 0.4f;
	m->specular = 0.9f;

	assets.CreateMaterial("m2", assets.GetShader("default"), nullptr);

	auto m2 = assets.GetMaterial("m2");
	m2->albedo = glm::vec4(0.6, 0.1, 0.1, 1.0);
	m2->ambientStrength = 0.4f;
	m2->diffuse = 0.4f;
	m2->specular = 0.9f;

	Scene initialScene{};
	initialScene.light.position = glm::vec3(1.0f, 3.0f, 0.0f);
	initialScene.light.color = glm::vec3(0.5f, 0.3f, 0.9f);

	auto player{ initialScene.CreateEntity()};
	player.AddComponent<CameraComponent>();
	player.AddComponent<ScriptComponent>().Bind<PlayerMoveScript>();
	initialScene.SetMainCamera(player);


	auto e{ initialScene.CreateEntity() };

	e.AddComponent<ScriptComponent>().Bind<CubeScript>();

	auto& meshComp = e.AddComponent<MeshComponent>();
	meshComp.mesh = assets.GetMesh("cube"); 
	
	auto& matComp  = e.AddComponent<MaterialComponent>();
	matComp.material = assets.GetMaterial("m1");

	auto& transformComp = e.GetComponent<TransformComponent>();
	transformComp.scale = glm::vec3(1.0f, 1.0f, 1.0f);
	transformComp.rotation = glm::quat(1.0f, 0.3f, 0.2f, 0.1f);
	transformComp.position = glm::vec3(0.0f, 0.0f, -10.0f);

	auto e2{ initialScene.CreateEntity() };

	auto& meshComp2 = e2.AddComponent<MeshComponent>();
	meshComp2.mesh = assets.GetMesh("cube"); 
	
	auto& matComp2  = e2.AddComponent<MaterialComponent>();
	matComp2.material = assets.GetMaterial("m2");

	auto& transformComp2 = e2.GetComponent<TransformComponent>();
	transformComp2.scale = 0.5f*glm::vec3(1.0f, 1.0f, 1.0f);
	transformComp2.rotation = glm::quat(0.1f, 0.3f, 0.9f, 0.1f);
	transformComp2.position = glm::vec3(1.5f, 2.0f, -7.0f);


	//initialScene2.cam.transform.position = glm::vec3(1.0f, 0.0f, 5.0f);

	app.SetCurrentScene(&initialScene);

	app.Run();
}
