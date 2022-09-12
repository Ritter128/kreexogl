#pragma once
#include <iostream>
#include <glad/glad.h>

#define GLCall(x) \
  x;              \
  CheckError(#x, __FILE__, __LINE__)

void CheckError(const char *function, const char *file, int line);