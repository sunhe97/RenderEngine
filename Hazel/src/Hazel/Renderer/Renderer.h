//
// Created by SunHe on 2023/5/14.
//
#pragma once
#include "RendererAPI.h"
#include "RenderCommand.h"
#include "Hazel/Renderer/OrthographicsCamera.h"
#include "Hazel/Renderer/Shader.h"

namespace Hazel{

  class Renderer {
  public:
    static void Init();
    static void OnWindowResize(uint32_t width, uint32_t height);
    static void BeginScene(OrthographicsCamera& camera);
    static void EndScene();

    static void Submit( const Hazel::Ref<Shader>& shader, const Hazel::Ref<VertexArray>& vertexArray,
                        const glm::mat4& transform = glm::mat4(1.0f));

    inline static RendererAPI::API GetAPI() {return RendererAPI::GetAPI();}

  private:
    struct SceneData {
      glm::mat4 ViewProjectMatrix;
    };

    static SceneData* m_SceneData;
  };
}