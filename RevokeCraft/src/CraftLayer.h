#include "MyRevoke.h"

#include "imgui.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp" 
#include <glm/gtc/type_ptr.hpp> 

namespace Revoke
{

	class CraftLayer : public Revoke::Layer
	{
	public:
		CraftLayer();

		void OnAttach() override;
		void OnDetach() override;

		void OnUpdate(Timestep deltaTime) override;
		void OnImGuiDraw() override;
		void OnEvent(Event& e) override;


	private:
		Shared <Texture2D> m_Texture2D;

		Shared<FrameBuffers> m_FrameBuffer;

		Shared<Scene> m_Scene;

		Entity m_SquereEntity;
		Entity m_CameraEntity;
		Entity m_SecondCamera;

		bool m_PrimaryCamera = true;
		glm::vec2 m_ViewportSize = { 0.0f, 0.0f };
		bool m_ViewportFocused = false;
		bool m_ViewportHovered = false;

		float m_Framerate = 0.0f;

		struct ProfileResult
		{
			const char* Name;
			float Time;
		};

		std::vector<ProfileResult> m_ProfileResults;
	};
}