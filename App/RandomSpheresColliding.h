#include "PhysicsEngine.h"
#include "PlayerMoveScript.h"
#include "Common.h"

#include <memory>
namespace Talk
{
    using namespace PhysicsEngine;
    
    class MovingSphereScript : public ScriptableEntity
    {
    public:
        glm::vec3 m_Velocity{ 0.0f };
        glm::vec3 m_RotationalVelocity{ 0.0f };
        float m_HalfExtent{ 100.0f };

        MovingSphereScript(glm::vec3 velocity, float halfExtent) : m_Velocity{ velocity }, m_HalfExtent{ halfExtent } {}

        void OnCreate() override
        {
        }

        void OnStart() override
        {
        }

        void OnUpdate(float dt) override
        {
            auto& transform = GetComponent<TransformComponent>();

            const glm::vec3& p = transform.m_Position;

            const bool outside =
                p.x < -m_HalfExtent || p.x > m_HalfExtent ||
                p.y < -m_HalfExtent || p.y > m_HalfExtent ||
                p.z < -m_HalfExtent || p.z > m_HalfExtent;

            if (outside)
            {
                GetComponent<MaterialComponent>().m_Material = nullptr;
            }
        }

        void OnDestroy() override
        {
        }
    };

    class SphereSpawnerScript : public ScriptableEntity
    {
    public:
        float m_BoxSideLength{ 100.0f };
        float m_SpawnInterval{ 0.5f };
        float m_MinSpeed{ 3.0f };
        float m_MaxSpeed{ 30.0f };
        float m_CubeScale = 3.0f;

        SphereSpawnerScript(float cubeScale) : m_CubeScale{ cubeScale } {}

    private:
        float m_SpawnTimer{ 0.0f };

    public:
        void OnCreate() override
        {
        }

        void OnStart() override
        {
        }

        void OnUpdate(float dt) override
        {
            m_SpawnTimer += dt;

            while (m_SpawnTimer >= m_SpawnInterval)
            {
                m_SpawnTimer -= m_SpawnInterval;
                SpawnCube();
            }
        }

        void OnDestroy() override
        {
        }

    private:
        void SpawnCube()
        {
            const float halfExtent = m_BoxSideLength * 0.5f;

            auto cube{ m_Scene->CreateEntity() };

            auto mesh = LoadMesh(MODELS_DIR "cube.obj");
            auto shader = LoadShader(SHADERS_DIR "shader.vert", SHADERS_DIR "shader.frag");
            auto material = CreateMaterial(shader, nullptr);

            // Random colour
            material->albedo = RandomColour();

            cube.AddComponent<NameComponent>("moving cube");
            cube.AddComponent<MeshComponent>(mesh);
            auto sharedMaterial = std::shared_ptr<Material>(std::move(material));
            cube.AddComponent<MaterialComponent>(sharedMaterial);

			auto localSize = mesh->GetBounds().size();
			auto worldSize = localSize * cube.GetComponent<TransformComponent>().m_Scale;

            cube.AddComponent<ColliderComponent>().AddPrimitive<BoxCollider>(localSize/2.0f);

            auto& transform = cube.GetComponent<TransformComponent>();
            transform.m_Position = RandomVec3(-halfExtent, halfExtent);
            transform.m_Scale = glm::vec3(m_CubeScale, m_CubeScale, m_CubeScale);

            auto vel{ glm::normalize(RandomVec3(-1.0f, 1.0f)) * RandomFloat(m_MinSpeed, m_MaxSpeed) };
            auto angVel{ glm::normalize(RandomVec3(-1.0f, 1.0f)) * RandomFloat(m_MinSpeed, m_MaxSpeed / 5.0f) };

            auto& rb { cube.AddComponent<RigidbodyComponent>() };
            rb.m_AngularVelocity = angVel;

            rb.m_LinearVelocity = vel;
            rb.m_AngularVelocity = angVel;

            cube.AddComponent<ScriptComponent>().Bind<MovingSphereScript>(vel,halfExtent);
        }
    };

    class RandomSpheresCollidingScene : public Scene
    {
        void SetUp() override
        {
            srand(static_cast<unsigned>(time(nullptr)));

            auto spawner = CreateEntity();
            spawner.AddComponent<NameComponent>("target");
            float cubeScale = 5.0f;
            spawner.AddComponent<ScriptComponent>().Bind<SphereSpawnerScript>(cubeScale);
     
            auto player = CreateEntity();
            player.AddComponent<ScriptComponent>().Bind<PlayerMoveScript>();
            player.AddComponent<CameraComponent>().m_Far = 500.0f;
            SetMainCamera(player);
        }
    };
}