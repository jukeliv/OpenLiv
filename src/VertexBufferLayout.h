#pragma once
#include "Core.h"
#include "Renderer.h" 
#include <vector>

struct VertexLayoutElement
{
	unsigned int type;
	unsigned int count;
	unsigned char normalized;

	static unsigned int GetSizeOfType(unsigned int t)
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
	void PushData(unsigned int count)
	{
		static_assert(false);
	}

	template<>
	void PushData<float>(unsigned int  count)
	{
		m_Elements.push_back({ GL_FLOAT, count, GL_FALSE });
		m_Stride += VertexLayoutElement::GetSizeOfType(GL_FLOAT) * count;
	}

	template<>
	void PushData<unsigned int>(unsigned int  count)
	{
		m_Elements.push_back({ GL_UNSIGNED_INT, count, GL_FALSE });
		m_Stride += VertexLayoutElement::GetSizeOfType(GL_UNSIGNED_INT) * count;
	}

	template<>
	void PushData<unsigned char>(unsigned int  count)
	{
		m_Elements.push_back({ GL_UNSIGNED_BYTE, count, GL_TRUE });
		m_Stride += VertexLayoutElement::GetSizeOfType(GL_UNSIGNED_BYTE) * count;
	}

	inline const std::vector<VertexLayoutElement> GetElements() const { return m_Elements; }
	inline unsigned int GetStride() const { return m_Stride; }

private:
	unsigned int m_Stride;
	std::vector<VertexLayoutElement> m_Elements;
};

