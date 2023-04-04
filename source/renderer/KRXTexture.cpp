#include "KRXTexture.hpp"


void KRXTexture::Init(const std::string& path) {
    stbi_set_flip_vertically_on_load(true);
    m_ImageBuffer = stbi_load(path.c_str(), &m_ImageWidth, &m_ImageHeight, &m_ImageBPP, 4);
    if (m_ImageBuffer) {
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

      GLCall(glGenTextures(1, &m_ID));
      GLCall(glBindTexture(GL_TEXTURE_2D, m_ID));
      GLCall(glTexImage2D(
      GL_TEXTURE_2D, 0, GL_RGBA,
      m_ImageWidth, m_ImageHeight, 0, GL_RGBA,
      GL_UNSIGNED_BYTE, m_ImageBuffer
    ));
      GLCall(glGenerateMipmap(GL_TEXTURE_2D));
      GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
      GLCall(glBindTexture(GL_TEXTURE_2D, 0));
    } else {
      std::cout << "Cannot load image\n";
    }    
  }

void KRXTexture::Delete() {
    GLCall(glDeleteTextures(1, &m_ID));
  }

void KRXTexture::Bind() {
    GLCall(glBindTexture(GL_TEXTURE_2D, m_ID));
  }

  void KRXTexture::Unbind() {
    GLCall(glBindTexture(GL_TEXTURE_2D, 0));
  }