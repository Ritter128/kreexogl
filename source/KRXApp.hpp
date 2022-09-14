#pragma once
#include "KRXWindow.hpp"
#include <glm/glm.hpp>

#include "renderer/KRXVertexBuffer.hpp"
#include "renderer/KRXIndexBuffer.hpp"
#include "renderer/KRXVertexArray.hpp"
#include "renderer/KRXShader.hpp"

class KRXApplication 
{
public:
  KRXApplication();
  ~KRXApplication();

private:
  KRXWindow m_Window{620, 480, "Kreex"};

  void Run();

  Vertex vertexData[MAX_VERTICES];
  uint32_t indexData[MAX_INDICES];

  KRXVertexBuffer m_VertexBuffer;
  KRXIndexBuffer m_IndexBuffer;
  KRXVertexArray m_VertexArray;
  KRXShader m_Shader;
};