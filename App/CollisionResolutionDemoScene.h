#pragma once
#include "PhysicsEngine.h"
#include "PlayerMoveScript.h"
#include "Common.h"

#include <memory>
namespace Talk
{
    using namespace PhysicsEngine;

    class SphereSphereTestScene : public Scene
    {
        void SetUp() override
        {
            auto shader{ m_AssetsRef->LoadShader(SHADERS_DIR "shader.vert",SHADERS_DIR "shader.frag") };
            auto material{ m_AssetsRef->CreateMaterial("mat", shader, nullptr) };

            auto target{ CreateEntity() };
            auto sphereMesh{ m_AssetsRef->LoadMesh(MODELS_DIR "sphere.obj") };
            target.AddComponent<MeshComponent>(sphereMesh);
            target.AddComponent<MaterialComponent>(material);
            target.GetComponent<TransformComponent>().m_Position = glm::vec3(0, 10, 0);
            target.AddComponent<RigidbodyComponent>();

            auto fallingObject{ CreateEntity() };
            target.AddComponent<MeshComponent>(sphereMesh);
            target.AddComponent<MaterialComponent>(material);



            auto player = CreateEntity();
            player.AddComponent<ScriptComponent>().Bind<PlayerMoveScript>();
            player.AddComponent<CameraComponent>().m_Far = 500.0f;
            SetMainCamera(player);
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
			auto sphereMesh{ m_AssetsRef->LoadMesh(MODELS_DIR "sphere.obj") };
			auto sphereLocalSize = sphereMesh->GetBounds().size();
			auto sphereWorldSize = sphereLocalSize * physicsTestEntity.GetComponent<TransformComponent>().m_Scale;

			physicsTestEntity.AddComponent<MeshComponent>(sphereMesh);
			physicsTestEntity.AddComponent<NameComponent>("target");
			physicsTestEntity.GetComponent<TransformComponent>().m_Position = glm::vec3(0.0, -10.0f, 0.0f);
			auto& rb = physicsTestEntity.AddComponent<RigidbodyComponent>();

			float sphereRadius = sphereWorldSize.x / 2.0f;
			physicsTestEntity.AddComponent<ColliderComponent>().AddPrimitive<SphereCollider>(sphereRadius);

			rb.m_InverseMass = 1.0f;

			auto s { m_AssetsRef->LoadShader(SHADERS_DIR "shader.vert", SHADERS_DIR "shader.frag") };

			auto mat{ m_AssetsRef->CreateMaterial("default", s, nullptr) };

			physicsTestEntity.AddComponent<MaterialComponent>(mat);

			// --- BOX ---
			auto boxEntity{ CreateEntity() };

			float cubeLength{ 2.0f };
			auto& boxEntityTransform = boxEntity.GetComponent<TransformComponent>();
			boxEntityTransform.m_Scale = glm::vec3(cubeLength, cubeLength, cubeLength);
			boxEntityTransform.m_Position = glm::vec3(0, 10, 0);
			boxEntityTransform.m_Rotation = glm::angleAxis(3.14f / 4.0f, glm::vec3(1, 0, 0));

			auto boxMesh{ m_AssetsRef->LoadMesh(MODELS_DIR "cube.obj") };
			auto boxLocalSize{ boxMesh->GetBounds().size() };

			boxEntity.AddComponent<MeshComponent>(boxMesh);

			boxEntity.AddComponent<RigidbodyComponent>().SetMass(1.0f);
			boxEntity.AddComponent<ForceGeneratorComponent>().Bind<GravityForceGenerator>(glm::vec3(0, -1, 0));

			auto boxMat{ m_AssetsRef->CreateMaterial("floor", s, nullptr)};
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

			auto boxMesh{ m_AssetsRef->LoadMesh(MODELS_DIR "cube.obj") };
			auto box1LocalSize{ boxMesh->GetBounds().size() };

			box1Entity.AddComponent<MeshComponent>(boxMesh);

			box1Entity.AddComponent<RigidbodyComponent>().SetMass(1.0f);
			box1Entity.AddComponent<ForceGeneratorComponent>().Bind<GravityForceGenerator>(glm::vec3(0, -1, 0));

			auto s { m_AssetsRef->LoadShader(SHADERS_DIR "shader.vert", SHADERS_DIR "shader.frag") };

			auto box1Mat{ m_AssetsRef->CreateMaterial("floor", s, nullptr) };
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

			auto boxMat{ m_AssetsRef->CreateMaterial("floor", s, nullptr) };
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
	class BoxPlaneCollideScene : public Scene
	{
		void SetUp() override
		{
			light.position = glm::vec3(0.0f, 100.0f, 10.0f); // fix lights?
			light.color = glm::vec3(1.0f, 1.0f, 1.0f);

			// --- PHYSICS TEST ---
			auto physicsTestEntity{ CreateEntity() };
			auto m{ m_AssetsRef->LoadMesh(MODELS_DIR "cube.obj") };
			auto localSize = m->GetBounds().size();
			auto worldSize = localSize * physicsTestEntity.GetComponent<TransformComponent>().m_Scale;

			physicsTestEntity.AddComponent<MeshComponent>(m);
			physicsTestEntity.AddComponent<NameComponent>("target");
			physicsTestEntity.GetComponent<TransformComponent>().m_Position = glm::vec3(0.0, 10.0f, 0.0f);
			physicsTestEntity.GetComponent<TransformComponent>().m_Rotation = glm::angleAxis(3.14f / 4, glm::vec3(1, 0, 0));
			auto& rb = physicsTestEntity.AddComponent<RigidbodyComponent>();
			physicsTestEntity.AddComponent<ForceGeneratorComponent>().Bind<GravityForceGenerator>(glm::vec3(0, -5, 0));

			glm::vec3 halfExtents{ 0.5f * worldSize.x, 0.5f * worldSize.y, 0.5f * worldSize.z };

			physicsTestEntity.AddComponent<ColliderComponent>().AddPrimitive<BoxCollider>(halfExtents);

			rb.m_InverseMass = 1.0f;

			auto s { m_AssetsRef->LoadShader(SHADERS_DIR "shader.vert", SHADERS_DIR "shader.frag") };

			auto mat{ m_AssetsRef->CreateMaterial("default", s, nullptr)};

			physicsTestEntity.AddComponent<MaterialComponent>(mat);

			// --- FLOOR ---
			auto floorEntity{ CreateEntity() };
			auto mesh{ m_AssetsRef->LoadMesh(MODELS_DIR "quad.obj") };
			floorEntity.AddComponent<MeshComponent>(mesh);

			auto floorMat{ m_AssetsRef->CreateMaterial("floor", s, nullptr) };
			floorMat->albedo = glm::vec4(0.2, 0.5, 0.8, 1.0);
			floorEntity.AddComponent<MaterialComponent>(floorMat);

			floorEntity.GetComponent<TransformComponent>().m_Position = glm::vec3(0);

			float floorLength{ 50.0f };
			floorEntity.GetComponent<TransformComponent>().m_Scale = glm::vec3(floorLength, 0.0f, floorLength);
			floorEntity.AddComponent<ColliderComponent>().AddPrimitive<PlaneCollider>(glm::vec3(0.0f, 1.0f, 0.0f), 0.0f);


			// --- PLAYER ---
			auto player{ CreateEntity() };
			player.AddComponent<CameraComponent>();
			player.AddComponent<ScriptComponent>().Bind<PlayerMoveScript>();
			player.GetComponent<TransformComponent>().m_Position = glm::vec3(10, 10, 10);
			SetMainCamera(player);
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
			auto m{ m_AssetsRef->LoadMesh(MODELS_DIR "sphere.obj") };
			auto localSize = m->GetBounds().size();
			auto worldSize = localSize * physicsTestEntity.GetComponent<TransformComponent>().m_Scale;

			physicsTestEntity.AddComponent<MeshComponent>(m);
			physicsTestEntity.AddComponent<NameComponent>("target");
			physicsTestEntity.GetComponent<TransformComponent>().m_Position = glm::vec3(0.0, 10.0f, 0.0f);
			auto& rb = physicsTestEntity.AddComponent<RigidbodyComponent>();
			rb.m_LinearVelocity = glm::vec3(1, 0, 0);
			rb.m_AngularVelocity = glm::vec3(1, 0, 0);
			physicsTestEntity.AddComponent<ForceGeneratorComponent>().Bind<GravityForceGenerator>(glm::vec3(0, -5, 0));

			physicsTestEntity.AddComponent<ColliderComponent>().AddPrimitive<SphereCollider>(worldSize.x/2.0f);

			rb.m_InverseMass = 1.0f;

			auto s{ m_AssetsRef->LoadShader(SHADERS_DIR "shader.vert", SHADERS_DIR "shader.frag") };

			auto mat{ m_AssetsRef->CreateMaterial("default", s, nullptr) };

			physicsTestEntity.AddComponent<MaterialComponent>(mat);

			// --- FLOOR ---
			auto floorEntity{ CreateEntity() };
			auto mesh{ m_AssetsRef->LoadMesh(MODELS_DIR "quad.obj") };
			floorEntity.AddComponent<MeshComponent>(mesh);

			auto floorMat{ m_AssetsRef->CreateMaterial("floor", s, nullptr) };
			floorMat->albedo = glm::vec4(0.2, 0.5, 0.8, 1.0);
			floorEntity.AddComponent<MaterialComponent>(floorMat);

			floorEntity.GetComponent<TransformComponent>().m_Position = glm::vec3(0);

			float floorLength{ 50.0f };
			floorEntity.GetComponent<TransformComponent>().m_Scale = glm::vec3(floorLength, 0.0f, floorLength);
			floorEntity.AddComponent<ColliderComponent>().AddPrimitive<PlaneCollider>(glm::vec3(0.0f, 1.0f, 0.0f), 0.0f);


			// --- PLAYER ---
			auto player{ CreateEntity() };
			player.AddComponent<CameraComponent>();
			player.AddComponent<ScriptComponent>().Bind<PlayerMoveScript>();
			player.GetComponent<TransformComponent>().m_Position = glm::vec3(10, 10, 10);
			SetMainCamera(player);
		}
	};
}
