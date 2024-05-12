#pragma once
#include "Hazel/Core/Window.h"
#include "Hazel/Renderer/GraphicsContext.h"

#include "GLFW/glfw3.h"


namespace Hazel {
	class HAZEL_API WindowsWindow :
		public Window
	{
	public:
		WindowsWindow(const WindowProps& props);
		virtual ~WindowsWindow();

		void OnUpdate() override;

		inline unsigned int GetWidth() const override { return m_Data.Width; }
		inline unsigned int GetHeight() const override { return m_Data.Height; }

		inline void SetEventCallback(const EventCallbackFn& callback) override { m_Data.EventCallback = callback; }
		void SetVSync(bool enabled);
		bool IsVSync()const;

		inline virtual void* GetNativeWindow() const override { return m_Window; }



	private:

		virtual void Init(const WindowProps& props);
		virtual void ShutDown();
	private:
		GLFWwindow* m_Window;

		GraphicsContext* m_Context;

		struct WindowData {
			unsigned int Height;
			unsigned int Width;
			std::string Title;
			bool VSync;
			EventCallbackFn EventCallback;

		};

		WindowData m_Data;
	};

}


