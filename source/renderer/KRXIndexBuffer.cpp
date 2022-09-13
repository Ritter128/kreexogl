#include "KRXIndexBuffer.hpp"

void KRXIndexBuffer::Init(uint32_t* elementData, size_t size)
{
  m_ElementData = elementData;
  m_TotalSize = size;
  GLCall(glGenBuffers(1, &m_ID));
  GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ID));
  GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_TotalSize, 
    nullptr, GL_DYNAMIC_DRAW));
}

void KRXIndexBuffer::Delete()
{
  GLCall(glDeleteBuffers(1, &m_ID));
}

void KRXIndexBuffer::LoadElementData(size_t offset, uint32_t* data, size_t elementCount)
{
  memcpy(m_ElementData + offset, data, elementCount * sizeof(uint32_t));
  GLCall(glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, m_TotalSize, m_ElementData));
}

void KRXIndexBuffer::DrawElementData(uint32_t indexCount)
{
  GLCall(glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, nullptr));
}

void KRXIndexBuffer::Bind()
{
  GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ID));
}

void KRXIndexBuffer::Unbind()
{
  GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
}