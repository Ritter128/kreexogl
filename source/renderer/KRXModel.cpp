#include "KRXModel.hpp"
#include <cstring>


KRXCube::KRXCube(vec3 position, vec3 scale, vec3 color)
{
  m_Position = position;
  m_Scale = scale;
  m_Color = color;
}

std::array<Vertex, 24> KRXCube::GetVertices()
{
// Front
Vertex vert0 = {vec3(-0.5f, -0.5f, 0.5f) + m_Position * m_Scale, m_Color, vec2(0.0f, 0.0f)};
Vertex vert1 = {vec3( 0.5f, -0.5f, 0.5f) + m_Position * m_Scale, m_Color, vec2(0.0f, 1.0f)};
Vertex vert2 = {vec3( 0.5f,  0.5f, 0.5f) + m_Position * m_Scale, m_Color, vec2(1.0f, 0.0f)};
Vertex vert3 = {vec3(-0.5f,  0.5f, 0.5f) + m_Position * m_Scale, m_Color, vec2(1.0f, 1.0f)};
// Back
Vertex vert4 = {vec3(-0.5f, -0.5f,-0.5f) + m_Position * m_Scale, m_Color, vec2(0.0f, 0.0f)};
Vertex vert5 = {vec3( 0.5f, -0.5f,-0.5f) + m_Position * m_Scale, m_Color, vec2(0.0f, 1.0f)};
Vertex vert6 = {vec3( 0.5f,  0.5f,-0.5f) + m_Position * m_Scale, m_Color, vec2(1.0f, 0.0f)};
Vertex vert7 = {vec3(-0.5f,  0.5f,-0.5f) + m_Position * m_Scale, m_Color, vec2(1.0f, 1.0f)};
// Right
Vertex vert8 = {vec3(-0.5f, -0.5f,-0.5f) +  m_Position * m_Scale, m_Color, vec2(0.0f, 0.0f)};
Vertex vert9 = {vec3(-0.5f, -0.5f, 0.5f) +  m_Position * m_Scale, m_Color, vec2(0.0f, 1.0f)};
Vertex vert10 = {vec3(-0.5f,  0.5f, 0.5f) + m_Position * m_Scale, m_Color, vec2(1.0f, 0.0f)};
Vertex vert11 = {vec3(-0.5f,  0.5f,-0.5f) + m_Position * m_Scale, m_Color, vec2(1.0f, 1.0f)};
// Left
Vertex vert12 = {vec3(0.5f, -0.5f,-0.5f) + m_Position * m_Scale, m_Color, vec2(0.0f, 0.0f)};
Vertex vert13 = {vec3(0.5f, -0.5f, 0.5f) + m_Position * m_Scale, m_Color, vec2(0.0f, 1.0f)};
Vertex vert14 = {vec3(0.5f,  0.5f, 0.5f) + m_Position * m_Scale, m_Color, vec2(1.0f, 0.0f)};
Vertex vert15 = {vec3(0.5f,  0.5f,-0.5f) + m_Position * m_Scale, m_Color, vec2(1.0f, 1.0f)};
// Top
Vertex vert16{vec3(-0.5f, -0.5f,-0.5f) + m_Position * m_Scale, m_Color, vec2(0.0f, 0.0f)};
Vertex vert17{vec3(-0.5f, -0.5f, 0.5f) + m_Position * m_Scale, m_Color, vec2(0.0f, 1.0f)};
Vertex vert18{vec3(0.5f,  -0.5f, 0.5f) + m_Position * m_Scale, m_Color, vec2(1.0f, 0.0f)};
Vertex vert19{vec3(0.5f,  -0.5f,-0.5f) + m_Position * m_Scale, m_Color, vec2(1.0f, 1.0f)};
// Bottom
Vertex vert20{vec3(-0.5f,  0.5f,-0.5f) + m_Position * m_Scale, m_Color, vec2(0.0f, 0.0f)};
Vertex vert21{vec3(-0.5f,  0.5f, 0.5f) + m_Position * m_Scale, m_Color, vec2(0.0f, 1.0f)};
Vertex vert22{vec3(0.5f,   0.5f, 0.5f) + m_Position * m_Scale, m_Color, vec2(1.0f, 0.0f)};
Vertex vert23{vec3(0.5f,   0.5f,-0.5f) + m_Position * m_Scale, m_Color, vec2(1.0f, 1.0f)};
  return {
    vert0, vert1, 
    vert2, vert3,

    vert4, vert5, 
    vert6, vert7,

    vert8, vert9,
    vert10, vert11,

    vert12, vert13,
    vert14, vert15,

    vert16, vert17, 
    vert18, vert19,

    vert20, vert21,
    vert22, vert23,
  };
}

void KRXCube::DumpVertexData(Vertex* vertexBufferData, size_t offset)
{
  memcpy(vertexBufferData + offset, GetVertices().data(), GetVertices().size() * sizeof(Vertex));
}

  void Move(vec3 position);