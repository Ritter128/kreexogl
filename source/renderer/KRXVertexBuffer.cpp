#include "KRXVertexBuffer.hpp"

void KRXVertexBuffer::Init(Vertex* vertexData, size_t size)
{
  m_VertexData = vertexData;
  m_TotalSize = size;
  GLCall(glGenBuffers(1, &m_ID));
  GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_ID));
  GLCall(glBufferData(GL_ARRAY_BUFFER, m_TotalSize, 
    nullptr, GL_DYNAMIC_DRAW));
}

void KRXVertexBuffer::Delete()
{
  GLCall(glDeleteBuffers(1, &m_ID));
}

void KRXVertexBuffer::LoadVertexData(size_t offset, Vertex* data, size_t vertexCount)
{
  memcpy(m_VertexData + offset, data, vertexCount * sizeof(Vertex));
  GLCall(glBufferSubData(GL_ARRAY_BUFFER, 0, m_TotalSize, m_VertexData));
}

void KRXVertexBuffer::Bind()
{
  GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_ID));
}

void KRXVertexBuffer::Unbind()
{
  GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
}