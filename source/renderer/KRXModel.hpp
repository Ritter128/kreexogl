#pragma once
#include "../KRXTypes.hpp"
#include <array>

class KRXCube 
{
public:
  KRXCube(vec3 position, vec3 scale, vec3 color);

  void DumpVertexData(Vertex* vertexBufferData, size_t offset);

  std::array<Vertex, 24> GetVertices();
  void Move(vec3 position);
private:
  vec3 m_Position;
  vec3 m_Scale;
  vec3 m_Color;
  Vertex* m_VertexData;

};