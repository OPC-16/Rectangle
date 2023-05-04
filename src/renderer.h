#pragma once

#include "glad/glad.h"

#define GLCall(x) GLClearError();\
   x;\
   GLLogCall(#x, __FILE__, __LINE__)

void GLClearError();
void GLLogCall(const char* function,const char* file, int line);
