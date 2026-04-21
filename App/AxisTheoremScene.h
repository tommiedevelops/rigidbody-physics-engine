#include "PhysicsEngine.h"
#include "PlayerMoveScript.h"
#include "Common.h"
#include <iostream>

namespace Talk
{
	class AxisTheoremScene : public Scene {

		class RacketScript : public ScriptableEntity
		{
			void OnCreate() override {}
			void OnStart() override
			{
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
			float w = 1.0f, h = 5.0f, d = 10.0f;
			float mass = 1.0f;
			float angVel = 5.0f;

			glm::mat3 inertiaTensor(0.0f);

			inertiaTensor[0][0] = 1.0f / 12.0f * mass * (h * h + d * d); 		
			inertiaTensor[1][1] = 1.0f / 12.0f * mass * (w * w + d * d);  
			inertiaTensor[2][2] = 1.0f / 12.0f * mass * (w * w + h * h);  
	
			auto mesh{m_AssetsRef->LoadMesh(MODELS_DIR "cube.obj")};
			auto shader{ m_AssetsRef->LoadShader(SHADERS_DIR "shader.vert", SHADERS_DIR "shader.frag") };
			auto material = m_AssetsRef->CreateMaterial("mat",shader, nullptr);
			material->albedo = glm::vec4(0.3, 0.4, 0.5, 1);

			auto xBox = CreateEntity();
			xBox.AddComponent<MeshComponent>(mesh);
			xBox.AddComponent<MaterialComponent>(material);
			auto& xTr{ xBox.GetComponent<TransformComponent>() };
			xTr.m_Position = glm::vec3(-30, 0, 0);
			xTr.m_Scale = glm::vec3(w, h, d);
			xBox.AddComponent<RigidbodyComponent>().m_AngularVelocity = glm::vec3(angVel, 0, 0);
			xBox.AddComponent<ScriptComponent>().Bind<RacketScript>();

			auto yBox = CreateEntity();
			yBox.AddComponent<MeshComponent>(mesh);
			yBox.AddComponent<MaterialComponent>(material);
			auto& yTr{ yBox.GetComponent<TransformComponent>() };
			yTr.m_Position = glm::vec3(0, 0, 0);
			yTr.m_Scale = glm::vec3(w, h, d);
			yBox.AddComponent<RigidbodyComponent>().m_AngularVelocity = glm::vec3(0,angVel, 0);
			yBox.AddComponent<NameComponent>("target");
			yBox.AddComponent<ScriptComponent>().Bind<RacketScript>();

			auto zBox = CreateEntity();
			zBox.AddComponent<MeshComponent>(mesh);
			zBox.AddComponent<MaterialComponent>(material);
			auto& zTr{ zBox.GetComponent<TransformComponent>() };
			zTr.m_Position = glm::vec3(30, 0, 0);
			zTr.m_Scale = glm::vec3(w, h, d);
			zBox.AddComponent<RigidbodyComponent>().m_AngularVelocity = glm::vec3(0,0,angVel);
			zBox.AddComponent<ScriptComponent>().Bind<RacketScript>();

			// --- PLAYER ---
			auto player{ CreateEntity() };
			player.AddComponent<CameraComponent>();
			player.AddComponent<ScriptComponent>().Bind<PlayerMoveScript>();
			player.GetComponent<TransformComponent>().m_Position = glm::vec3(0, 50, 50);
			SetMainCamera(player);
			GetMainCamera()->m_Far = 500.0f;
		}
	};
}