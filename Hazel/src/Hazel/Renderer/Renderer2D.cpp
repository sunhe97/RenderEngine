//
// Created by SunHe on 2023/10/10.
//

#include "Renderer2D.h"
#include "Hazel/Renderer/VertexArray.h"

#include "Hazel/Renderer/Shader.h"
#include "Hazel/Renderer/RenderCommand.h"
#include "glm/gtx/transform.hpp"

namespace Hazel {

  struct Renderer2DStorage {
    Ref<VertexArray> QuadVertexArray;
    Ref<Shader> TextureShader;
    Ref<Texture2D> WhiteTexture;
  };

  static Renderer2DStorage* s_Data;

  void Hazel::Renderer2D::Init() {
    s_Data = new Renderer2DStorage();
    s_Data->QuadVertexArray = Hazel::VertexArray::Create();

    float squareVertices[5 * 4] = {
            -0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
            0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
            0.5f, 0.5f, 0.0f, 1.0f, 1.0f,
            -0.5f, 0.5f, 0.0f, 0.0f, 1.0f
    };

    Hazel::Ref<Hazel::VertexBuffer> sqaureVB;
    sqaureVB.reset(Hazel::VertexBuffer::Create(squareVertices, sizeof(squareVertices)));
    sqaureVB->SetLayout({
                                {Hazel::ShaderDataType::Float3, "a_Position"},
                                {Hazel::ShaderDataType::Float2, "a_TextCoord"}

                        });
    s_Data->QuadVertexArray->AddVertexBuffer(sqaureVB);
    unsigned int sqaureIndices[6] = { 0, 1, 2, 2, 3,0 };
    Hazel::Ref<Hazel::IndexBuffer> sqaureIB;
    sqaureIB.reset(Hazel::IndexBuffer::Create(sqaureIndices, sizeof(sqaureIndices) /sizeof(uint32_t)));
    s_Data->QuadVertexArray->SetIndexBuffer(sqaureIB);

    s_Data->WhiteTexture = Hazel::Texture2D::Create(1, 1);
    uint32_t whiteTextureData = 0xffffffff;
    s_Data->WhiteTexture->SetData(&whiteTextureData, sizeof(whiteTextureData));

    s_Data->TextureShader = Hazel::Shader::Create("C:\\Users\\SunHe\\Desktop\\hazil\\Sandbox\\assets\\shaders\\Texture.glsl");
    s_Data->TextureShader->Bind();
    s_Data->TextureShader->SetInt("u_Texture", 0);
  }

  void Hazel::Renderer2D::Shutdown() {
    delete s_Data;
  }

  void Hazel::Renderer2D::BeginScene(const Hazel::OrthographicsCamera &camera) {
    s_Data->TextureShader->Bind();
    s_Data->TextureShader->SetMat4("u_ViewProjection", camera.GetViewProjectionMatrix());

  }

  void Hazel::Renderer2D::EndScene() {

  }

  void Hazel::Renderer2D::DrawQuad(const glm::vec2 &position, const glm::vec2 &size, const glm::vec4 &color) {
    DrawQuad({position.x, position.y, 0.0f}, size, color);
  }

  void Hazel::Renderer2D::DrawQuad(const glm::vec3 &position, const glm::vec2 &size, const glm::vec4 &color) {
    s_Data->TextureShader->SetFloat4("u_Color", color);
    s_Data->WhiteTexture->Bind();

    glm::mat4 translation = glm::translate(glm::mat4(1.0f), position) * glm::scale(glm::mat4(1.0f), {size.x, size.y, 1.0f});
    s_Data->TextureShader->SetMat4("u_Transform", translation);
    s_Data->QuadVertexArray->Bind();
    Hazel::RenderCommand::DrawIndexed(s_Data->QuadVertexArray);
  }

  void Renderer2D::DrawQuad(const glm::vec2 &position, const glm::vec2 &size, const Ref <Texture2D> &texture) {
    DrawQuad({position.x, position.y, 0.0f}, size, texture);
  }

  void Renderer2D::DrawQuad(const glm::vec3 &position, const glm::vec2 &size, const Ref <Texture2D> &texture) {
    s_Data->TextureShader->SetFloat4("u_Color", glm::vec4(1.0f));

    texture->Bind();

    glm::mat4 translation = glm::translate(glm::mat4(1.0f), position) * glm::scale(glm::mat4(1.0f), {size.x, size.y, 1.0f});
    s_Data->TextureShader->SetMat4("u_Transform", translation);
    s_Data->QuadVertexArray->Bind();
    Hazel::RenderCommand::DrawIndexed(s_Data->QuadVertexArray);
  }

}