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
   window = glfwCreateWindow(1000, 800, "Rectangle~OpenGL", NULL, NULL);
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
   opcShader.setUniform4f("u_Color", 1.0f, 0.9f, 0.1f, 1.0f);

   //unbinding following
   va.unbind();
   va.unbind();
   ib.unbind();
   opcShader.unbind();

   float r = 0.0f;
   float increment = 0.05f;

   //loop until user closes the window
   while(!glfwWindowShouldClose(window)) {
      // glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
      GLCall(glClear(GL_COLOR_BUFFER_BIT));

      //binding them again
      opcShader.bind();
      opcShader.setUniform4f("u_Color", r, 0.9f, 0.1f, 1.0f);
      // GLCall(glBindBuffer(GL_ARRAY_BUFFER, buffer));
      ib.bind();
      va.bind();

      GLCall(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr));

      if (r > 1.0f)
         increment = -0.05f;
      else if (r < 0.0f)
         increment = 0.05f;

      r += increment;
      //swap front and back buffers
      glfwSwapBuffers(window);

      //poll for and process events
      glfwPollEvents();
   } //while-loop

   // glDeleteProgram(shader);
   glfwTerminate();

} //function-main
