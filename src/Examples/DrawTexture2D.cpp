#include "DrawTexture2D.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Rendering/Buffers/VertexBuffer.h"
#include "Rendering/Buffers/VertexBufferLayout.h"
#include "Rendering/Utils/Texture.h"

namespace tests {
	DrawTexture2D::DrawTexture2D()
		:m_Projection(glm::ortho(-2.0f, 2.0f, -1.5f, 1.5f, -0.1f, 1.0f)),
		m_View(glm::translate(glm::mat4(1.0f), glm::vec3(0.0f))),
		m_Translation(0.0f)
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
		m_Shader->Bind();
		m_Shader->setUniform<float>("uAlpha", 1.0f);
		m_Texture = std::make_unique<Texture>("ricardo.png");
		m_Texture->Bind();
		m_Shader->setUniform<int>("uTexture", 0);
	}

	DrawTexture2D::~DrawTexture2D()
	{

	}

	void DrawTexture2D::OnRender(Renderer& renderer)
	{
		glCall(glClearColor(0.0f, 0.0f, 0.0f, 1.0f));

		glm::mat4 model = glm::translate(glm::mat4(1.0f), m_Translation);
		glm::mat4 pvm = m_Projection * m_View * model;

		renderer.RenderScene(*m_VAO, *m_IBO, *m_Shader);
		m_Shader->setUniform<glm::mat4>("uPVM", pvm);
	}
	void DrawTexture2D::OnUIRender()
	{
		ImGui::SliderFloat2("Position",&m_Translation.x, -1.0f, 1.0f);
	}
}