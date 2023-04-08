#include "debug.hpp"

void CheckError(const char *function, const char *file, int line) {
  while (GLenum error = glGetError()) 
  {
   // std::cout << "[OPENGL ERROR " << error << "] in " << function << ", " << file << ", " << line << "\n";
  }
}