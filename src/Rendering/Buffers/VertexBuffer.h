#pragma once

#include <GL/glew.h>
#include "GLErrorManager.h"

class VertexBuffer {
public:
	VertexBuffer(const void* data, uint32_t size);
	~VertexBuffer();

	void Bind() const;
	void UnBind() const;

private:
	uint32_t m_RendererID;
};