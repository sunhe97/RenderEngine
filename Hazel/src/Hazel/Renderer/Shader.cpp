//
// Created by SunHe on 2023/5/14.
//

#include "hzpch.h"
#include "Shader.h"
#include "Renderer.h"
#include "Platform/OpenGL/OpenGLShader.h"

namespace Hazel{
  Ref<Shader> Shader::Create(const std::string& filePath) {
    switch (Renderer::GetAPI()) {
      case RendererAPI::API::None:
        HZ_CORE_ASSERT(false, "RendererAPI::None is currently not supported!");
        return nullptr;
        break;
      case RendererAPI::API::OpenGL:
        return std::make_shared<OpenGLShader>(filePath);
        break;
    }

    HZ_CORE_ASSERT(false, "Unknown RendererAPI");
    return nullptr;
  }


  Ref<Shader> Shader::Create(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc) {
    switch (Renderer::GetAPI()) {
      case RendererAPI::API::None:
        HZ_CORE_ASSERT(false, "RendererAPI::None is currently not supported!");
        return nullptr;
        break;
      case RendererAPI::API::OpenGL:
        return std::make_shared<OpenGLShader>(name, vertexSrc, fragmentSrc);
        break;
    }

    HZ_CORE_ASSERT(false, "Unknown RendererAPI");
    return nullptr;
  }

  void ShaderLibrary::Add(const Ref <Shader> &shader) {
    auto& name = shader->GetName();
    Add(name, shader);
  }

  void ShaderLibrary::Add(const std::string &name, const Ref <Shader> &shader) {
    HZ_CORE_ASSERT(!Exists(name), "Shader already exists!");
    m_Shaders[name] = shader;
  }

  Hazel::Ref<Hazel::Shader> ShaderLibrary::Load(const std::string &filePath) {
    auto shader = Shader::Create(filePath);
    Add(shader);
    return shader;
  }

  Hazel::Ref<Hazel::Shader> ShaderLibrary::Load(const std::string &name, const std::string &filePath) {
    auto shader = Shader::Create(filePath);
    Add(name, shader);
    return shader;
  }

  Ref <Shader> ShaderLibrary::Get(const std::string &name) {
    HZ_CORE_ASSERT(Exists(name), "Shader not found!");
    return m_Shaders[name];
  }

  bool ShaderLibrary::Exists(const std::string &name) const {
    return m_Shaders.find(name) != m_Shaders.end();
  }

}