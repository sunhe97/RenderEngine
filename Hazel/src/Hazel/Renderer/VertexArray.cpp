//
// Created by SunHe on 2023/5/14.
//

#include "hzpch.h"
#include "VertexArray.h"
#include "Renderer.h"
#include "Platform/OpenGL/OpenGLVertexArray.h"
#include "memory"

namespace Hazel{
  Hazel::Ref<VertexArray> VertexArray::Create() {
    switch (Renderer::GetAPI()) {
      case RendererAPI::API::None:
        HZ_CORE_ASSERT(false, "RendererAPI::None is currently not supported!");
        return nullptr;
        break;
      case RendererAPI::API::OpenGL:
        return std::make_shared<OpenGLVertexArray>();
        break;
    }

    HZ_CORE_ASSERT(false, "Unknown RendererAPI");
    return nullptr;
  }
}