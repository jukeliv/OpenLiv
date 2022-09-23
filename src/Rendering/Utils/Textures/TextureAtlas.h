#pragma once
#include "Texture.h"
struct TextureAtlasData
{
	std::string name;
	int x,y;
	int w,h;
};
class TextureAtlas
{
	TextureAtlas(const std::string& image, std::vector<TextureAtlasData> data)
	{
		for (auto& frame : data)
		{
			glm::vec2 pos(frame.x, frame.y);
			glm::vec2 dim(frame.w, frame.h);

			Texture img(image, GL_NEAREST);
			
		}
	}
private:
	std::vector<Texture> m_Frames;
};