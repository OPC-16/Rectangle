#pragma once

#include <vector>

#include <glad/glad.h>

struct vertexBufferElement {
   unsigned int type;
   unsigned int count;
   unsigned char normalized;

   static unsigned int getSizeOfType(unsigned int type) {
      switch (type) {
         case GL_FLOAT:         return 4;
         case GL_UNSIGNED_INT:  return 4;
         case GL_UNSIGNED_BYTE: return 1;
      } //switch

      return 0;
   } //function-getSizeOfType

};//struct-vertexBufferElement

class vertexBufferLayout {
   private:
      std::vector<vertexBufferElement> m_elements;
      unsigned int m_stride;
   public:
      vertexBufferLayout()
         : m_stride(0) { }

      template<typename T>
      void push(unsigned int count) {
         // static_assert(false);
      } //function-push

      inline unsigned int getStride() const { return m_stride; }

      inline const std::vector<vertexBufferElement>& getElements() const { return m_elements; }
}; //class-vertexBufferLayout

template<>
inline void vertexBufferLayout::push<float>(unsigned int count) {
   m_elements.push_back({ GL_FLOAT, count, GL_FALSE });
   m_stride += count * vertexBufferElement::getSizeOfType(GL_FLOAT);
} //function-push

template<>
inline void vertexBufferLayout::push<unsigned int>(unsigned int count) {
   m_elements.push_back({ GL_UNSIGNED_INT, count, GL_FALSE });
   m_stride += count * vertexBufferElement::getSizeOfType(GL_UNSIGNED_INT);
} //function-push

template<>
inline void vertexBufferLayout::push<unsigned char>(unsigned int count) {
   m_elements.push_back({ GL_UNSIGNED_BYTE, count, GL_TRUE });
   m_stride += count * vertexBufferElement::getSizeOfType(GL_UNSIGNED_BYTE);
} //function-push
