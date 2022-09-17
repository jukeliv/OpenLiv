#include "VertexBuffer.h"

VertexBuffer::VertexBuffer(const void* data, unsigned int size)
{
	glCall(glGenBuffers(1, &mRendererID));
	glCall(glBindBuffer(GL_ARRAY_BUFFER, mRendererID));
	glCall(glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW));
}

VertexBuffer::~VertexBuffer()
{
	glCall(glDeleteBuffers(1, &mRendererID));
}

void VertexBuffer::Bind() const
{
	glCall(glBindBuffer(GL_ARRAY_BUFFER, mRendererID));
}
void VertexBuffer::UnBind() const
{
	glCall(glBindBuffer(GL_ARRAY_BUFFER, mRendererID));
}
