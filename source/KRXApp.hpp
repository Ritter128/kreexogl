#pragma once
#include "KRXWindow.hpp"

#include "renderer/KRXVertexBuffer.hpp"
#include "renderer/KRXIndexBuffer.hpp"
#include "renderer/KRXVertexArray.hpp"
#include "renderer/KRXShader.hpp"
#include "renderer/KRXModel.hpp"
#include <cstdint>
#include <stb_image.h>
#include <ctime>

const uint32_t WIDTH = 1400;
const uint32_t HEIGHT = 900;

class KRXApplication 
{
public:
  KRXApplication();
  ~KRXApplication();

private:
  void Run();

  Vertex vertexData[MAX_VERTICES];
  uint32_t indexData[MAX_INDICES];

  KRXCube cube{vec3(0.0f), vec3(1.0f), vec3(1.0f)};
  KRXCube cube2{vec3(2.0f), vec3(1.0f), vec3(1.0f)};
  KRXCube cube3{vec3(1.0f, -4.0f, 1.0f), vec3(1.0f), vec3(1.0f)};
  KRXPlane plane{vec3(0.1f, -0.5f, 0.2f), vec3(20.0f), vec3(1.0f)};
  Vertex* models;

  KRXWindow m_Window{WIDTH, HEIGHT, "Kreex"};

  KRXVertexBuffer m_VertexBuffer;
  KRXIndexBuffer m_IndexBuffer;
  KRXVertexArray m_VertexArray;
  KRXShader m_Shader;
  // Crashes the program for some reason?
  uint32_t texture;

  Transform m_ModelTransform;
  Transform m_CameraTransform;
  glm::mat4 m_ViewMatrix;
  glm::mat4 m_ProjMatrix;
};