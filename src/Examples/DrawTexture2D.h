#pragma once
#include "Examples/Application.h"
#include "Rendering/Utils/Texture.h"
#include <memory>

namespace tests {
	class DrawTexture2D : public Application
	{
	public:
		DrawTexture2D();
		~DrawTexture2D();
		void OnRender(Renderer& renderer) override;
		void OnUIRender() override;
	private:
		std::unique_ptr<VertexArray> m_VAO;
		std::unique_ptr<VertexBuffer> m_VBO;
		std::unique_ptr<IndexBuffer> m_IBO;
		std::unique_ptr <Shader> m_Shader;
		std::unique_ptr<Texture> m_Texture;

		glm::vec3 m_Translation;
		glm::mat4 m_Projection;
		glm::mat4 m_View;
	};
}