#include "hzpch.h"
#include "OpenGLShader.h"
#include "glad/glad.h"
#include <glm/gtc/type_ptr.hpp>

namespace Hazel {

  static GLenum ShaderTypeFromString(const std::string& type) {
    if (type == "vertex") {
      return GL_VERTEX_SHADER;
    }
    if (type == "fragment" || type == "pixel") {
      return GL_FRAGMENT_SHADER;
    }
    HZ_CORE_ASSERT(false, "Unknown shader type!");
    return 0;
  }

  OpenGLShader::OpenGLShader(const std::string &filePath) : Shader(filePath) {

    std::string shader_source = ReadFile(filePath);
    auto shader_sources = PreProcess(shader_source);
    Compile(shader_sources);

    // assets/shaders/Texture.glsl extract name from path
    auto last_slash = filePath.find_last_of("/\\");
    last_slash = last_slash == std::string::npos ? 0 : last_slash + 1;
    auto last_dot = filePath.rfind('.');
    auto count = last_dot == std::string::npos ? filePath.size() - last_slash : last_dot - last_slash;
    m_Name = filePath.substr(last_slash, count);
  }


  OpenGLShader::OpenGLShader(const std::string& name, const std::string &vertexSrc, const std::string &fragmentSrc) :
  Shader(vertexSrc, fragmentSrc), m_Name(name) {
    std::unordered_map<GLenum, std::string> shaderSources;
    shaderSources[GL_VERTEX_SHADER] = vertexSrc;
    shaderSources[GL_FRAGMENT_SHADER] = fragmentSrc;
    Compile(shaderSources);
  }

  OpenGLShader::~OpenGLShader() {
    glDeleteProgram(m_RendererID);
  }

  void OpenGLShader::Bind() const {
    glUseProgram(m_RendererID);
  }

  void OpenGLShader::UnBind() const {
    glUseProgram(0);
  }

  void OpenGLShader::UploadUniformMat4(const std::string& name, const glm::mat4 &matrix) {
    GLint location = glGetUniformLocation(m_RendererID, name.c_str());
    glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
  }

  void OpenGLShader::UploadUniformInt(const std::string &name, int value) {
    GLint location = glGetUniformLocation(m_RendererID, name.c_str());
    glUniform1i(location, value);
  }

  void OpenGLShader::UploadUniformFloat(const std::string &name, float value) {
    GLint location = glGetUniformLocation(m_RendererID, name.c_str());
    glUniform1f(location, value);
  }

  void OpenGLShader::UploadUniformFloat2(const std::string &name, const glm::vec2 &value) {
    GLint location = glGetUniformLocation(m_RendererID, name.c_str());
    glUniform2f(location, value.x, value.y);
  }

  void OpenGLShader::UploadUniformFloat3(const std::string &name, const glm::vec3 &value) {
    GLint location = glGetUniformLocation(m_RendererID, name.c_str());
    glUniform3f(location, value.x, value.y, value.z);
  }

  void OpenGLShader::UploadUniformFloat4(const std::string &name, const glm::vec4 &value) {
    GLint location = glGetUniformLocation(m_RendererID, name.c_str());
    glUniform4f(location, value.x, value.y, value.z, value.w);
  }

  void OpenGLShader::UploadUniformMat3(const std::string &name, const glm::mat3 &matrix) {
    GLint location = glGetUniformLocation(m_RendererID, name.c_str());
    glUniformMatrix3fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
  }

  std::string OpenGLShader::ReadFile(const std::string &filePath) {
    std::ifstream in(filePath, std::ios::in | std::ios::binary);
    std::string result;
    if(in) {
      in.seekg(0, std::ios::end);
      result.resize(in.tellg());
      in.seekg(0, std::ios::beg);
      in.read(&result[0], result.size());
    } else {
      HZ_CORE_ERROR("Could not open file '{0}'", filePath);
    }
    return result;
  }

  void OpenGLShader::Compile(const std::unordered_map<GLenum, std::string> &shaderSources) {
    GLuint program = glCreateProgram();
    HZ_CORE_ASSERT(shaderSources.size() <= 2, "We only support 2 shaders for now!");
    std::array<GLenum, 2> glShaderIDs{};
    int glShaderIDIndex = 0;
//    glShaderIDs.reserve(shaderSources.size());
    for(auto& vf : shaderSources) {
      auto type = vf.first;
      const std::string& source_shader = vf.second;
      GLuint Shader = glCreateShader(type);

      const GLchar* source = source_shader.c_str();
      glShaderSource(Shader, 1, &source, 0);
// Compile the vertex shader
      glCompileShader(Shader);

      GLint isCompiled = 0;
      glGetShaderiv(Shader, GL_COMPILE_STATUS, &isCompiled);
      if(isCompiled == GL_FALSE)
      {
        GLint maxLength = 0;
        glGetShaderiv(Shader, GL_INFO_LOG_LENGTH, &maxLength);

        // The maxLength includes the NULL character
        std::vector<GLchar> infoLog(maxLength);
        glGetShaderInfoLog(Shader, maxLength, &maxLength, &infoLog[0]);

        // We don't need the shader anymore.
        glDeleteShader(Shader);

        HZ_CORE_ERROR(type + "Shader compilation failure!");
        HZ_CORE_ERROR("{0}", infoLog.data());
        HZ_CORE_ASSERT(false, type + "shader compilation failure!");
        break;
      }
      glAttachShader(program, Shader);
      glShaderIDs[glShaderIDIndex++] = Shader;
    }

// Link our program
    glLinkProgram(program);

// Note the different functions here: glGetProgram* instead of glGetShader*.
    GLint isLinked = 0;
    glGetProgramiv(program, GL_LINK_STATUS, (int*)&isLinked);
    if (isLinked == GL_FALSE)
    {
      GLint maxLength = 0;
      glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);

      // The maxLength includes the NULL character
      std::vector<GLchar> infoLog(maxLength);
      glGetProgramInfoLog(program, maxLength, &maxLength, &infoLog[0]);

      // We don't need the m_RendererID anymore.
      glDeleteProgram(program);
      // Don't leak shaders either.
      for (auto id : glShaderIDs)
        glDeleteShader(id);


      HZ_CORE_ERROR("Shader link failure!");
      HZ_CORE_ERROR("{0}", infoLog.data());
      HZ_CORE_ASSERT(false, "Shader link failure!");
      return;
    }

// Always detach shaders after a successful link.
  for (auto id : glShaderIDs)
    glDetachShader(program, id);
    m_RendererID = program;
  }

  std::unordered_map<GLenum, std::string> OpenGLShader::PreProcess(const std::string &source) {
    std::unordered_map<GLenum, std::string> shaderSources;
    std::string typeToken = "#type";
    size_t typeTokenLength = typeToken.length();
    size_t pos = source.find( typeToken, 0);
    while(pos != std::string::npos) {
      size_t type_end_pos = source.find_first_of("\r\n", pos);
      size_t type_start_pos = pos + typeTokenLength + 1;
      std::string type = source.substr(type_start_pos, type_end_pos - type_start_pos);
      HZ_CORE_ASSERT(ShaderTypeFromString(type), "Invalid shader type specified!");
      size_t shader_code_start_pos = source.find_first_not_of("\r\n", type_end_pos);
      pos = source.find(typeToken, shader_code_start_pos);
      shaderSources[ShaderTypeFromString(type)] = source.substr(shader_code_start_pos,
                                                                pos == std::string::npos ? source.size() - shader_code_start_pos : pos - shader_code_start_pos );
    }
    return shaderSources;
  }

  void OpenGLShader::SetMat4(const std::string& name, const glm::mat4 &value) {
    UploadUniformMat4(name, value);
  }
  void OpenGLShader::SetFloat(const std::string& name, float value) {
    UploadUniformFloat(name, value);
  }
  void OpenGLShader::SetFloat4(const std::string& name, const glm::vec4 &value) {
    UploadUniformFloat4(name, value);
  }

  void OpenGLShader::SetFloat3(const std::string& name, const glm::vec3 &value) {
    UploadUniformFloat3(name, value);
  }

  void OpenGLShader::SetInt(const std::string &name, int value) {
    UploadUniformInt(name, value);
  }


}