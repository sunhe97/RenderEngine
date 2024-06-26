//
// Created by SunHe on 2023/8/30.
//

#pragma once
#include "Hazel/Renderer/Texture.h"
#include <string>
#include <glad/glad.h>
namespace Hazel{
class OpenGLTexture2D : public Texture2D {
public:
  OpenGLTexture2D(const std::string& path);
  OpenGLTexture2D(uint32_t width, uint32_t height);
  virtual ~OpenGLTexture2D();
  virtual uint32_t GetWidth() const override {return m_Width;}
  virtual uint32_t GetHeight() const override {return m_Height;}
  virtual void Bind(uint32_t slot) const override;
  virtual void SetData(void* data, uint32_t size) override;
private:
  uint32_t m_Width;
  uint32_t m_Height;
  std::string m_Path;
  uint32_t m_RendererID;
  GLenum m_InternalFormat, m_DataFormat;
};

} // namespace Hazel
