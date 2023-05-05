#include "indexBuffer.h"
#include "renderer.h"

indexBuffer::indexBuffer(const unsigned int* data, unsigned int count)
   : m_count(count) 
{
   unsigned int buffer;
   GLCall(glGenBuffers(1, &m_rendererID));
   GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_rendererID));
   GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), data, GL_STATIC_DRAW));
} //function-indexBuffer

indexBuffer::~indexBuffer() {
   GLCall(glDeleteBuffers(1, &m_rendererID));
} //function-indexBuffer

void indexBuffer::bind() const {
   GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_rendererID));
} //function-bind

void indexBuffer::unbind() const {
   GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
} //function-unbind
