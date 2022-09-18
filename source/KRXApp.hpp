#pragma once
#include "KRXWindow.hpp"

#include "renderer/KRXVertexBuffer.hpp"
#include "renderer/KRXIndexBuffer.hpp"
#include "renderer/KRXVertexArray.hpp"
#include "renderer/KRXShader.hpp"
#include "renderer/KRXTexture2D.hpp"
#include "renderer/KRXModel.hpp"

const uint32_t WIDTH = 1400;
const uint32_t HEIGHT = 900;

uint32_t* GenerateIndices();

class KRXApplication 
{
public:
  KRXApplication();
  ~KRXApplication();

private:
  void Run();

  Vertex vertexData[MAX_VERTICES];
  uint32_t indexData[MAX_INDICES];

  KRXCube cube{vec3(0.0f), vec3(1.0f), vec3(1.0f, 0.0f, 0.0f)};
  KRXCube cube2{vec3(2.0f), vec3(1.0f), vec3(0.0f, 1.0f, 0.0f)};
  Vertex* models;

  KRXWindow m_Window{WIDTH, HEIGHT, "Kreex"};

  KRXVertexBuffer m_VertexBuffer;
  KRXIndexBuffer m_IndexBuffer;
  KRXVertexArray m_VertexArray;
  KRXShader m_Shader;
  // Crashes the program for some reason?
  KRXTexture2D m_MainTexture;


  Transform m_ModelTransform;
  Transform m_CameraTransform;
  glm::mat4 m_ViewMatrix;
  glm::mat4 m_ProjMatrix;
};