#include "KRXModel.hpp"
#include <cstring>

vec2 TX_GRASS[4] = {
  vec2(0.0f, 0.5f),
  vec2(0.5f, 1.0f),
  vec2(0.5f, 0.5f),
  vec2(0.0f, 1.0f),
};

vec2 TX_SQUAREBRICKS[4] = {
  vec2(0.0f, 0.0f),
  vec2(0.5f, 0.5f),
  vec2(0.5f, 0.0f),
  vec2(0.0f, 0.5f),
};

vec2 TX_SANDSTONEBRICKS[4] = {
  vec2(0.5f, 0.5f),
  vec2(1.0f, 0.5f),
  vec2(1.0f, 1.0f),
  vec2(0.5f, 1.0f),
};

vec2 TX_COBBLESTONE[4] = {
  vec2(0.5f, 0.0f),
  vec2(1.0f, 0.0f),
  vec2(0.5f, 0.5f),
  vec2(1.0f, 0.5f),
};


KRXCube::KRXCube(vec3 position, vec3 scale, vec3 color)
{
  m_Position = position;
  m_Scale = scale;
  m_Color = color;
}

std::array<Vertex, 24> KRXCube::GetVertices()
{
// Front
Vertex vert0 = {vec3(-0.5f, -0.5f, 0.5f) + m_Position * m_Scale, m_Color, TX_GRASS[0]};
Vertex vert1 = {vec3( 0.5f, -0.5f, 0.5f) + m_Position * m_Scale, m_Color, TX_GRASS[1]};
Vertex vert2 = {vec3( 0.5f,  0.5f, 0.5f) + m_Position * m_Scale, m_Color, TX_GRASS[2]};
Vertex vert3 = {vec3(-0.5f,  0.5f, 0.5f) + m_Position * m_Scale, m_Color, TX_GRASS[3]};
// Back
Vertex vert4 = {vec3(-0.5f, -0.5f,-0.5f) + m_Position * m_Scale, m_Color, TX_COBBLESTONE[0]};
Vertex vert5 = {vec3( 0.5f, -0.5f,-0.5f) + m_Position * m_Scale, m_Color, TX_COBBLESTONE[1]};
Vertex vert6 = {vec3( 0.5f,  0.5f,-0.5f) + m_Position * m_Scale, m_Color, TX_COBBLESTONE[2]};
Vertex vert7 = {vec3(-0.5f,  0.5f,-0.5f) + m_Position * m_Scale, m_Color, TX_COBBLESTONE[3]};
// Right
Vertex vert8 = {vec3(-0.5f, -0.5f,-0.5f) +  m_Position * m_Scale, m_Color, TX_SANDSTONEBRICKS[0]};
Vertex vert9 = {vec3(-0.5f, -0.5f, 0.5f) +  m_Position * m_Scale, m_Color, TX_SANDSTONEBRICKS[1]};
Vertex vert10 = {vec3(-0.5f,  0.5f, 0.5f) + m_Position * m_Scale, m_Color, TX_SANDSTONEBRICKS[2]};
Vertex vert11 = {vec3(-0.5f,  0.5f,-0.5f) + m_Position * m_Scale, m_Color, TX_SANDSTONEBRICKS[3]};
// Left
Vertex vert12 = {vec3(0.5f, -0.5f,-0.5f) + m_Position * m_Scale, m_Color, TX_SQUAREBRICKS[0]};
Vertex vert13 = {vec3(0.5f, -0.5f, 0.5f) + m_Position * m_Scale, m_Color, TX_SQUAREBRICKS[1]};
Vertex vert14 = {vec3(0.5f,  0.5f, 0.5f) + m_Position * m_Scale, m_Color, TX_SQUAREBRICKS[2]};
Vertex vert15 = {vec3(0.5f,  0.5f,-0.5f) + m_Position * m_Scale, m_Color, TX_SQUAREBRICKS[3]};
// Top
Vertex vert16{vec3(-0.5f, -0.5f,-0.5f) + m_Position * m_Scale, m_Color, TX_GRASS[0]};
Vertex vert17{vec3(-0.5f, -0.5f, 0.5f) + m_Position * m_Scale, m_Color, TX_GRASS[1]};
Vertex vert18{vec3(0.5f,  -0.5f, 0.5f) + m_Position * m_Scale, m_Color, TX_GRASS[2]};
Vertex vert19{vec3(0.5f,  -0.5f,-0.5f) + m_Position * m_Scale, m_Color, TX_GRASS[3]};
// Bottom
Vertex vert20{vec3(-0.5f,  0.5f,-0.5f) + m_Position * m_Scale, m_Color, TX_GRASS[0]};
Vertex vert21{vec3(-0.5f,  0.5f, 0.5f) + m_Position * m_Scale, m_Color, TX_GRASS[1]};
Vertex vert22{vec3(0.5f,   0.5f, 0.5f) + m_Position * m_Scale, m_Color, TX_GRASS[2]};
Vertex vert23{vec3(0.5f,   0.5f,-0.5f) + m_Position * m_Scale, m_Color, TX_GRASS[3]};
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

KRXPlane::KRXPlane(vec3 position, vec3 scale, vec3 color)
{
  m_Position = position;
  m_Scale = scale;
  m_Color = color;
}

std::array<Vertex, 4> KRXPlane::GetVertices()
{
  // Plane FIX COORDINATES
  Vertex vert0 = {(vec3(0.5f,  0.0f, -0.5f) + m_Position) * m_Scale, m_Color, TX_GRASS[0]};
  Vertex vert1 = {(vec3(0.5f,  0.0f,  0.5f) + m_Position) * m_Scale, m_Color, TX_GRASS[1]};
  Vertex vert2 = {(vec3(-0.5f,  0.0f, 0.5f) + m_Position) * m_Scale, m_Color, TX_GRASS[2]};
  Vertex vert3 = {(vec3(-0.5f,  0.0f, -0.5f) + m_Position) * m_Scale, m_Color, TX_GRASS[3]};
  return {
    vert0, vert1,
    vert2, vert3
  };
}

void KRXPlane::DumpVertexData(Vertex* vertexBufferData, size_t offset)
{
  memcpy(vertexBufferData + offset, GetVertices().data(), GetVertices().size() * sizeof(Vertex));
}