#include "KRXShader.hpp"

void KRXShader::Init(const std::string& vsPath, const std::string& fsPath)
{
  std::string vsSource = ReadFile(vsPath);
  std::string fsSource = ReadFile(fsPath);  

  const char* cVSSource = vsSource.c_str();
  const char* cFSSource = fsSource.c_str();

  m_ID = glCreateProgram();
  uint32_t vsID = CompileShader(vsSource, GL_VERTEX_SHADER);
  uint32_t fsID = CompileShader(fsSource, GL_FRAGMENT_SHADER);

  GLCall(glAttachShader(m_ID, vsID));
  GLCall(glAttachShader(m_ID, fsID));

  GLCall(glLinkProgram(m_ID));

  GLCall(glDeleteShader(vsID));
  GLCall(glDeleteShader(fsID));
}

void KRXShader::Delete()
{
  GLCall(glDeleteProgram(m_ID));
}

void KRXShader::Bind()
{
  GLCall(glUseProgram(m_ID));
}

void KRXShader::Unbind()
{
  GLCall(glUseProgram(m_ID));
}

uint32_t KRXShader::CompileShader(const std::string &src, uint32_t type) 
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