#pragma once
#include <glad/glad.h>
#include <cstdint>
#include <cstring>
#include "../debug/debug.hpp"

#define MAX_INDICES 2000 * sizeof(uint32_t)

class KRXIndexBuffer 
{
public:
  void Init(uint32_t* elementData, size_t size);
  void Delete();

  void LoadElementData(size_t offset, uint32_t* data, size_t elementCount);

  void DrawElementData(uint32_t indexCount);

  void Bind();
  void Unbind();
private:
  uint32_t m_ID;

  uint32_t* m_ElementData;
  size_t m_TotalSize;
};