#include "vertexBuffer.h"
#include "renderer.h"

vertexBuffer::vertexBuffer(const void* data, unsigned int size) {
   unsigned int buffer;
   GLCall(glGenBuffers(1, &m_rendererID));
   GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_rendererID));
   GLCall(glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW));
} //function-vertexBuffer

vertexBuffer::~vertexBuffer() {
   GLCall(glDeleteBuffers(1, &m_rendererID));
} //function-vertexBuffer

void vertexBuffer::bind() const {
   GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_rendererID));
} //function-bind

void vertexBuffer::unbind() const {
   GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
} //function-unbind
