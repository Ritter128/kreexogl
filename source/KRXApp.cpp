#include "KRXApp.hpp"
#include "debug/debug.hpp"
#include <iostream>
#include <cstring>
#include <fstream>
#include <sstream>


Vertex vertices[] = {
  vec3(-0.5f, -0.5f, 0.0f), vec3(1.0, 0.0, 0.0),
  vec3( 0.5f, -0.5f, 0.0f), vec3(0.0, 1.0, 0.0),
  vec3( 0.5f,  0.5f, 0.0f), vec3(0.0, 0.0, 1.0),
  vec3(-0.5f,  0.5f, 0.0f), vec3(1.0, 1.0, 0.0),
};

uint32_t indices[] = {
  0, 1, 2,
  0, 3, 2,
};

const std::string ReadFile(std::string name) 
{
  std::ifstream inFile;
  inFile.open(name);
  std::stringstream contents;
  std::string item;

  if (inFile.fail()) 
  {
    std::cout << "Could not read given path\n";
    return "Failed to read file";
  } 
  while (getline(inFile, item)) 
  {
    contents << item << "\n";
  }

  return contents.str();
}

KRXApplication::KRXApplication() 
{
  m_Window.LoadOpenGL();
  /*
  GLCall(glGenBuffers(1, &vboID));
  GLCall(glBindBuffer(GL_ARRAY_BUFFER, vboID));
  GLCall(glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), 
    nullptr, GL_DYNAMIC_DRAW));
  */

  vertexBuffer.Init(vertexData, sizeof(vertexData));

  GLCall(glGenVertexArrays(1, &vaoID));
  GLCall(glBindVertexArray(vaoID));

  // Position
  GLCall(glEnableVertexAttribArray(0));
  GLCall(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)offsetof(Vertex, position)));
  // Color
  GLCall(glEnableVertexAttribArray(1));
  GLCall(glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)offsetof(Vertex, color)));

  GLCall(glGenBuffers(1, &eboID));
  GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, eboID));
  GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indexData), 
    nullptr, GL_DYNAMIC_DRAW));

  // Shaders
  string vsSource = ReadFile("source/shaders/default.vert");
  string fsSource = ReadFile("source/shaders/default.frag");  

  const char* cVSSource = vsSource.c_str();
  const char* cFSSource = fsSource.c_str();

  shaderID = glCreateProgram();
  vsID = glCreateShader(GL_VERTEX_SHADER);
  fsID = glCreateShader(GL_FRAGMENT_SHADER);

  GLCall(glShaderSource(vsID, 1, &cVSSource, NULL));
  GLCall(glShaderSource(fsID, 1, &cFSSource, NULL));

  GLCall(glCompileShader(vsID));
  GLCall(glCompileShader(fsID));

  GLCall(glAttachShader(shaderID, vsID));
  GLCall(glAttachShader(shaderID, fsID));

  GLCall(glLinkProgram(shaderID));

  GLCall(glDeleteShader(vsID));
  GLCall(glDeleteShader(fsID));

  GLCall(glUseProgram(shaderID));

  // Loading data into buffers
  //memcpy(vertexData, vertices, sizeof(vertices));
  //GLCall(glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertexData), vertexData));
  vertexBuffer.LoadVertexData(0, vertices, sizeof(vertices));
  memcpy(indexData, indices, sizeof(indices));
  GLCall(glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, sizeof(indexData), indexData));

  while (!m_Window.bCloseWindow())
  {
    Run();  
  }
}

KRXApplication::~KRXApplication() 
{
  GLCall(glDeleteVertexArrays(1, &vaoID));
  //GLCall(glDeleteBuffers(1, &vboID));
  vertexBuffer.Delete();
  GLCall(glDeleteBuffers(1, &eboID));
  GLCall(glDeleteProgram(shaderID));
  glfwTerminate();
}

void KRXApplication::Run()
{
  glClear(GL_COLOR_BUFFER_BIT);
  glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

  GLCall(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr));

  m_Window.Swap();
  glfwPollEvents();  
}