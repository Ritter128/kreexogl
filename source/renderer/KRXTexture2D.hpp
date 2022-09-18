#pragma once
#include <stdint.h>
#include <stb_image.h>
#include <glad/glad.h>
#include "../debug/debug.hpp"
#include <string>

class KRXTexture2D
{
public:
  void Init(const std::string& path);
  void Delete();

  void Bind();
  void Unbind();
private:
  uint32_t m_ID;
  //int width, height, BPP;
  //char* m_ImageBuffer;
  int32_t m_Width;
  uint8_t* m_ImageBuffer{0};
};