//
// Created by SunHe on 2023/5/14.
//

#include "hzpch.h"
#include "Buffer.h"
#include "Renderer.h"
#include "Platform/OpenGL/OpenGLBuffer.h"

namespace Hazel {

  VertexBuffer *VertexBuffer::Create(float *vertices, uint32_t size) {
    switch (Renderer::GetAPI()) {
      case RendererAPI::API::None:
        HZ_CORE_ASSERT(false, "RendererAPI::None is currently not supported!");
        return nullptr;
        break;
      case RendererAPI::API::OpenGL:
        return new OpenGLVertexBuffer(vertices, size);
        break;
    }

    HZ_CORE_ASSERT(false, "Unknown RendererAPI");
    return nullptr;
  }

  IndexBuffer *IndexBuffer::Create(uint32_t *indices, uint32_t size) {
    switch (Renderer::GetAPI()) {
      case RendererAPI::API::None:
        HZ_CORE_ASSERT(false, "RendererAPI::None is currently not supported!");
        return nullptr;
        break;
      case RendererAPI::API::OpenGL:
        return new OpenGLIndexBuffer(indices, size);
        break;
    }

    HZ_CORE_ASSERT(false, "Unknown RendererAPI");
    return nullptr;
  }
}