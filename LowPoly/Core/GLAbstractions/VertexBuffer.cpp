#include "VertexBuffer.h"

#include "GL\glew.h"

yami::VertexBuffer::VertexBuffer(const void * data, unsigned int size)
{
	glGenBuffers(1, &this->id);
	glBindBuffer(GL_ARRAY_BUFFER, this->id);
	glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
}

yami::VertexBuffer::~VertexBuffer()
{
	glDeleteBuffers(1, &this->id);
}

void yami::VertexBuffer::bind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, this->id);
}

void yami::VertexBuffer::unbind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}
