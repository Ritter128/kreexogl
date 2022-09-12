#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <cstdint>
#include <iostream>
#include <string>

using std::string;

class KRXWindow
{
public:
  KRXWindow(uint32_t width, uint32_t height, const string& title);

  void LoadOpenGL();

  bool bCloseWindow();

  void Swap();

private:
  GLFWwindow* m_CoreWindow;
  uint32_t m_Width, m_Height;

};