#pragma once 
#include <glad/glad.h>
#include <cstdint>
#include "../debug/debug.hpp"
#include <cstring>

#include "../KRXTypes.hpp"


constexpr uint32_t MAX_VERTICES = 1000 * sizeof(Vertex);

class KRXVertexBuffer 
{
public:
  void Init(Vertex* vertexData, size_t size);
  void Delete();

  void LoadVertexData(size_t offset, Vertex* data, size_t vertexCount);

  void Bind();
  void Unbind();
private:
  uint32_t m_ID;

  Vertex* m_VertexData;
  size_t m_TotalSize;
};