#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <ImGui/imgui.h>
#include "GLErrorManager.h"
#include <StringTools.h>

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <unordered_map>

class Shader {
public:
	Shader(const std::string& shaderFolder)
		: m_ProgramID(0)
	{
		m_ProgramID = glCreateProgram();
		uint32_t vs = CompileShader(GL_VERTEX_SHADER, shaderFolder);
		uint32_t fs = CompileShader(GL_FRAGMENT_SHADER, shaderFolder);

		glCall(glAttachShader(m_ProgramID, vs));
		glCall(glAttachShader(m_ProgramID, fs));
		glCall(glLinkProgram(m_ProgramID));

		int succes;
		glGetShaderiv(m_ProgramID, GL_LINK_STATUS, &succes);
		if (!succes)
		{
			int len;
			glGetShaderiv(m_ProgramID, GL_INFO_LOG_LENGTH, &len);
			char* message = (char*)malloc(len);

			glGetShaderInfoLog(m_ProgramID, len, &len, message);

			fprintf(stderr, "Failed to link program!!!\n%s\n", message);

			free(message);
		}

		glDeleteShaders({ vs, fs });
	}
	~Shader()
	{
		glCall(glDeleteProgram(m_ProgramID));
	}

	void Bind() const
	{
		glCall(glUseProgram(m_ProgramID));
	}
	void UnBind() const
	{
		glCall(glUseProgram(0));
	}

	//Uniforms
	template<typename T>
	void setUniform(const std::string& uniform, const T& value)
	{
		static_assert(false);
	}

	template<>
	void setUniform<int>(const std::string& uniform, const int& value)
	{
		glUniform1i(getUniformLocation(uniform), value);
	}
	template<>
	void setUniform<float>(const std::string& uniform, const float& value)
	{
		glUniform1f(getUniformLocation(uniform), value);
	}
	template<>
	void setUniform<glm::vec3>(const std::string& uniform, const glm::vec3& value)
	{
		glUniform3f(getUniformLocation(uniform), value.r, value.g, value.b);
	}
	template<>
	void setUniform<glm::vec4>(const std::string& uniform, const glm::vec4& value)
	{
		glUniform4f(getUniformLocation(uniform), value.r, value.g, value.b, value.a);
	}
	template<>
	void setUniform < ImVec4 > (const std::string& uniform, const ImVec4& value)
	{
		glUniform4f(getUniformLocation(uniform), value.x, value.y, value.z, value.w);
	}
	template<>
	void setUniform<glm::mat4>(const std::string& uniform, const glm::mat4& value)
	{
		glUniformMatrix4fv(getUniformLocation(uniform), 1, GL_FALSE, &value[0][0]);
	}

private:
	uint32_t m_ProgramID;

	mutable std::unordered_map<std::string, uint32_t> m_UniformLocationCage;

	static std::string getShadersPath() { return "res/shaders/"; }

	/*thanks a lot to `HomelikeBrick42` from TheChernos Discord
	* for helping me with the error i was having with this function */
	uint32_t getUniformLocation(const std::string& uniform) const
	{
		if (m_UniformLocationCage.find(uniform) != m_UniformLocationCage.end())
			return m_UniformLocationCage.at(uniform);

		uint32_t location = glGetUniformLocation(m_ProgramID, uniform.c_str());

		if (location == -1) {
			fprintf(stderr, "ERROR: %s does not exist\n", uniform.c_str());
			return NULL;
		}

		m_UniformLocationCage[uniform] = location;
		return location;
	}

	static uint32_t CompileShader(uint32_t t, const std::string& folder)
	{
		const char* t_str = (t == GL_VERTEX_SHADER ? "vertex.shader" : "fragment.shader");

		const std::string file = StringTools::getFile(getShadersPath() + folder, t_str);

		uint32_t ID = glCreateShader(t);

		//Hardcode this shit cuz it gives errors B)
		std::string src = "#version 330 core\n\n";
		src.append(file.c_str());

		const char* src_c = src.c_str();

		glShaderSource(ID, 1, &src_c, NULL);

		glCall(glCompileShader(ID));
			
		int succes;
		glGetShaderiv(ID, GL_COMPILE_STATUS, &succes);
		if (!succes)
		{
			int len;
			glGetShaderiv(ID, GL_INFO_LOG_LENGTH, &len);

			char* message = (char*)malloc(len);

			glGetShaderInfoLog(ID, len, &len, message);

			fprintf(stderr, "Failed to compile %s shader!!!\n%s\n", t_str, message);

			free(message);
		}

		return ID;
	}

	static void glDeleteShaders(std::vector<uint32_t> shaders)
	{
		for(auto& shader : shaders)
		{
			glCall(glDeleteShader(shader));
		}
	}
};