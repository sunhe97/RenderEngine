#pragma once

#include <string>
#include <unordered_map>
#include <glm/glm.hpp>

namespace Hazel {
	class Shader {
	public:
    Shader(const std::string& filePath) {}
		Shader(const std::string& vertecSrc, const std::string& fragmentSrc) {}
		virtual ~Shader() = default;
		virtual void Bind() const = 0;
		virtual void UnBind() const = 0;
    virtual void SetMat4(const std::string& name, const glm::mat4& value) = 0;
    virtual void SetFloat4(const std::string& name, const glm::vec4& value) = 0;
    virtual void SetFloat3(const std::string& name, const glm::vec3& value) = 0;
    virtual void SetInt(const std::string& name, int value) = 0;

    virtual const std::string& GetName() const = 0;
    static Ref<Shader> Create(const std::string& filePath);
    static Ref<Shader> Create(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc);
	};

  class ShaderLibrary {
  public:
    void Add(const Ref<Shader>& shader);
    void Add(const std::string& name, const Ref<Shader>& shader);
    Hazel::Ref<Hazel::Shader> Load(const std::string& filePath);
    Hazel::Ref<Hazel::Shader> Load(const std::string& name, const std::string& filePath);

    Ref<Shader> Get(const std::string& name);

    bool Exists(const std::string& name) const;
  private:
    std::unordered_map<std::string, Ref<Shader>> m_Shaders;
  };
}