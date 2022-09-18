#include "IndexBuffer.h"

IndexBuffer::IndexBuffer(const unsigned int* data, unsigned int count, unsigned int type)
	: m_Count(count), m_Type(type)
{
	ASSERT((sizeof(unsigned int) == sizeof(GLuint)));

	glCall(glGenBuffers(1, &m_RendererID));
	glCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID));
	glCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), data, GL_STATIC_DRAW));
}
IndexBuffer::~IndexBuffer()
{
	glCall(glDeleteBuffers(1, &m_RendererID));
}

void IndexBuffer::Bind() const
{
	glCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID));
}

void IndexBuffer::UnBind() const
{
	glCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
}