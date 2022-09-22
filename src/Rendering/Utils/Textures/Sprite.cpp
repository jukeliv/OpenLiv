#include "Sprite.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

Sprite::Sprite(const std::string& texture, uint32_t param, Shader& shader, VertexArray& vao, IndexBuffer& ibo)
	:m_Texture(texture, param), m_Translation(0.0f), m_Projection(glm::ortho(-8.0f, 8.0f, -4.5f, 4.5f, -0.1f, 1.0f)),
	m_Shader(shader), m_VAO(vao), m_IBO(ibo), m_Scale(1.0f), m_View(glm::translate(glm::mat4(1.0f), m_Translation))
{
	m_Shader.Bind();
	m_Texture.Bind();
	m_Shader.setUniform<int>("uTexture", 0);

	vao.UnBind();
	ibo.UnBind();
	m_Shader.UnBind();
	m_Texture.UnBind();
}

Sprite::~Sprite()
{
	m_Texture.UnBind();
}

void Sprite::Draw(Renderer& renderer)
{
	m_Texture.Bind();

	{
		glm::mat4 model = glm::translate(glm::mat4(1.0f), m_Translation);
		glm::mat4 pvm = m_Projection * m_View * model;

		m_Shader.Bind();
		m_Shader.setUniform<glm::vec2>("uScale", m_Scale);
		m_Shader.setUniform<glm::mat4>("uPVM", pvm);

		renderer.RenderScene(m_VAO, m_IBO, m_Shader);
	}
}


void Sprite::SetTranslation(const glm::vec3& newPos)
{
	m_Translation = newPos;
}

/*
void Sprite::SetScale(const float& scale)
{
	m_Scale = scale;
}
*/
void Sprite::SetScale(const glm::vec2& scale)
{
	m_Scale = scale;
}