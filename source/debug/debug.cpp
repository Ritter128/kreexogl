#include "debug.hpp"

void CheckError(const char *function, const char *file, int line) {
  while (GLenum error = glGetError()) 
  {
    std::cout << "[OPENGL ERROR] in " << function << ", " << file << ", " << line << ": " << error << "\n";
  }
}