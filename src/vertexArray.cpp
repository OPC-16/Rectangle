#include "vertexArray.h"
#include "renderer.h"

vertexArray::vertexArray() {
   GLCall(glGenVertexArrays(1, &m_rendererID));
   // GLCall(glBindVertexArray(m_rendererID));     /* don't have to bind in this case */
} //function-vertexArray

vertexArray::~vertexArray() {
   GLCall(glDeleteVertexArrays(1, &m_rendererID));
} //function-~vertexArray

void vertexArray::addBuffer(const vertexBuffer& vb, const vertexBufferLayout& layout) {
   bind();     //binds the vertex array
   vb.bind();  //binds the buffer

   const auto& elements = layout.getElements();
   unsigned int offset = 0;
   for (unsigned int i=0; i < elements.size(); i++) {
      const auto& element = elements[i];

      GLCall(glEnableVertexAttribArray(i));
      GLCall(glVertexAttribPointer(i, element.count, element.type, element.normalized,
               layout.getStride(), (const void*)offset));
      offset += element.count * vertexBufferElement::getSizeOfType(element.type);
   } //for-loop
} //function-addBuffer

void vertexArray::bind() const {
   GLCall(glBindVertexArray(m_rendererID));
} //function-bind

void vertexArray::unbind() const {
   GLCall(glBindVertexArray(0));
} //function-unbind
