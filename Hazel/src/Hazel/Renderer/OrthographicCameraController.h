//
// Created by SunHe on 2023/9/26.
//

#pragma once
#include "Hazel/Renderer/OrthographicsCamera.h"
#include "Hazel/Core/Timestep.h"
#include "Hazel/Events/ApplicationEvent.h"
#include "Hazel/Events/MouseEvent.h"

namespace Hazel {

  class OrthographicCameraController {
  public:
    OrthographicCameraController(float aspectRatio, bool rotation = false);
    void OnUpdate(Hazel::Timestep ts);
    void OnEvent(Hazel::Event& e);
    OrthographicsCamera& GetCamera() { return m_Camera; }
    const OrthographicsCamera& GetCamera() const { return m_Camera; }

    float GetZoomLevel() const { return m_ZoomLevel; }
    void SetZoomLevel(float zoomLevel) { m_ZoomLevel = zoomLevel; }

  private:
    bool OnMouseScrolled(Hazel::MouseScrolledEvent& e);
    bool OnWindowResized(Hazel::WindowResizeEvent& e);
  private:
    Hazel::OrthographicsCamera m_Camera;
    float m_AspectRatio;
    float m_ZoomLevel = 1.0f;

    bool m_Rotation = false;

    glm::vec3 m_CameraPosition = {0.0f, 0.0f, 0.0f};
    float m_CameraRotation = 0.0f;
    float m_CameraTranslationSpeed = 1.0f, m_CameraRotationSpeed = 1.0f;
  };

}
