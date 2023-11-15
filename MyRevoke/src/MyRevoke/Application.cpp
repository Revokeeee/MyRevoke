#include "rvpch.h"
#include "Application.h"
#include "Log.h"
#include "Input.h"

#include "Renderer/Renderer.h"
#include "Renderer/RenderCommand.h"

#include "GLFW/glfw3.h"

namespace Revoke
{
	
	Application* Application::s_Instance = nullptr;
	

	Application::Application()
	
	{
	
		RV_CORE_ASSERT(!s_Instance, "Applicatio already exist");
		s_Instance = this;

		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->SetEventCallback(RV_BIND_EVENT_FUNK(Application::OnEvent));

		m_ImGuiLayer = new ImGuiLayer();
		PushOverlay(m_ImGuiLayer);

	}
	Application::~Application()
	{
	
	}
	void Application::Run()
	{
	
		while (m_Run)
		{
			float time = (float)glfwGetTime();
			Timestep timestep = time - m_LastFrame;
			m_LastFrame = time;

			for (Layer* layer : m_LayerStack)
				layer->OnUpdate(timestep);

			m_ImGuiLayer->Begin();
			for (Layer* layer : m_LayerStack)
				layer->OnImGuiDraw();
			m_ImGuiLayer->End();


			m_Window->OnUpdate();
		}
	}
	void Application::OnEvent(Event& e)
	{
		
		EventDispatcher eDispatcher(e);
		
		eDispatcher.Dispatch<WindowsCloseEvent>(RV_BIND_EVENT_FUNK(Application::OnWindowsClose));


		for (auto it = m_LayerStack.end(); it != m_LayerStack.begin();)
		{
			(*--it)->OnEvent(e);
			if (e.Handled)
				break;
		}

	}
	void Application::PushLayer(Layer* layer)
	{
		m_LayerStack.PushLayer(layer);
	}
	void Application::PushOverlay(Layer* layer)
	{
		m_LayerStack.PushOverlay(layer);
	}
	bool Application::OnWindowsClose(WindowsCloseEvent e)
	{
		m_Run = false;
		return true;
	}
}