#pragma once

#include <string>
#include <unordered_map>

struct shaderProgramSource {
   std::string vertexSource;
   std::string fragmentSource;
}; //struct-shaderProgramSource

class shader {
   private:
      std::string m_filePath;
      unsigned int m_rendererID;
      //caching for uniforms
      std::unordered_map<std::string, int> m_uniformLocationCache;
   public:
      shader(const std::string& filePath);
      ~shader();

      void bind() const;
      void unbind() const;

      //set uniforms
      void setUniform4f(const std::string& name, float v0, float v1, float v2, float v3);
      void setUniform1f(const std::string& name, float value);

   private:
      int getUniformLocation(const std::string& name);
      unsigned int compileShader(unsigned int shaderType, const std::string& shaderSource);
      shaderProgramSource parseShader(const std::string& filepath);
      unsigned int createShader(const std::string& vertexShader, const std::string& fragmentShader);
}; //class-shader
