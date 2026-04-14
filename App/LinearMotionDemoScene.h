#include "PhysicsEngine.h"
#include "PlayerMoveScript.h"
#include "Common.h"

#include <memory>
namespace Talk
{
    using namespace PhysicsEngine;

    static float RandomFloat(float min, float max)
    {
        return min + (max - min) * (static_cast<float>(rand()) / static_cast<float>(RAND_MAX));
    }

    static glm::vec3 RandomVec3(float min, float max)
    {
        return glm::vec3(
            RandomFloat(min, max),
            RandomFloat(min, max),
            RandomFloat(min, max)
        );
    }

    static glm::vec4 RandomColour()
    {
        return glm::vec4(
            RandomFloat(0.0f, 1.0f),
            RandomFloat(0.0f, 1.0f),
            RandomFloat(0.0f, 1.0f),
            1.0f
        );
    }

    class MovingCubeScript : public ScriptableEntity
    {
    public:
        glm::vec3 m_Velocity{ 0.0f };
        float m_HalfExtent{ 100.0f };

        MovingCubeScript(glm::vec3 velocity, float halfExtent) : m_Velocity{ velocity }, m_HalfExtent{ halfExtent } {}

        void OnCreate() override
        {
        }

        void OnStart() override
        {
        }

        void OnUpdate(float dt) override
        {
            auto& transform = GetComponent<TransformComponent>();

            transform.m_Position += m_Velocity * dt;

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

    class CubeSpawnerScript : public ScriptableEntity
    {
    public:
        float m_BoxSideLength{ 300.0f };
        float m_SpawnInterval{ 0.01f };
        float m_MinSpeed{ 3.0f };
        float m_MaxSpeed{ 10.0f };

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

            auto& transform = cube.GetComponent<TransformComponent>();
            transform.m_Position = RandomVec3(-halfExtent, halfExtent);

            auto vel{ glm::normalize(RandomVec3(-1.0f, 1.0f)) * RandomFloat(m_MinSpeed, m_MaxSpeed) };

            cube.AddComponent<ScriptComponent>().Bind<MovingCubeScript>(vel,halfExtent);
        }
    };

    class LinearMotionDemoScene : public Scene
    {
        void SetUp() override
        {
            srand(static_cast<unsigned>(time(nullptr)));

            auto spawner = CreateEntity();
            spawner.AddComponent<NameComponent>("target");
            spawner.AddComponent<ScriptComponent>().Bind<CubeSpawnerScript>();
     
            auto player = CreateEntity();
            player.AddComponent<ScriptComponent>().Bind<PlayerMoveScript>();
            player.AddComponent<CameraComponent>().m_Far = 500.0f;
            SetMainCamera(player);
        }
    };
}