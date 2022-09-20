#pragma once

#include <GL/glew.h>
#include <iostream>

#include "GLErrorManager.h"

#include <vector>

struct LayoutElement
{
	uint32_t type;
	uint32_t count;
	unsigned char normalized;

	static uint32_t GetSizeOfType(uint32_t t)
	{
		switch (t)
		{
			case GL_FLOAT:	return 4;
			case GL_UNSIGNED_INT:	return 4;
			case GL_UNSIGNED_BYTE:	return 1;
		}

		ASSERT(false);
		return 0;
	}
};
class VertexBufferLayout
{
public:
	VertexBufferLayout()
		: m_Stride(0) {}

	template<typename T>
	void PushData(uint32_t count)
	{
		static_assert(false);
	}

	template<>
	void PushData<float>(uint32_t  count)
	{
		m_Elements.push_back({ GL_FLOAT, count, GL_FALSE });
		m_Stride += LayoutElement::GetSizeOfType(GL_FLOAT) * count;
	}

	template<>
	void PushData<uint32_t>(uint32_t  count)
	{
		m_Elements.push_back({ GL_UNSIGNED_INT, count, GL_FALSE });
		m_Stride += LayoutElement::GetSizeOfType(GL_UNSIGNED_INT) * count;
	}

	template<>
	void PushData<unsigned char>(uint32_t  count)
	{
		m_Elements.push_back({ GL_UNSIGNED_BYTE, count, GL_TRUE });
		m_Stride += LayoutElement::GetSizeOfType(GL_UNSIGNED_BYTE) * count;
	}

	inline const std::vector <LayoutElement> GetElements() const& { return m_Elements; }
	inline uint32_t GetStride() const { return m_Stride; }

private:
	uint32_t m_Stride;
	std::vector<LayoutElement> m_Elements;
};

