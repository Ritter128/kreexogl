#include "KRXTexture2D.hpp"
#include <iostream>

/*
void KRXTexture2D::Init(const std::string& path)
{
  stbi_set_flip_vertically_on_load(true);
  imageBuffer = stbi_load(path.c_str(), &width, &height, &BPP, 4);

  if (imageBuffer)
  {
    GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT));
    GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT));
    GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
    GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
    
    GLCall(glGenTextures(1, &m_ID));
    GLCall(glBindTexture(GL_TEXTURE_2D, m_ID));
    GLCall(glTexImage2D(
      GL_TEXTURE_2D, 0, GL_RGBA, 
      width, height, 0, GL_RGBA, 
      GL_UNSIGNED_BYTE, imageBuffer
    ));
    GLCall(glGenerateMipmap(GL_TEXTURE_2D));
    GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
    GLCall(glActiveTexture(GL_TEXTURE0));
    GLCall(glBindTexture(GL_TEXTURE_2D, 0));
  } 
  else 
  {
    std::cout << "Could not load texture\n";
  }

}

void KRXTexture2D::Delete()
{
  GLCall(glDeleteTextures(1, &m_ID));
}

void KRXTexture2D::Bind()
{
  GLCall(glBindTexture(GL_TEXTURE_2D, m_ID));
}

void KRXTexture2D::Unbind()
{
  GLCall(glBindTexture(GL_TEXTURE_2D, 0));
}
*/