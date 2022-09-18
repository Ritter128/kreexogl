#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

using glm::vec3;
using glm::vec2;

struct Vertex
{
  glm::vec3 position;
  glm::vec3 color;
  glm::vec2 texCoords;
};

struct Transform 
{
  glm::vec3 position;
  glm::vec3 rotation;
  glm::vec3 scale;
  float angle;

  void SetModel(glm::vec3 pos, glm::vec3 rotDir, float rot, glm::vec3 scal)
  {
    position = pos;
    rotation = rotDir;
    angle = glm::radians(rot);
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