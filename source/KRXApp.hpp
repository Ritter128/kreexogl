#pragma once
#include "KRXWindow.hpp"
#include <glm/glm.hpp>

#include "renderer/KRXVertexBuffer.hpp"
#include "renderer/KRXIndexBuffer.hpp"
#include "renderer/KRXVertexArray.hpp"
#include "renderer/KRXShader.hpp"

struct Transform 
{
  glm::vec3 position;
  glm::vec3 rotation;
  float angle;
  glm::vec3 scale;

  void SetModel(glm::vec3 pos, glm::vec3 rotDir, float rot, glm::vec3 scal)
  {
    position = pos;
    rotation = rotDir;
    angle = rot;
    scale = scal;
  }

  glm::mat4 GetModel()
  {
    glm::mat4 translationMatrix = glm::translate(glm::mat4(1.0f), position);
    glm::mat4 rotationMatrix = glm::rotate(glm::mat4(1.0f), angle, rotation);
    glm::mat4 scaleMatrix = glm::scale(glm::mat4(1.0f), scale);

    return translationMatrix * rotationMatrix * scaleMatrix;
  }
};

class KRXApplication 
{
public:
  KRXApplication();
  ~KRXApplication();

private:

  void Run();

  Vertex vertexData[MAX_VERTICES];
  uint32_t indexData[MAX_INDICES];

  KRXWindow m_Window{620, 480, "Kreex"};

  KRXVertexBuffer m_VertexBuffer;
  KRXIndexBuffer m_IndexBuffer;
  KRXVertexArray m_VertexArray;
  KRXShader m_Shader;

  Transform m_ModelTransform;
};