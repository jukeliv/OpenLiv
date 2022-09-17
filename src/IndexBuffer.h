#pragma once

#include "Core.h"
#include "Renderer.h"

class IndexBuffer
{
public:
	IndexBuffer(const unsigned int* data, unsigned int count);
	~IndexBuffer();

	void Bind() const;
	void UnBind() const;

	inline unsigned int GetCount() const { return mCount; }
private:
	unsigned int mRendererID;
	unsigned int mCount;
};