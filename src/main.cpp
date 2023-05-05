#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include <iostream>
#include <sstream>
#include <fstream>

#include "renderer.h"

#include "vertexBuffer.h"
#include "indexBuffer.h"
#include "vertexArray.h"
#include "vertexBufferLayout.h"
#include "shader.h"

int main() {
   // initialise the library
   if (!glfwInit())
      return -1;

   glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
   glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
   glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

   GLFWwindow* window;

   // create a window and its OpenGL context
   window = glfwCreateWindow(800, 600, "Rectangle~OpenGL", NULL, NULL);
   if (!window) {
      glfwTerminate();
      return -1;
   }

   //make the window's context current
   glfwMakeContextCurrent(window);

   glfwSwapInterval(1);

   //glad: load all OpenGL function pointers
   if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
      std::cout << "Failed to initialise GLAD\n";
      return -1;
   }

   float positions[] = {
      -0.5f, -0.5f,  //0
       0.5f, -0.5f,  //1
       0.5f,  0.5f,  //2
      -0.5f,  0.5f,  //3
   };

   unsigned int indices[] {
      0, 1, 2,
      2, 3, 0
   };

   vertexArray va;
   vertexBuffer vb(positions, 4 * 2 * sizeof(float)); //constructor automatically binds the buffer

   vertexBufferLayout layout;
   layout.push<float>(2);
   va.addBuffer(vb, layout);

   indexBuffer ib(indices, 6);   //2nd arg is count and not size

   shader opcShader("../shaders/basic.shader");
   opcShader.bind();
   opcShader.setUniform4f("u_Color", 1.0f, 0.5f, 0.0f, 0.0f);

   ib.bind();

   //loop until user closes the window
   while(!glfwWindowShouldClose(window)) {

      GLCall(glClear(GL_COLOR_BUFFER_BIT));

      GLCall(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr));

      //swap front and back buffers
      glfwSwapBuffers(window);

      //poll for and process events
      glfwPollEvents();
   } //while-loop

   // glDeleteProgram(shader);
   glfwTerminate();

} //function-main
