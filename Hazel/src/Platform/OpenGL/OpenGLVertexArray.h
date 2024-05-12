//
// Created by SunHe on 2023/5/14.
//

#pragma once
#include "vector"
#include "Hazel/Renderer/VertexArray.h"

namespace Hazel{

  class OpenGLVertexArray : public VertexArray {
    public:
    OpenGLVertexArray();
     virtual ~OpenGLVertexArray();

     virtual void Bind() const override;
     virtual void Unbind() const override;

     virtual void AddVertexBuffer(const Hazel::Ref<VertexBuffer>& vertexBuffer) override;
     virtual void SetIndexBuffer(const Hazel::Ref<IndexBuffer>& indexBuffer) override;

     virtual const std::vector<Hazel::Ref<VertexBuffer>>& GetVertexBuffer() const override {return m_VertexBuffers;};
     virtual const Hazel::Ref<IndexBuffer>& GetIndexBuffer() const override {return m_IndexBuffer;}
  private:
    std::vector<Hazel::Ref<VertexBuffer>> m_VertexBuffers;
    Hazel::Ref<IndexBuffer> m_IndexBuffer;
    uint32_t m_RendererID;
  };


}

