#include "KRXApp.hpp"
#include "debug/debug.hpp"
#include <cstdint>
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

  size_t currentSize = 0;

  cube.DumpVertexData(models, currentSize);
  currentSize += cube.GetVertices().size();
  cube2.DumpVertexData(models, currentSize);
  currentSize += cube2.GetVertices().size();
  cube3.DumpVertexData(models, currentSize);
  

  m_VertexArray.Init();
  m_VertexBuffer.Init(vertexData, sizeof(vertexData));
  m_IndexBuffer.Init(indexData, sizeof(indexData));
  // Position
  m_VertexArray.AddAttribute(0, 3, GL_FLOAT, sizeof(Vertex), (const void*)offsetof(Vertex, position));
  // Color
  m_VertexArray.AddAttribute(1, 3, GL_FLOAT, sizeof(Vertex), (const void*)offsetof(Vertex, color));
  m_VertexArray.AddAttribute(2, 2, GL_FLOAT, sizeof(Vertex), (const void *)offsetof(Vertex, texCoords));

  // Texture 
  uint8_t* m_ImageBuffer;
  int32_t m_ImageWidth, m_ImageHeight, m_ImageBPP;

  stbi_set_flip_vertically_on_load(true);
  m_ImageBuffer = stbi_load("source/assets/textures/mipmap1.jpg", &m_ImageWidth, &m_ImageHeight, &m_ImageBPP, 4);
  if (m_ImageBuffer) {
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    GLCall(glGenTextures(1, &texture));
    GLCall(glBindTexture(GL_TEXTURE_2D, texture));
    GLCall(glTexImage2D(
    GL_TEXTURE_2D, 0, GL_RGBA,
    m_ImageWidth, m_ImageHeight, 0, GL_RGBA,
    GL_UNSIGNED_BYTE, m_ImageBuffer
  ));
    GLCall(glGenerateMipmap(GL_TEXTURE_2D));
    GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
  } else {
    std::cout << "Cannot load image\n";
  }

  // Shaders
  m_Shader.Init(
    "source/assets/shaders/default/default.vert",
    "source/assets/shaders/default/default.frag"
  );
  m_Shader.Bind();

  m_Shader.SetIntUniform("uTexSample", 0);

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
  GLCall(glDeleteTextures(1, &texture));
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
  if (m_Window.OnPress(GLFW_KEY_T))
  {
    m_CameraTransform.position += glm::vec3(0.0f, speed, 0.0f);
  }
  if (m_Window.OnPress(GLFW_KEY_Y))
  {
    m_CameraTransform.position += glm::vec3(0.0f, -speed, 0.0f);
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