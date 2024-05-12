//
// Created by SunHe on 2023/5/14.
//

#pragma once
#include "memory"
#include "Hazel/Renderer/Buffer.h"

namespace Hazel {
  class VertexArray {
  public:
    virtual ~VertexArray() {}

    virtual void Bind() const = 0;
    virtual void Unbind() const = 0;

    virtual void AddVertexBuffer(const Hazel::Ref<VertexBuffer>& vertexBuffer) = 0;
    virtual void SetIndexBuffer(const Hazel::Ref<IndexBuffer>& indexBuffer) = 0;

    virtual const std::vector<std::shared_ptr<VertexBuffer>>& GetVertexBuffer() const = 0;
    virtual const Hazel::Ref<IndexBuffer>& GetIndexBuffer() const = 0;

    static Hazel::Ref<VertexArray> Create();
  };
}