#pragma once
#include <Rendering/Utils/Shader.h>
#include <Rendering/Utils/Textures/Texture.h>

class Sprite
{
public:
	Sprite(const std::string& texture, VertexArray& vao, IndexBuffer& ibo, Shader& shader);
	~Sprite();
	void Draw(Renderer& renderer);
	void SetTranslation(glm::vec3 newPos);
private:
	glm::vec3 m_Translation;
	glm::mat4 m_Projection;
	glm::mat4 m_View;
	Shader m_Shader;
	Texture m_Texture;
	VertexArray m_VAO;
	IndexBuffer m_IBO;
};