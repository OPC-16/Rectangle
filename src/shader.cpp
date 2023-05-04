#include "shader.h"
#include "renderer.h"

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

shader::shader(const std::string& filePath)
   : m_filePath(filePath)
{
      shaderProgramSource source = parseShader(filePath);
      m_rendererID = createShader(source.vertexSource, source.fragmentSource);
} //function-shader

shader::~shader() {
   GLCall(glDeleteProgram(m_rendererID));
} //function-~shader

shaderProgramSource shader::parseShader(const std::string& filepath) {
   std::ifstream stream(filepath);

   enum class ShaderType {
      NONE = -1, VERTEX = 0, FRAGMENT = 1
   };

   std::string line;
   std::stringstream ss[2];
   ShaderType type = ShaderType::NONE;

   while (getline(stream, line)) {
      if (line.find("#shader") != std::string::npos) {
         if (line.find("vertex") != std::string::npos) {
            //set mode to vertex
            type = ShaderType::VERTEX;
         }
         else if (line.find("fragment") != std::string::npos) {
            //set mode to fragment
            type = ShaderType::FRAGMENT;
         }
      }
      else {
         ss[(int)type] << line << '\n';
      }
   }

   return { ss[0].str(), ss[1].str() };
} //function-parseShader

unsigned int shader::compileShader(unsigned int shaderType, const std::string& shaderSource) {
   unsigned int id = glCreateShader(shaderType);
   const char* src = shaderSource.c_str();
   glShaderSource(id, 1, &src, nullptr);
   glCompileShader(id);

   //Error handling:
   int result;
   glGetShaderiv(id, GL_COMPILE_STATUS, &result);
   if (result == GL_FALSE) {
      int length;
      glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
      char* message = (char*)alloca(length * sizeof(char));
      glGetShaderInfoLog(id, length, &length, message);
      std::cout << "Failed to compile " << (shaderType == GL_VERTEX_SHADER ? "vertex" : "fragment") << " shader!\n";
      std::cout << message << std::endl;
      glDeleteShader(id);
      return 0;
   } //if
   return id;
} //function-compileShader

unsigned int shader::createShader(const std::string& vertexShader, const std::string& fragmentShader) {
   unsigned int program = glCreateProgram();
   unsigned int vs = compileShader(GL_VERTEX_SHADER, vertexShader);
   unsigned int fs = compileShader(GL_FRAGMENT_SHADER, fragmentShader);

   glAttachShader(program, vs);
   glAttachShader(program, fs);
   glLinkProgram(program);

   glDeleteShader(vs);
   glDeleteShader(fs);

   return program;
} //function-createShader

void shader::bind() const {
   GLCall(glUseProgram(m_rendererID));
} //function-bind

void shader::unbind() const {
   GLCall(glUseProgram(0));
} //function-bind

void shader::setUniform1f(const std::string& name, float value) {
   GLCall(glUniform1f(getUniformLocation(name), value));
} //function-setUniform1f

void shader::setUniform4f(const std::string& name, float v0, float v1, float v2, float v3) {
   GLCall(glUniform4f(getUniformLocation(name), v0, v1, v2, v3));
} //function-setUniform4f

int shader::getUniformLocation(const std::string& name) {
   //caching:
   if (m_uniformLocationCache.find(name) != m_uniformLocationCache.end()) {
      return m_uniformLocationCache[name];
   }

   GLCall(int location = glGetUniformLocation(m_rendererID, name.c_str()));
   if (location == -1) {
      std::cout << "Warning: uniform '" << name << "' doesn't exist!" << std::endl;
   }
   m_uniformLocationCache[name] = location;
   return location;
} //function-getUniformLocation
