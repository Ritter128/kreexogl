#include <glad/glad.h>
#include "../debug/debug.hpp"
#include <stb_image.h>
#include <cstdint>

class KRXTexture {
public:
  void Init(const std::string& path);
  void Delete();

  void Bind();

  void Unbind();
private:
  uint32_t m_ID;
  int32_t m_ImageWidth, m_ImageHeight, m_ImageBPP;
  uint8_t* m_ImageBuffer;
};
