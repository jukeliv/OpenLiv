#include "VertexBuffer.h"

VertexBuffer::VertexBuffer(const void* data, uint32_t size)
{
	glCall(glGenBuffers(1, &m_RendererID));
	glCall(glBindBuffer(GL_ARRAY_BUFFER, m_RendererID));
	glCall(glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW));
}
VertexBuffer::~VertexBuffer()
{
	glCall(glDeleteBuffers(1, &m_RendererID));
}

void VertexBuffer::Bind() const
{
	glCall(glBindBuffer(GL_ARRAY_BUFFER, m_RendererID));
}
void VertexBuffer::UnBind() const
{
	glCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
}