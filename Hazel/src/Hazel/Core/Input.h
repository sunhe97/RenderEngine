#pragma once

#include "Hazel/Core/core.h"

namespace Hazel {
	class HAZEL_API Input {
	public:
		inline static bool IsKeyPressed(int keyCode) { return s_Instance->IsKeyPressedImpl(keyCode); }
		inline static bool IsMouseButtonPressed(int button) { return s_Instance->IsMouseButtonPressedImpl(button); }
		inline static bool GetMouseX() { return s_Instance->GetMouseXImpl(); }
		inline static bool GetMouseY() { return s_Instance->GetMouseYImpl(); }
		inline static std::pair<float, float> GetMousePos() { return s_Instance->GetMousePosImpl(); }

	protected:
		virtual bool IsKeyPressedImpl(int keyCode) = 0;
		virtual bool IsMouseButtonPressedImpl(int button) = 0;
		virtual float GetMouseXImpl() = 0;
		virtual float GetMouseYImpl() = 0;
		virtual std::pair<float, float> GetMousePosImpl() = 0;

	private:
		static Input* s_Instance;

	};



}