#include "hzpch.h"
#include "Hazel.h"
#include "Hazel/Core/EntryPoint.h"
#include "imgui/imgui.h"

#include <glm/gtc/matrix_transform.hpp>
#include "Hazel/Renderer/Shader.h"
#include "Platform/OpenGL/OpenGLShader.h"
#include "glm/gtc/type_ptr.hpp"
#include "Hazel/Renderer/Shader.h"
#include "Sandbox2D.h"

class ExampleLayer :public Hazel::Layer
{
public:
	ExampleLayer()
		:Layer("example"),  m_CameraController(1280.0f / 720.0f)
	{

    m_VertexArray = Hazel::VertexArray::Create();

    float vertices[3 * 7] = {
            -0.5f, -0.5f, -0.0f, 0.8f, 0.2f, 0.8f, 1.0f,
            0.5f, -0.5f, -0.0f, 0.2f, 0.3f, 0.8f, 1.0f,
            0.0f, 0.5f, -0.0f, 0.8f, 0.8f, 0.2f, 1.0f
    };

    Hazel::Ref<Hazel::VertexBuffer> vertexBuffer;
    vertexBuffer.reset(Hazel::VertexBuffer::Create(vertices, sizeof(vertices)));

    Hazel::BufferLayout layout = {
            {Hazel::ShaderDataType::Float3, "a_Position"},
            {Hazel::ShaderDataType::Float4, "a_Color"}
    };
    vertexBuffer->SetLayout(layout);

    m_VertexArray->AddVertexBuffer(vertexBuffer);


    unsigned int indices[3] = { 0, 1, 2 };
    Hazel::Ref<Hazel::IndexBuffer> indexBuffer;
    indexBuffer.reset(Hazel::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
    m_VertexArray->SetIndexBuffer(indexBuffer);

    m_SquareVA = Hazel::VertexArray::Create();

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
    m_SquareVA->AddVertexBuffer(sqaureVB);
    unsigned int sqaureIndices[6] = { 0, 1, 2, 2, 3,0 };
    Hazel::Ref<Hazel::IndexBuffer> sqaureIB;
    sqaureIB.reset(Hazel::IndexBuffer::Create(sqaureIndices, sizeof(sqaureIndices) /sizeof(uint32_t)));
    m_SquareVA->SetIndexBuffer(sqaureIB);

    std::string vertexSrc = R"(
      #version 330 core

      layout(location = 0) in vec3 a_Position;
      layout(location = 1) in vec4 a_Color;

      uniform mat4 u_ViewProjection;
      uniform mat4 u_Transform;


      out vec3 v_Position;
      out vec4 v_Color;
      void main()
      {
        v_Position = a_Position;
        v_Color = a_Color;
        gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);
      }

)";
    std::string fragmentSrc = R"(
      #version 330 core

      layout(location = 0) out vec4 color;
      in vec3 v_Position;
      in vec4 v_Color;
      void main()
      {
        color = vec4(v_Position, 1.0);
        color = v_Color;
      }
    )";

    m_Shader = Hazel::Shader::Create("VertexColorTriangle", vertexSrc, fragmentSrc);

    std::string blueSqaureVertexSrc = R"(
      #version 330 core

      layout(location = 0) in vec3 a_Position;
      uniform mat4 u_ViewProjection;
      uniform mat4 u_Transform;
      out vec3 v_Position;
      void main()
      {
        v_Position = a_Position;
        gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);
      }

)";
    std::string blueSquareFragmentSrc = R"(
      #version 330 core

      layout(location = 0) out vec4 color;
      in vec3 v_Position;
      uniform vec3 u_Color;
      void main()
      {
        color = vec4(u_Color, 1.0);
      }
    )";

    m_SqaureShader = Hazel::Shader::Create("blueSquare", blueSqaureVertexSrc, blueSquareFragmentSrc);

    std::string textureShaderVertexSrc = R"(
      #version 330 core

      layout(location = 0) in vec3 a_Position;
      layout(location = 1) in vec2 a_TextCoord;
      uniform mat4 u_ViewProjection;
      uniform mat4 u_Transform;
      out vec2 v_TextCoord;
      void main()
      {
        v_TextCoord = a_TextCoord;
        gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);
      }

)";
    std::string textureShaderFragmentSrc = R"(
      #version 330 core

      layout(location = 0) out vec4 color;

      in vec2 v_TextCoord;
      uniform sampler2D u_Texture;
      void main()
      {
        color = texture(u_Texture, v_TextCoord);
      }
    )";

    auto texture_shader = m_ShaderLibrary.Load("C:\\Users\\SunHe\\Desktop\\Hazel\\Sandbox\\assets\\shaders\\Texture.glsl");
	  m_Texture = Hazel::Texture2D::Create("C:\\Users\\SunHe\\Desktop\\Hazel\\Sandbox\\assets\\textures\\Checkerboard.png");
    m_TransparentTexture = Hazel::Texture2D::Create("C:\\Users\\SunHe\\Desktop\\Hazel\\Sandbox\\assets\\textures\\ChernoLogo.png");
    std::dynamic_pointer_cast<Hazel::OpenGLShader>(texture_shader)->Bind();
    std::dynamic_pointer_cast<Hazel::OpenGLShader>(texture_shader)->UploadUniformInt("u_Texture", 0);

  }
	void OnUpdate(Hazel::Timestep ts) override
	{
    m_CameraController.OnUpdate(ts);

    Hazel::RenderCommand::SetClearColor({0.1f, 0.1f, 0.1f, 1});
    Hazel::RenderCommand::Clear();
    Hazel::Renderer::BeginScene(m_CameraController.GetCamera());
    glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));

    std::dynamic_pointer_cast<Hazel::OpenGLShader>(m_SqaureShader)->Bind();
    std::dynamic_pointer_cast<Hazel::OpenGLShader>(m_SqaureShader)->UploadUniformFloat3("u_Color", m_SquareColor);
    for (int i = 0; i < 20; ++i) {
      for (int j = 0; j < 20; ++j) {
        glm::vec3 pos(i * 0.11f, j * 0.11f, 0.0f);

        glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos);
        Hazel::Renderer::Submit(m_SqaureShader, m_SquareVA, transform * scale);
      }
    }
    auto texture_shader = m_ShaderLibrary.Get("Texture");
    m_Texture->Bind();
    Hazel::Renderer::Submit(texture_shader, m_SquareVA, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));
    m_TransparentTexture->Bind();
    Hazel::Renderer::Submit(texture_shader, m_SquareVA, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));
    Hazel::Renderer::EndScene();
	}

	void OnImGuiRender() override {
		ImGui::Begin("Settings");
		ImGui::ColorEdit3("Square Color", glm::value_ptr(m_SquareColor));
		ImGui::End();
	}

	void OnEvent(Hazel::Event& event) override
	{
    m_CameraController.OnEvent(event);
	}

private:
  Hazel::ShaderLibrary m_ShaderLibrary;
  Hazel::OrthographicCameraController m_CameraController;
  Hazel::Ref<Hazel::Shader> m_Shader;
  Hazel::Ref<Hazel::Shader> m_SqaureShader;
  Hazel::Ref<Hazel::VertexArray> m_VertexArray;
  Hazel::Ref<Hazel::VertexArray> m_SquareVA;
  Hazel::Ref<Hazel::Texture2D> m_Texture, m_TransparentTexture;

  glm::vec3 m_SquareColor = {0.2f, 0.3f, 0.8f};
};

class Sandbox : public Hazel::Application
{
public:
	Sandbox()
	{
		//PushLayer(new ExampleLayer());
    PushLayer(new Sandbox2D());

	}
	~Sandbox()
	{
	
	}

	
	   
};


Hazel::Application* Hazel::CreateApplication()
{
	return new Sandbox();//
}