//
// Created by SunHe on 2023/5/28.
//
#include "hzpch.h"
#include "RenderCommand.h"
#include "Platform/OpenGL/OpenGLRendererAPI.h"

namespace Hazel {
  RendererAPI* RenderCommand::s_RendererAPI = new OpenGLRendererAPI;
}