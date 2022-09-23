#pragma once
#include "Rendering/Renderer.h"
#include <stb_image/stb_image.h>
#include <iostream>

class Texture
{
public:
	Texture(const std::string& file, const uint32_t& param)
		: m_RendererID(0), m_LocalBuffer(nullptr),
		m_Width(0), m_Height(0), m_BPP(0)
	{
		std::string path = "res/textures/";
		path.append(file);

		stbi_set_flip_vertically_on_load(1);
		m_LocalBuffer = stbi_load(path.c_str(), &m_Width, &m_Height, &m_BPP, 4);

		glCall(glGenTextures(1, &m_RendererID));
		glCall(glBindTexture(GL_TEXTURE_2D, m_RendererID));

		glCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, param));
		glCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, param));
		glCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
		glCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));

		glCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_Width, m_Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_LocalBuffer));
		glCall(glBindTexture(GL_TEXTURE_2D, 0));

		if (m_LocalBuffer) {
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_Width, m_Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_LocalBuffer);
			glBindTexture(GL_TEXTURE_2D, 0);
			stbi_image_free(m_LocalBuffer);
			fprintf(stdout, "Succesfully created texture\n %s\n", path.c_str());
		}
		else {
			fprintf(stderr, "Error: Failed to load texture in path\n %s\n( reason: %s )\n", path.c_str(), stbi_failure_reason());
			ASSERT(false);
		}
	}
	~Texture()
	{
		glCall(glDeleteTextures(1, &m_RendererID));
	}

	void Bind(uint8_t slot = 0) const	
	{
		glCall(glActiveTexture(GL_TEXTURE0+slot));
		glCall(glBindTexture(GL_TEXTURE_2D, m_RendererID));
	}

	void UnBind() const
	{
		glCall(glBindTexture(GL_TEXTURE_2D, 0));
	}

	inline int GetWidth() const { return m_Width; }
	inline int GetHeight() const { return m_Height; }
private:
	uint32_t m_RendererID;
	uint8_t* m_LocalBuffer;
	int m_Width, m_Height, m_BPP;
};