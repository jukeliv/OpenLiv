#include "Sandbox.h"

#include <glm/glm.hpp>

#include "Rendering/Buffers/VertexBuffer.h"
#include "Rendering/Buffers/VertexBufferLayout.h"

namespace tests {
	Sandbox::Sandbox()
		: m_Translation(0.0f), m_TranslationB(0.0f)
	{
		const float vertexData[16] = {
			-0.5f, -0.5f, 0.0f, 0.0f,
			 0.5f, -0.5f, 1.0f, 0.0f,
			 0.5f,  0.5f, 1.0f, 1.0f,
			-0.5f,  0.5f, 0.0f, 1.0f,
		};

		const uint32_t indices[6] = {
			0, 1, 2,
			2, 3, 0
		};
		glCall(glEnable(GL_BLEND));
		glCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

		m_VAO = std::make_unique<VertexArray>();
		m_VBO = std::make_unique<VertexBuffer>(vertexData, 4 * 4 * sizeof(float));
		VertexBufferLayout layout;
		layout.PushData<float>(2);
		layout.PushData<float>(2);
		m_VAO->AddBuffer(*m_VBO, layout);
		m_IBO = std::make_unique<IndexBuffer>(indices, 6, GL_UNSIGNED_INT);

		m_Shader = std::make_unique<Shader>("Main");

		m_BoxSprite = std::make_unique<Sprite>("Sandbox/box.png", *m_VAO, *m_IBO, *m_Shader);
		m_BGSprite = std::make_unique<Sprite>("Sandbox/BackGround.png", *m_VAO, *m_IBO, *m_Shader);
	}

	Sandbox::~Sandbox()
	{
		m_IBO->UnBind();
		m_VAO->UnBind();
	}

	void Sandbox::OnRender(Renderer& renderer)
	{
		glCall(glClearColor(0.2f, 0.6f, 1.0f, 1.0f));

		m_BoxSprite->Draw(renderer);
		m_BoxSprite->SetTranslation(m_Translation);

		m_BGSprite->Draw(renderer);
		m_BGSprite->SetTranslation(m_TranslationB);

	}
	void Sandbox::OnUIRender()
	{
		ImGui::SliderFloat2("Position",&m_Translation.x, -1.0f, 1.0f);
		ImGui::SliderFloat2("Position B", &m_TranslationB.x, -1.0f, 1.0f);
	}
}