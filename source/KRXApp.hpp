#pragma once
#include "KRXWindow.hpp"
#include "renderer/KRXVertexBuffer.hpp"
#include <glm/glm.hpp>


constexpr uint32_t MAX_INDICES = 2000 * sizeof(Vertex);

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

  //uint32_t vboID;
  KRXVertexBuffer vertexBuffer;
  uint32_t eboID;
  uint32_t vaoID;
  uint32_t shaderID;
  uint32_t vsID;
  uint32_t fsID;
};