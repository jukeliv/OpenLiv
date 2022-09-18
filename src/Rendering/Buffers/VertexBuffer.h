#pragma once

#include <GL/glew.h>
#include "GLErrorManager.h"

class VertexBuffer {
public:
	VertexBuffer(const void* data, unsigned int size);
	~VertexBuffer();

	void Bind() const;
	void UnBind() const;

private:
	unsigned int m_RendererID;
};