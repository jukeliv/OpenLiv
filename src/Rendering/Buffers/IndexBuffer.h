#pragma once

#include "GL/glew.h"
#include "GLErrorManager.h"

class IndexBuffer
{
public:
	IndexBuffer(const unsigned int* data, unsigned int count, unsigned int type);
	~IndexBuffer();

	void Bind() const;
	void UnBind() const;

	inline unsigned int GetCount() const { return m_Count; }
	inline unsigned int GetType() const { return m_Type; }
private:
	unsigned int m_RendererID;
	unsigned int m_Type;
	unsigned int m_Count;
};