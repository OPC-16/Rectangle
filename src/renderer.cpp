#include "renderer.h"

#include <iostream>

void GLClearError() {
   while (glGetError() != GL_NO_ERROR);
} //function-GLClearError

void GLLogCall(const char* function,const char* file, int line) {
   while (GLenum error = glGetError()){
      std::cout << "[OpenGL Error] (" << error << "): " << function <<
         " " << file << ":" << line << std::endl;
   }
} //function-GLLogCall
