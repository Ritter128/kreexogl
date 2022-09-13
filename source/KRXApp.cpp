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

uint32_t CompileShader(const std::string &src, uint32_t type) 
{
  const char *cSource = src.c_str();
  uint32_t shaderID = glCreateShader(type);
  glShaderSource(shaderID, 1, &cSource, NULL);
  glCompileShader(shaderID);

  int compileStatus;
  glGetShaderiv(shaderID, GL_COMPILE_STATUS, &compileStatus);

  if (compileStatus == GL_FALSE) {
    switch (type) {
    case GL_VERTEX_SHADER: {
      std::cout << "[VERTEX SHADER ERROR]\n";
      break;
    }
    case GL_FRAGMENT_SHADER: {
      std::cout << "[FRAGMENT SHADER ERROR]\n";
      break;
    }
    case GL_GEOMETRY_SHADER: {
      std::cout << "[GEOMETRY SHADER ERROR]\n";
      break;
    }
    case GL_COMPUTE_SHADER: {
      std::cout << "[COMPUTE SHADER ERROR]\n";
      break;
    }
    }

    GLsizei infoLength;

    glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &infoLength);

    char *infoLog = (char *)alloca(infoLength * sizeof(char));

    glGetShaderInfoLog(shaderID, infoLength, &infoLength, infoLog);

    std::cout << infoLog << "\n";
  }

  return shaderID;
}

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

  vertexBuffer.Init(vertexData, sizeof(vertexData));

  GLCall(glGenVertexArrays(1, &vaoID));
  GLCall(glBindVertexArray(vaoID));

  // Position
  GLCall(glEnableVertexAttribArray(0));
  GLCall(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)offsetof(Vertex, position)));
  // Color
  GLCall(glEnableVertexAttribArray(1));
  GLCall(glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)offsetof(Vertex, color)));

  indexBuffer.Init(indexData, sizeof(indexData));

  // Shaders
  string vsSource = ReadFile("source/shaders/default.vert");
  string fsSource = ReadFile("source/shaders/default.frag");  

  const char* cVSSource = vsSource.c_str();
  const char* cFSSource = fsSource.c_str();

  shaderID = glCreateProgram();
  vsID = CompileShader(vsSource, GL_VERTEX_SHADER);
  fsID = CompileShader(fsSource, GL_FRAGMENT_SHADER);

  GLCall(glAttachShader(shaderID, vsID));
  GLCall(glAttachShader(shaderID, fsID));

  GLCall(glLinkProgram(shaderID));

  GLCall(glDeleteShader(vsID));
  GLCall(glDeleteShader(fsID));

  GLCall(glUseProgram(shaderID));

  // Loading data into buffers
  vertexBuffer.LoadVertexData(0, vertices, sizeof(vertices));
  indexBuffer.LoadElementData(0, indices, sizeof(indices));

  while (!m_Window.bCloseWindow())
  {
    Run();  
  }
}

KRXApplication::~KRXApplication() 
{
  GLCall(glDeleteVertexArrays(1, &vaoID));
  vertexBuffer.Delete();
  indexBuffer.Delete();
  GLCall(glDeleteProgram(shaderID));
  glfwTerminate();
}

void KRXApplication::Run()
{
  glClear(GL_COLOR_BUFFER_BIT);
  glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

  indexBuffer.DrawElementData(6);

  m_Window.Swap();
  glfwPollEvents();  
}