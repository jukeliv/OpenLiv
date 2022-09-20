#pragma once

#include "GL/glew.h"
#include "GLErrorManager.h"

class IndexBuffer
{
public:
	IndexBuffer(const uint32_t* data, uint32_t count, uint32_t type);
	~IndexBuffer();

	void Bind() const;
	void UnBind() const;

	inline uint32_t GetCount() const { return m_Count; }
	inline uint32_t GetType() const { return m_Type; }
private:
	uint32_t m_RendererID;
	uint32_t m_Type;
	uint32_t m_Count;
};