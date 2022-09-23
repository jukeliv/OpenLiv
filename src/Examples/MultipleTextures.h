#pragma once
#include "Examples/ExampleTemplate.h"
#include "Rendering/Utils/Textures/Sprite.h"

#include <memory>

namespace examples {
	class MultipleTextures : public ExampleTemplate
	{
	public:
		MultipleTextures();
		~MultipleTextures();
		void OnRender() override;
		void OnUIRender() override;

	private:
		glm::vec3 m_Translation;
		glm::vec3 m_TranslationB;
		glm::vec3 m_TranslationC;

		glm::vec2 m_Scale;
		glm::vec2 m_ScaleB;
		glm::vec2 m_ScaleC;

		std::unique_ptr<VertexArray> m_VAO;
		std::unique_ptr<VertexBuffer> m_VBO;
		std::unique_ptr<IndexBuffer> m_IBO;
		std::unique_ptr <Shader> m_Shader;

		std::unique_ptr <Sprite> m_SunSprite;
		std::unique_ptr <Sprite> m_IslandSprite;
		std::unique_ptr <Sprite> m_SeaSprite;
	};
}