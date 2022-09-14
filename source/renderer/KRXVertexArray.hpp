#pragma once
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <cstdint>
#include "../debug/debug.hpp"
#include <cstring>


class KRXVertexArray 
{
public:
  void Init();
  void Delete();

  void AddAttribute(uint32_t index, uint32_t count, 
    GLenum type, size_t stride, const void* offset);

  void Bind();
  void Unbind();
private:
  uint32_t m_ID;
};