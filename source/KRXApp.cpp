#include "KRXApp.hpp"
#include "debug/debug.hpp"
#include <iostream>
#include <cstring>
#include <fstream>
#include <sstream>

float speed = 0.5f;

KRXApplication::KRXApplication() 
{
  m_Window.LoadOpenGL();

  uint32_t indices[256] = {0};
  uint32_t vertIndex = 0;

  for (uint32_t i = 0; i < 256; i += 6)
  {
    indices[i + 0] = 0 + vertIndex;
    indices[i + 1] = 1 + vertIndex;
    indices[i + 2] = 2 + vertIndex;
    indices[i + 3] = 0 + vertIndex;
    indices[i + 4] = 3 + vertIndex;
    indices[i + 5] = 2 + vertIndex;
    vertIndex += 4;
  }

  cube.DumpVertexData(models, 0);
  cube2.DumpVertexData(models, cube.GetVertices().size());

  m_VertexArray.Init();
  m_VertexBuffer.Init(vertexData, sizeof(vertexData));
  m_IndexBuffer.Init(indexData, sizeof(indexData));
  // Position
  m_VertexArray.AddAttribute(0, 3, GL_FLOAT, sizeof(Vertex), (const void*)offsetof(Vertex, position));
  // Color
  m_VertexArray.AddAttribute(1, 3, GL_FLOAT, sizeof(Vertex), (const void*)offsetof(Vertex, color));
  m_VertexArray.AddAttribute(2, 2, GL_FLOAT, sizeof(Vertex), (const void *)offsetof(Vertex, texCoords));

  // Texture
  //m_Texture.Init("source/assets/textures/dirt.jpg");
  //m_Texture.Unbind();

  // Shaders
  m_Shader.Init(
    "source/assets/shaders/default.vert",
    "source/assets/shaders/default.frag"
  );
  m_Shader.Bind();

  m_ModelTransform.SetModel(
    glm::vec3(0.0f, 0.0f, 0.0f), 
    glm::vec3(1.0f), 
    0.0f, glm::vec3(1.0f)
  );

  m_CameraTransform.SetModel(
    glm::vec3(0.0f, 0.0f, 2.0f), 
    glm::vec3(2.0f), 
    0.0f, glm::vec3(1.0f)
  );

  m_ViewMatrix = glm::lookAt(
    m_CameraTransform.position, 
    m_CameraTransform.position + glm::vec3(0.0f, 0.0f, 1.0f),  
    glm::vec3(0.0f, 1.0f, 0.0f) 
  );

  m_ProjMatrix = glm::perspective(glm::radians(45.0f), (float)(WIDTH/HEIGHT), 0.001f, 100.0f);

  // Loading data into buffers
  m_VertexBuffer.LoadVertexData(0, models, sizeof(Vertex) * 256);
  m_IndexBuffer.LoadElementData(0, indices, sizeof(indices));

  GLCall(glViewport(0, 0, WIDTH, HEIGHT));

  GLCall(glEnable(GL_DEPTH_TEST));

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
  //m_MainTexture.Delete();
  m_Shader.Delete();
  glfwTerminate();
}

void KRXApplication::Run()
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

  if (m_Window.OnPress(GLFW_KEY_W))
  {
    m_CameraTransform.position += glm::vec3(0.0f, 0.0f, speed);
  }
  if (m_Window.OnPress(GLFW_KEY_S))
  {
    m_CameraTransform.position += glm::vec3(0.0f, 0.0f, -speed);
  }
  if (m_Window.OnPress(GLFW_KEY_A))
  {
    m_CameraTransform.position += glm::vec3(speed, 0.0f, 0.0f);
  }
  if (m_Window.OnPress(GLFW_KEY_D))
  {
    m_CameraTransform.position += glm::vec3(-speed, 0.0f, 0.0f);
  }
  if (m_Window.OnPress(GLFW_KEY_E))
  {
    m_ModelTransform.angle += glm::radians(1.0f);
    m_ModelTransform.rotation = glm::vec3(0.0f, 1.0f, 0.0f);
  }

  m_ViewMatrix = glm::lookAt(
    m_CameraTransform.position, 
    m_CameraTransform.position + glm::vec3(0.0f, 0.0f, 1.0f),   
    glm::vec3(0.0f, 1.0f, 0.0f)    
  );

  m_Shader.SetMat4Uniform("uModelMatrix", m_ModelTransform.GetModel());
  m_Shader.SetMat4Uniform("uViewMatrix", m_ViewMatrix);
  m_Shader.SetMat4Uniform("uProjMatrix", m_ProjMatrix);

  m_IndexBuffer.DrawElementData(256);

  m_Window.Swap();
  glfwPollEvents();  
}