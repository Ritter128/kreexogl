#include "KRXVertexArray.hpp"

void KRXVertexArray::Init()
{
  GLCall(glGenVertexArrays(1, &m_ID));
  GLCall(glBindVertexArray(m_ID));
}
  
void KRXVertexArray::Delete()
{
  GLCall(glDeleteVertexArrays(1, &m_ID));
}

void KRXVertexArray::AddAttribute(uint32_t index, uint32_t count, 
    GLenum type, size_t stride, const void* offset)
{
  GLCall(glEnableVertexAttribArray(index));
  GLCall(glVertexAttribPointer(index, count, type, GL_FALSE, stride, offset));
}

  void Bind();
  void Unbind();