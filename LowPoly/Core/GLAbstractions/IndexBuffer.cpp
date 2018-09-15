#include "IndexBuffer.h"

#include "GL\glew.h"

yami::IndexBuffer::IndexBuffer(const unsigned int * data, unsigned int count)
{
	this->count = count;
	glGenBuffers(1, &this->id);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->id);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->count * sizeof(unsigned int), data, GL_STATIC_DRAW);
}

yami::IndexBuffer::~IndexBuffer()
{
	glDeleteBuffers(1, &this->id);
}

void yami::IndexBuffer::bind() const
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->id);
}

void yami::IndexBuffer::unbind() const
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
