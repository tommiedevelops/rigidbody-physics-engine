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

class SpherePlaneCollideScene : public Scene
{
	void SetUp() override
	{
		light.position = glm::vec3(0.0f, 100.0f, 10.0f); // fix lights?
		light.color = glm::vec3(1.0f, 1.0f, 1.0f);

		// --- PHYSICS TEST ---
		auto physicsTestEntity{ CreateEntity() };
		Mesh* m{ m_AssetsRef->LoadMesh(MODELS_DIR "sphere.obj").get() };
		auto localSize = m->GetBounds().size();
		auto worldSize = localSize * physicsTestEntity.GetComponent<TransformComponent>().m_Scale;

		physicsTestEntity.AddComponent<MeshComponent>(m);
		physicsTestEntity.AddComponent<NameComponent>("target");
		physicsTestEntity.GetComponent<TransformComponent>().m_Position = glm::vec3(0.0, 10.0f, 0.0f);
		auto& rb = physicsTestEntity.AddComponent<RigidbodyComponent>();
		physicsTestEntity.AddComponent<ForceGeneratorComponent>().Bind<GravityForceGenerator>(glm::vec3(-1,0,0));

		float sphereRadius = worldSize.x / 2.0f;
		physicsTestEntity.AddComponent<ColliderComponent>().AddPrimitive<SphereCollider>(sphereRadius);

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
		floorEntity.GetComponent<TransformComponent>().m_Rotation = glm::angleAxis(-3.14f / 2, glm::vec3(0, 0, 1));
		floorEntity.GetComponent<TransformComponent>().m_Position = glm::vec3(-10, 0, 0);

		floorEntity.AddComponent<ColliderComponent>().AddPrimitive<PlaneCollider>(glm::vec3(0.0f,1.0f,0.0f), 0.0f);


		// --- PLAYER ---
		auto player{ CreateEntity() };
		player.AddComponent<CameraComponent>();
		player.AddComponent<ScriptComponent>().Bind<PlayerMoveScript>();
		SetMainCamera(player);
	}
};


class SphereSphereCollideScene : public Scene
{
	void SetUp() override
	{
		light.position = glm::vec3(0.0f, 100.0f, 10.0f); // fix lights?
		light.color = glm::vec3(1.0f, 1.0f, 1.0f);

		// --- PHYSICS TEST ---
		auto sphere1{ CreateEntity() };
		Mesh* m{ m_AssetsRef->LoadMesh(MODELS_DIR "sphere.obj").get() };
		auto localSize = m->GetBounds().size();
		auto worldSize = localSize * sphere1.GetComponent<TransformComponent>().m_Scale;

		sphere1.AddComponent<MeshComponent>(m);
		sphere1.AddComponent<NameComponent>("target");
		sphere1.GetComponent<TransformComponent>().m_Position = glm::vec3(0.0, 10.0f, 0.0f);
		auto& rb = sphere1.AddComponent<RigidbodyComponent>();
		sphere1.AddComponent<ForceGeneratorComponent>().Bind<GravityForceGenerator>(glm::vec3(0, -1, 0));

		float sphereRadius = worldSize.x / 2.0f;
		sphere1.AddComponent<ColliderComponent>().AddPrimitive<SphereCollider>(sphereRadius);

		rb.m_InverseMass = 1.0f;

		Shader* s
		{
			m_AssetsRef->LoadShader(SHADERS_DIR "shader.vert", SHADERS_DIR "shader.frag").get(),
		};

		Material* mat{ m_AssetsRef->CreateMaterial("default", s, nullptr).get() };

		sphere1.AddComponent<MaterialComponent>(mat);

		// --- FLOOR ---
		auto sphere2{ CreateEntity() };
		sphere2.AddComponent<MeshComponent>(m_AssetsRef->LoadMesh(MODELS_DIR "sphere.obj").get());

		Material* floorMat{ m_AssetsRef->CreateMaterial("floor", s, nullptr).get() };
		floorMat->albedo = glm::vec4(0.5, 0.0, 0.5, 1.0);
		sphere2.AddComponent<MaterialComponent>(floorMat);

		sphere2.GetComponent<TransformComponent>().m_Position = glm::vec3(0);

		float sphere2Radius{ 2.0f };
		sphere2.GetComponent<TransformComponent>().m_Scale = glm::vec3(sphere2Radius, sphere2Radius, sphere2Radius);
		sphere2.GetComponent<TransformComponent>().m_Position = glm::vec3(0, 0, 0);

		sphere2.AddComponent<ColliderComponent>().AddPrimitive<SphereCollider>(sphere2Radius);


		// --- PLAYER ---
		auto player{ CreateEntity() };
		player.AddComponent<CameraComponent>();
		player.AddComponent<ScriptComponent>().Bind<PlayerMoveScript>();
		SetMainCamera(player);
	}
};

class BoxPlaneCollideScene : public Scene
{
	void SetUp() override
	{
		light.position = glm::vec3(0.0f, 100.0f, 10.0f); // fix lights?
		light.color = glm::vec3(1.0f, 1.0f, 1.0f);

		// --- PHYSICS TEST ---
		auto physicsTestEntity{ CreateEntity() };
		Mesh* m{ m_AssetsRef->LoadMesh(MODELS_DIR "cube.obj").get() };
		auto localSize = m->GetBounds().size();
		auto worldSize = localSize * physicsTestEntity.GetComponent<TransformComponent>().m_Scale;

		physicsTestEntity.AddComponent<MeshComponent>(m);
		physicsTestEntity.AddComponent<NameComponent>("target");
		physicsTestEntity.GetComponent<TransformComponent>().m_Position = glm::vec3(0.0, 10.0f, 0.0f);
		physicsTestEntity.GetComponent<TransformComponent>().m_Rotation = glm::angleAxis(3.14f / 4, glm::vec3(1, 0, 0));
		auto& rb = physicsTestEntity.AddComponent<RigidbodyComponent>();
		physicsTestEntity.AddComponent<ForceGeneratorComponent>().Bind<GravityForceGenerator>(glm::vec3(0,-1,0));

		glm::vec3 halfExtents{ 0.5f * worldSize.x, 0.5f * worldSize.y, 0.5f * worldSize.z };

		physicsTestEntity.AddComponent<ColliderComponent>().AddPrimitive<BoxCollider>(halfExtents);

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


class PrintDataScript : public ScriptableEntity
{
	// Inherited via ScriptableEntity
	void OnCreate() override
	{
	}
	void OnStart() override
	{
	}
	void OnUpdate(float dt) override
	{
		std::cout << "Printing Sphere Data\n";
		std::cout << GetComponent<TransformComponent>().m_Position << std::endl;
	}
	void OnDestroy() override
	{
	}
};

class SphereBoxCollideScene : public Scene
{
	void SetUp() override
	{
		light.position = glm::vec3(0.0f, 100.0f, 10.0f); // fix lights?
		light.color = glm::vec3(1.0f, 1.0f, 1.0f);

		// --- PHYSICS TEST ---
		auto physicsTestEntity{ CreateEntity() };
		Mesh* sphereMesh{ m_AssetsRef->LoadMesh(MODELS_DIR "sphere.obj").get() };
		auto sphereLocalSize = sphereMesh->GetBounds().size();
		auto sphereWorldSize = sphereLocalSize * physicsTestEntity.GetComponent<TransformComponent>().m_Scale;

		physicsTestEntity.AddComponent<MeshComponent>(sphereMesh);
		physicsTestEntity.AddComponent<NameComponent>("target");
		physicsTestEntity.GetComponent<TransformComponent>().m_Position = glm::vec3(0.0, -10.0f, 0.0f);
		auto& rb = physicsTestEntity.AddComponent<RigidbodyComponent>();

		physicsTestEntity.AddComponent<ScriptComponent>().Bind<PrintDataScript>();

		float sphereRadius = sphereWorldSize.x / 2.0f;
		physicsTestEntity.AddComponent<ColliderComponent>().AddPrimitive<SphereCollider>(sphereRadius);

		rb.m_InverseMass = 1.0f;
	
		Shader* s
		{
			m_AssetsRef->LoadShader( SHADERS_DIR "shader.vert", SHADERS_DIR "shader.frag" ).get(),
		};

		Material* mat{ m_AssetsRef->CreateMaterial("default", s, nullptr).get() };

		physicsTestEntity.AddComponent<MaterialComponent>(mat);

		// --- BOX ---
		auto boxEntity{ CreateEntity() };

		float cubeLength{ 2.0f };
		auto& boxEntityTransform = boxEntity.GetComponent<TransformComponent>();
		boxEntityTransform.m_Scale = glm::vec3(cubeLength, cubeLength, cubeLength);
		boxEntityTransform.m_Position = glm::vec3(0, 10, 0);
		boxEntityTransform.m_Rotation = glm::angleAxis(3.14f / 4.0f, glm::vec3(1, 0, 0));

		Mesh* boxMesh{ m_AssetsRef->LoadMesh(MODELS_DIR "cube.obj").get() };
		auto boxLocalSize{ boxMesh->GetBounds().size() };

		boxEntity.AddComponent<MeshComponent>(boxMesh);

		boxEntity.AddComponent<RigidbodyComponent>().SetMass(1.0f);
		boxEntity.AddComponent<ForceGeneratorComponent>().Bind<GravityForceGenerator>(glm::vec3(0,-1,0));

		Material* boxMat{ m_AssetsRef->CreateMaterial("floor", s, nullptr).get()};
		boxMat->albedo = glm::vec4(0.5, 0.0, 0.5, 1.0);
		boxEntity.AddComponent<MaterialComponent>(boxMat);
		
		glm::vec3 boxHalfExtents{ boxLocalSize / 2.0f };
		boxEntity.AddComponent<ColliderComponent>().AddPrimitive<BoxCollider>(boxHalfExtents);

		// --- PLAYER ---
		auto player{ CreateEntity() };
		player.AddComponent<CameraComponent>();
		player.AddComponent<ScriptComponent>().Bind<PlayerMoveScript>();
		SetMainCamera(player);
	}
};


class BoxBoxCollideScene : public Scene
{
	void SetUp() override
	{
		light.position = glm::vec3(0.0f, 100.0f, 10.0f); // fix lights?
		light.color = glm::vec3(1.0f, 1.0f, 1.0f);

		// --- BOX 1 ---
		auto box1Entity{ CreateEntity() };

		box1Entity.AddComponent<NameComponent>("target");
		float cube1Length{ 3.0f };
		auto& box1EntityTransform = box1Entity.GetComponent<TransformComponent>();
		box1EntityTransform.m_Scale = glm::vec3(cube1Length, cube1Length, cube1Length);
		box1EntityTransform.m_Position = glm::vec3(0, 20, 0);
		box1EntityTransform.m_Rotation = glm::angleAxis(3.14f / 4.0f, glm::vec3(0, 0, -1));

		Mesh* boxMesh{ m_AssetsRef->LoadMesh(MODELS_DIR "cube.obj").get() };
		auto box1LocalSize{ boxMesh->GetBounds().size() };

		box1Entity.AddComponent<MeshComponent>(boxMesh);

		box1Entity.AddComponent<RigidbodyComponent>().SetMass(1.0f);
		box1Entity.AddComponent<ForceGeneratorComponent>().Bind<GravityForceGenerator>(glm::vec3(0, -1, 0));

		Shader* s
		{
			m_AssetsRef->LoadShader( SHADERS_DIR "shader.vert", SHADERS_DIR "shader.frag" ).get(),
		};

		Material* box1Mat{ m_AssetsRef->CreateMaterial("floor", s, nullptr).get() };
		box1Mat->albedo = glm::vec4(0.5, 0.0, 0.5, 1.0);
		box1Entity.AddComponent<MaterialComponent>(box1Mat);

		glm::vec3 box1HalfExtents{ box1LocalSize / 2.0f };
		box1Entity.AddComponent<ColliderComponent>().AddPrimitive<BoxCollider>(box1HalfExtents);

		// --- BOX 2 ---
		auto boxEntity{ CreateEntity() };

		float cubeLength{ 2.0f };
		auto& boxEntityTransform = boxEntity.GetComponent<TransformComponent>();
		boxEntityTransform.m_Scale = glm::vec3(cubeLength, cubeLength, cubeLength);
		boxEntityTransform.m_Position = glm::vec3(0, 0, 0);
		boxEntityTransform.m_Rotation = glm::angleAxis(3.14f / 4.0f, glm::vec3(1, 0, 0));

		auto boxLocalSize{ boxMesh->GetBounds().size() };

		boxEntity.AddComponent<MeshComponent>(boxMesh);

		boxEntity.AddComponent<RigidbodyComponent>().SetMass(1.0f);

		Material* boxMat{ m_AssetsRef->CreateMaterial("floor", s, nullptr).get()};
		boxMat->albedo = glm::vec4(0.0, 0.5, 0.5, 1.0);
		boxEntity.AddComponent<MaterialComponent>(boxMat);
		
		glm::vec3 boxHalfExtents{ boxLocalSize / 2.0f };
		boxEntity.AddComponent<ColliderComponent>().AddPrimitive<BoxCollider>(boxHalfExtents);

		// --- PLAYER ---
		auto player{ CreateEntity() };
		player.AddComponent<CameraComponent>();
		player.AddComponent<ScriptComponent>().Bind<PlayerMoveScript>();
		SetMainCamera(player);
	}

};

class TennisRacketScene : public Scene {

	class RacketScript : public ScriptableEntity
	{
		void OnCreate() override {}
		void OnStart() override
		{
			auto& rb = GetComponent<RigidbodyComponent>();
			rb.m_AngularVelocity = glm::vec3(0.0f, 5.0f, 0.0);
		}

		void OnUpdate(float dt) override
		{

		}

		void OnDestroy() override {}

		void OnEvent(Event& e) override
		{
			EventDispatcher dispatcher(e);

			auto& rb = GetComponent<RigidbodyComponent>();

			dispatcher.Dispatch<KeyPressedEvent>([&rb](KeyPressedEvent& e)  -> bool
			{

				float p = 0.4f;
				if (e.GetKeyCode() == GLFW_KEY_Z)
				{
					std::cout << "perturbed on z axis\n";
					rb.m_AngularVelocity += glm::vec3(0, 0, p);
				}
				else if (e.GetKeyCode() == GLFW_KEY_Y)
				{
					std::cout << "perturbed on y axis\n";
					rb.m_AngularVelocity += glm::vec3(0, p, 0);
				}
				else if (e.GetKeyCode() == GLFW_KEY_X)
				{
					std::cout << "perturbed on x axis\n";
					rb.m_AngularVelocity += glm::vec3(p, 0, 0);
				}

				return true;
			});

		}
	};

	void SetUp() override {
		auto e = CreateEntity();

		Mesh* boxMesh{ m_AssetsRef->LoadMesh(MODELS_DIR "cube.obj").get() };
		e.AddComponent<MeshComponent>(boxMesh);

		auto& rb = e.AddComponent<RigidbodyComponent>();
		float w = 1.0f, h = 10.0f, d = 30.0f;

		e.GetComponent<TransformComponent>().m_Scale = glm::vec3(w, h, d);
		float mass = 1.0f;

		glm::mat3 inertiaTensor(0.0f);

		inertiaTensor[0][0] = 1.0f / 12.0f * mass * (h * h + d * d);  // = 1/12 * (4+9) = 1.083
		inertiaTensor[1][1] = 1.0f / 12.0f * mass * (w * w + d * d);  // = 1/12 * (1+9) = 0.833
		inertiaTensor[2][2] = 1.0f / 12.0f * mass * (w * w + h * h);  // = 1/12 * (1+4) = 0.416

		rb.SetInertiaTensor(inertiaTensor);
		rb.SetMass(1.0f);

		Shader* s
		{
			m_AssetsRef->LoadShader(SHADERS_DIR "shader.vert", SHADERS_DIR "shader.frag").get(),
		};

		Material* boxMat{ m_AssetsRef->CreateMaterial("floor", s, nullptr).get() };
		boxMat->albedo = glm::vec4(0.5, 0.0, 0.5, 1.0);

		e.AddComponent<ScriptComponent>().Bind<RacketScript>();
		e.AddComponent<MaterialComponent>(boxMat);
		e.AddComponent<NameComponent>("target");

		// --- PLAYER ---
		auto player{ CreateEntity() };
		player.AddComponent<CameraComponent>();
		player.AddComponent<ScriptComponent>().Bind<PlayerMoveScript>();
		SetMainCamera(player);
	}
};
