#include "KRXApp.hpp"
#include "debug/debug.hpp"
#include <iostream>
#include <cstring>
#include <fstream>
#include <sstream>

Vertex vertices[] = {
  vec3(-0.5f, -0.5f, 0.0f), vec3(1.0, 0.0, 0.0),
  vec3( 0.5f, -0.5f, 0.0f), vec3(0.0, 1.0, 0.0),
  vec3( 0.5f,  0.5f, 0.0f), vec3(0.0, 0.0, 1.0),
  vec3(-0.5f,  0.5f, 0.0f), vec3(1.0, 1.0, 0.0),
};

uint32_t indices[] = {
  0, 1, 2,
  0, 3, 2,
};

uint32_t CompileShader(const std::string &src, uint32_t type) 
{
  const char *cSource = src.c_str();
  uint32_t shaderID = glCreateShader(type);
  glShaderSource(shaderID, 1, &cSource, NULL);
  glCompileShader(shaderID);

  int compileStatus;
  glGetShaderiv(shaderID, GL_COMPILE_STATUS, &compileStatus);

  if (compileStatus == GL_FALSE) {
    switch (type) {
    case GL_VERTEX_SHADER: {
      std::cout << "[VERTEX SHADER ERROR]\n";
      break;
    }
    case GL_FRAGMENT_SHADER: {
      std::cout << "[FRAGMENT SHADER ERROR]\n";
      break;
    }
    case GL_GEOMETRY_SHADER: {
      std::cout << "[GEOMETRY SHADER ERROR]\n";
      break;
    }
    case GL_COMPUTE_SHADER: {
      std::cout << "[COMPUTE SHADER ERROR]\n";
      break;
    }
    }

    GLsizei infoLength;

    glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &infoLength);

    char *infoLog = (char *)alloca(infoLength * sizeof(char));

    glGetShaderInfoLog(shaderID, infoLength, &infoLength, infoLog);

    std::cout << infoLog << "\n";
  }

  return shaderID;
}

KRXApplication::KRXApplication() 
{
  m_Window.LoadOpenGL();

  m_VertexArray.Init();
  m_VertexBuffer.Init(vertexData, sizeof(vertexData));
  m_IndexBuffer.Init(indexData, sizeof(indexData));
  // Position
  m_VertexArray.AddAttribute(0, 3, GL_FLOAT, sizeof(Vertex), (const void*)offsetof(Vertex, position));
  // Color
  m_VertexArray.AddAttribute(1, 3, GL_FLOAT, sizeof(Vertex), (const void*)offsetof(Vertex, color));

  // Shaders
  m_Shader.Init(
    "source/assets/shaders/default.vert",
    "source/assets/shaders/default.frag"
  );
  m_Shader.Bind();

  m_ModelTransform.SetModel(
    glm::vec3(0.0f), 
    glm::vec3(1.0f), 
    0.0f, glm::vec3(0.25f)
  );

  // Loading data into buffers
  m_VertexBuffer.LoadVertexData(0, vertices, sizeof(vertices));
  m_IndexBuffer.LoadElementData(0, indices, sizeof(indices));

  while (!m_Window.bCloseWindow())
  {
    Run();  
  }
}

KRXApplication::~KRXApplication() 
{
  m_VertexArray.Delete();
  m_VertexBuffer.Delete();
  m_IndexBuffer.Delete();
  m_Shader.Delete();
  glfwTerminate();
}

void KRXApplication::Run()
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

  if (m_Window.OnPress(GLFW_KEY_A))
  {
    m_ModelTransform.SetModel(
      m_ModelTransform.position + glm::vec3(-0.02f, 0.0f, 0.0f), 
      glm::vec3(1.0f), 
      0.0f, m_ModelTransform.scale
    );
  }
  if (m_Window.OnPress(GLFW_KEY_D))
  {
    m_ModelTransform.SetModel(
      m_ModelTransform.position + glm::vec3(0.02f, 0.0f, 0.0f), 
      glm::vec3(1.0f), 
      0.0f, m_ModelTransform.scale
    );
  }
  if (m_Window.OnPress(GLFW_KEY_W))
  {
    m_ModelTransform.SetModel(
      m_ModelTransform.position + glm::vec3(0.0f, 0.02f, 0.0f), 
      glm::vec3(1.0f), 
      0.0f, m_ModelTransform.scale
    );
  }
  if (m_Window.OnPress(GLFW_KEY_S))
  {
    m_ModelTransform.SetModel(
      m_ModelTransform.position + glm::vec3(0.0f, -0.02f, 0.0f), 
      glm::vec3(1.0f), 
      0.0f, m_ModelTransform.scale
    );
  }
  m_Shader.SetMat4Uniform("uModelMatrix", m_ModelTransform.GetModel());

  m_IndexBuffer.DrawElementData(6);

  m_Window.Swap();
  glfwPollEvents();  
}