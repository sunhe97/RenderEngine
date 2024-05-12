//
// Created by SunHe on 2023/5/14.
//
#include "hzpch.h"
#include "Renderer.h"
#include "Platform/OpenGL/OpenGLShader.h"
#include "Hazel/Renderer/Renderer2D.h"

namespace Hazel {
  Renderer::SceneData* Renderer::m_SceneData = new Renderer::SceneData;
  void Renderer::BeginScene(OrthographicsCamera& camera) {
    m_SceneData->ViewProjectMatrix = camera.GetViewProjectionMatrix();
  }

  void Renderer::EndScene() {

  }

  void Renderer::Submit(const Hazel::Ref<Shader>& shader, const Hazel::Ref<VertexArray>& vertexArray,
                        const glm::mat4& transform) {
    shader->Bind();

    std::dynamic_pointer_cast<OpenGLShader>(shader)->UploadUniformMat4("u_ViewProjection", m_SceneData->ViewProjectMatrix);
    std::dynamic_pointer_cast<OpenGLShader>(shader)->UploadUniformMat4("u_Transform", transform);
    vertexArray->Bind();
    RenderCommand::DrawIndexed(vertexArray);
  }

  void Renderer::Init() {
    RenderCommand::Init();
    Renderer2D::Init();
  }

  void Renderer::OnWindowResize(uint32_t width, uint32_t height) {
    RenderCommand::SetViewport(0, 0, width, height);

  }
}