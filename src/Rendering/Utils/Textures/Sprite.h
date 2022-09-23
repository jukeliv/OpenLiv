#pragma once
#include <Rendering/Utils/Shader.h>
#include <Rendering/Utils/Textures/Texture.h>

class Sprite
{
public:
	Sprite(const std::string& texture, uint32_t param, Shader& shader, VertexArray& vao, IndexBuffer& ibo, const glm::vec2& aspectRation);
	~Sprite();
	void Draw();
	void SetTranslation(const glm::vec3& newPos);
	void SetScale(const glm::vec2& scale);
	bool isColliding(Sprite sprite);

	[[nodiscard]] inline glm::vec2 GetWH() { return glm::vec2(m_Texture.GetWidth(), m_Texture.GetHeight()); }
	[[nodiscard]] inline glm::vec3 getTranslation() { return m_Translation; }
private:
	glm::vec3 m_Translation;
	glm::mat4 m_Projection;
	glm::mat4 m_View;
	glm::vec2 m_Scale;
	Shader m_Shader;
	Texture m_Texture;
	VertexArray m_VAO;
	IndexBuffer m_IBO;
};