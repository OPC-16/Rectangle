#pragma once

class vertexBuffer {
   private:
      unsigned int m_rendererID; //every created obj (vertex buffer, textures, etc) will have an id, this is where it will be tied to
   public:
      vertexBuffer(const void* data, unsigned int size);
      ~vertexBuffer();

      void bind() const ;
      void unbind() const ;
}; //class-vertexBuffer
