//
// Created by SunHe on 2023/10/9.
//

#pragma once
#include "Hazel/Core/Layer.h"
#include "glm/glm.hpp"
#include "Hazel/Renderer/OrthographicCameraController.h"
#include "Hazel/Renderer/Texture.h"

namespace Hazel {
  class Shader;
  class VertexArray;
  class OrthographicCameraController;
}
class Sandbox2D : public Hazel::Layer{
public:
  Sandbox2D();
  virtual ~Sandbox2D() = default;
  void OnAttach() override;
  void OnDetach() override;

  void OnUpdate(Hazel::Timestep ts) override;
  virtual void OnImGuiRender() override;
  void OnEvent(Hazel::Event& e) override;
private:
  Hazel::Ref<Hazel::Shader>  m_FlatColorShader;
  Hazel::Ref<Hazel::VertexArray>  m_SquareVA;

  Hazel::OrthographicCameraController m_CameraController;

  Hazel::Ref<Hazel::Texture2D> m_CheckerBoardTexture;

  glm::vec4 m_SquareColor = { 0.2f, 0.3f, 0.8f,  1.0f};

};



