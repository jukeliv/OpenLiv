#include "ClearColor.h"

namespace tests {
	ClearColor::ClearColor()
		: m_ClearColor{1.0f, 1.0f, 1.0f}
	{
	}
	ClearColor::~ClearColor()
	{
	}

	void ClearColor::OnRender(Renderer& renderer)
	{
		glCall(glClearColor(m_ClearColor[0], m_ClearColor[1], m_ClearColor[2], 1.0f));
		/*Clear is handled by Renderer.h
		* glCall(glClear(GL_COLOR_BUFFER_BIT));
		*/
	}

	void ClearColor::OnUIRender()
	{
		ImGui::ColorEdit3("Background Color", m_ClearColor);
	}
}