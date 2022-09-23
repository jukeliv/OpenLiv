#pragma once
#include "Examples/Application.h"
#include "Rendering/Utils/Textures/Sprite.h"

#include <memory>

namespace examples {
	class DrawTexture2D : public Application
	{
	public:
		DrawTexture2D();
		~DrawTexture2D();
		void OnRender() override;
		void OnUIRender() override;
	private:
		glm::vec3 m_Translation;
		glm::vec3 m_TranslationB;

		std::unique_ptr<VertexArray> m_VAO;
		std::unique_ptr<VertexBuffer> m_VBO;
		std::unique_ptr<IndexBuffer> m_IBO;
		std::unique_ptr <Shader> m_Shader;
		std::unique_ptr<Sprite> m_Sprite;
		std::unique_ptr<Sprite> m_SpriteB;
	};
}