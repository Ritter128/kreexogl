#include "KRXWindow.hpp"

KRXWindow::KRXWindow(uint32_t width, uint32_t height, const string& title)
{
  m_Width = width;
  m_Height = height;

  if (!glfwInit())
      std::cerr << "GLFW ERROR: Could not initialize GLFW\n";

  glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  
  m_CoreWindow = glfwCreateWindow(m_Width, m_Height, title.c_str(), NULL, NULL);
  if (!m_CoreWindow)
  {
      glfwTerminate();
      std::cerr << "GLFW ERROR: Could not create window\n";
  }
}

void KRXWindow::LoadOpenGL()
{
  glfwMakeContextCurrent(m_CoreWindow);

  if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) 
  {
      std::cerr << "OPENGL ERROR: Could not load GLAD\n";
  }
}

bool KRXWindow::bCloseWindow()
{
  return glfwWindowShouldClose(m_CoreWindow);
}

void KRXWindow::Swap() 
{
  glfwSwapBuffers(m_CoreWindow);
}

bool KRXWindow::OnPress(int32_t key)
{
  return (glfwGetKey(m_CoreWindow, key) == GLFW_PRESS);
}