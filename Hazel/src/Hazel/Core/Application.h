#pragma once

#include "core.h"
#include "Hazel/Events/Event.h"
#include "LayerStack.h"
#include "Hazel/Events/ApplicationEvent.h"
#include "Window.h"
#include "Hazel/ImGui/ImGuiLayer.h"
#include "Hazel/Core/Timestep.h"


namespace Hazel {
	class HAZEL_API Application
	{
	public:
		Application(); 
		virtual ~Application();

		void Run();

		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);

		inline static Application& Get() { return *s_Instance; }

		inline Window& GetWindow() { return *m_Window; }
	private:
		bool OnWindowClose(WindowCloseEvent& e);
    	bool OnWindowResize(WindowResizeEvent& e);
  private:
		std::unique_ptr<Window> m_Window;
		bool m_Running = true;
    	bool m_Minimized = false;
		LayerStack m_LayerStack;
		ImGuiLayer* m_ImGuiLayer;
    float m_LastFrameTime = 0.0f;
  private:
		static Application* s_Instance;
	};

	//TO be defined in client
	Application* CreateApplication();
}

