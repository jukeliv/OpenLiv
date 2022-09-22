#include "MultipleTextures.h""
#include <glm/glm.hpp>

#include "Rendering/Buffers/VertexBuffer.h"
#include "Rendering/Buffers/VertexBufferLayout.h"

namespace tests {
	MultipleTextures::MultipleTextures()
		: m_Translation(0.254f, -0.108f, 0.0f), m_TranslationB(0.0f, 0.154f, 0.0f),
		m_TranslationC(0.0f, 0.124f, 0.0f), m_Scale(1.0f), m_ScaleB(1.0f), m_ScaleC(1.0f)
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

		m_SunSprite = std::make_unique<Sprite>("Examples/Sun.png", GL_NEAREST, *m_Shader, *m_VAO, *m_IBO);
		m_Scale = glm::vec2(10.0f, 10.0f);

		m_BGSprite = std::make_unique<Sprite>("Examples/Background.png", GL_NEAREST, *m_Shader, *m_VAO, *m_IBO);
		m_ScaleB = glm::vec2(7.0f, 7.0f);

		m_SeaSprite = std::make_unique<Sprite>("Examples/Sea.png", GL_NEAREST, *m_Shader, *m_VAO, *m_IBO);
		m_ScaleC = glm::vec2(16.0f, 16.0f);
	}

	MultipleTextures::~MultipleTextures()
	{
		m_IBO->UnBind();
		m_VAO->UnBind();
	}

	void MultipleTextures::OnRender(Renderer& renderer)
	{
		glCall(glClearColor(0.2f, 0.6f, 1.0f, 1.0f));

		m_SunSprite->Draw(renderer);
		m_SunSprite->SetTranslation(m_Translation);
		m_SunSprite->SetScale(m_Scale);

		m_BGSprite->Draw(renderer);
		m_BGSprite->SetTranslation(m_TranslationB);
		m_BGSprite->SetScale(m_ScaleB);

		m_SeaSprite->Draw(renderer);
		m_SeaSprite->SetTranslation(m_TranslationC);
		m_SeaSprite->SetScale(m_ScaleC);

	}
	void MultipleTextures::OnUIRender()
	{
		ImGui::SliderFloat2("Sun Position", &m_Translation.x, -1.0f, 1.0f);
		ImGui::SliderFloat2("Island Position", &m_TranslationB.x, -1.0f, 1.0f);
		ImGui::SliderFloat2("Sea Position", &m_TranslationC.x, -1.0f, 1.0f);

		ImGui::SliderFloat2("Sun Scale", &m_Scale.x, 0.0f, 10.0f);
		ImGui::SliderFloat2("Island Scale", &m_ScaleB.x, 0.0f, 10.0f);
		ImGui::SliderFloat2("Sea Scale", &m_ScaleC.x, 0.0f, 10.0f);
	}
}