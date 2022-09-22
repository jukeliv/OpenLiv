#include "Sprite.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

Sprite::Sprite(const std::string& texture, VertexArray& vao, IndexBuffer& ibo, Shader& shader)
	:m_Texture(texture), m_Translation(0.0f), m_Projection(glm::ortho(-2.0f, 2.0f, -1.5f, 1.5f, -0.1f, 1.0f)),
	m_View(glm::translate(glm::mat4(1.0f), glm::vec3(0.0f))), m_Shader(shader), m_VAO(vao),
	m_IBO(ibo)
{
	m_Shader.Bind();
	m_Shader.setUniform<float>("uAlpha", 1.0f);
	m_Shader.setUniform<int>("uTexture", 0);
}

Sprite::~Sprite()
{
	m_Texture.UnBind();
}

void Sprite::Draw(Renderer& renderer)
{
	m_Texture.Bind();
	glm::mat4 model = glm::translate(glm::mat4(1.0f), m_Translation);
	glm::mat4 pvm = m_Projection * m_View * model;

	renderer.RenderScene(m_VAO, m_IBO, m_Shader);
	m_Shader.setUniform<glm::mat4>("uPVM", pvm);
}

void Sprite::SetTranslation(glm::vec3 newPos)
{
	m_Translation = newPos;
}