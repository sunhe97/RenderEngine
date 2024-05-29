//
// Created by SunHe on 2023/10/9.
//
#include "hzpch.h"
#include "Sandbox2D.h"

#include <chrono>
#include <glm/gtc/matrix_transform.hpp>

#include "Hazel.h"
#include "Hazel/Renderer/Shader.h"
#include "Platform/OpenGL/OpenGLShader.h"
#include "glm/gtc/type_ptr.hpp"

#include "imgui/imgui.h"

Sandbox2D::Sandbox2D()
    : Hazel::Layer("Sandbox2D"), m_CameraController(1280.0f / 720.0f) {}

void Sandbox2D::OnAttach() {
  m_CheckerBoardTexture = Hazel::Texture2D::Create(
      "C:\\Users\\SunHe\\Desktop\\Hazel\\Sandbox\\assets\\textures\\Checkerboard.png");
}

void Sandbox2D::OnDetach() {}

void Sandbox2D::OnUpdate(Hazel::Timestep ts) {
  HZ_PROFILE_FUNCTION();
  {
    HZ_PROFILE_SCOPE("CameraController::OnUpdate");
    m_CameraController.OnUpdate(ts);
  }

  {
    HZ_PROFILE_SCOPE("Rendered Prep");
    Hazel::RenderCommand::SetClearColor({0.1f, 0.1f, 0.1f, 1});
    Hazel::RenderCommand::Clear();
  }

  {
    HZ_PROFILE_SCOPE("Rendered scene");
    Hazel::Renderer2D::BeginScene(m_CameraController.GetCamera());
    //  glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));
    //  std::dynamic_pointer_cast<Hazel::OpenGLShader>(m_FlatColorShader)->Bind();
    //  std::dynamic_pointer_cast<Hazel::OpenGLShader>(m_FlatColorShader)->UploadUniformFloat4("u_Color",
    //  m_SquareColor);
    //
    //  Hazel::Renderer2D::Submit(m_FlatColorShader, m_SquareVA,
    //  glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));
    Hazel::Renderer2D::DrawQuad({-1.0f, 0.0f}, {0.8f, 0.8f},
                                {0.8f, 0.2f, 0.3f, 1.0f});
    Hazel::Renderer2D::DrawQuad({0.5f, -0.5f}, {0.5f, 0.75f},
                                {0.2f, 0.3f, 0.8f, 1.0f});
    Hazel::Renderer2D::DrawQuad({0.0f, 0.0f, -0.1}, {10.0f, 10.0f},
                                m_CheckerBoardTexture, 10.0f);

    Hazel::Renderer2D::EndScene();
  }
}

void Sandbox2D::OnImGuiRender() {
  ImGui::Begin("Settings");
  ImGui::ColorEdit4("Square Color", glm::value_ptr(m_SquareColor));
  ImGui::End();
}

void Sandbox2D::OnEvent(Hazel::Event &e) { m_CameraController.OnEvent(e); }
