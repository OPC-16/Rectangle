#pragma once

class indexBuffer {
   private:
      unsigned int m_rendererID; //every created obj (vertex buffer, textures, etc) will have an id, this is where it will be tied to
      unsigned int m_count;
   public:
      indexBuffer(const unsigned int* data, unsigned int count);  //count is number of indices
      ~indexBuffer();

      void bind() const ;
      void unbind() const ;

      inline unsigned int getCount() const { return m_count; }
}; //class-vertexBuffer
