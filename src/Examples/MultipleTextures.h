#pragma once
#include "Examples/Application.h"
#include "Rendering/Utils/Textures/Sprite.h"

#include <memory>

namespace tests {
	class MultipleTextures : public Application
	{
	public:
		MultipleTextures();
		~MultipleTextures();
		void OnRender(Renderer& renderer) override;
		void OnUIRender() override;

	private:
		glm::vec3 m_Translation;
		glm::vec3 m_TranslationB;
		glm::vec3 m_TranslationC;
		float m_Scale;
		float m_ScaleB;
		float m_ScaleC;
		std::unique_ptr<VertexArray> m_VAO;
		std::unique_ptr<VertexBuffer> m_VBO;
		std::unique_ptr<IndexBuffer> m_IBO;
		std::unique_ptr <Shader> m_Shader;

		std::unique_ptr <Sprite> m_SunSprite;
		std::unique_ptr <Sprite> m_BGSprite;
		std::unique_ptr <Sprite> m_SeaSprite;
	};
}