#pragma once
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <cstdint>
#include "../debug/debug.hpp"
#include <cstring>
#include <string>
#include <fstream>
#include <sstream>

const std::string ReadFile(std::string name);

class KRXShader 
{
public:
  void Init(const std::string& vsPath, const std::string& fsPath);
  void Delete();

  void Bind();
  void Unbind();

  void SetMat4Uniform(const std::string& name, glm::mat4 matrix);

  void SetIntUniform(const std::string& name, int32_t integer);
private:
  uint32_t m_ID;

  uint32_t CompileShader(const std::string &src, uint32_t type);
};