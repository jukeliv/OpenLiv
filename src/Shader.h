#pragma once

#include "Core.h"
#include "Renderer.h"

#include <fstream>
#include <string>
#include <sstream>
#include <unordered_map>

struct Vec3
{
	Vec3(float _x, float _y, float _z)
	{
		x = _x;
		y = _y;
		z = _z;
	}

	float x;
	float y;
	float z;
};

class Shader {
public:
	Shader(const char* shaderFolder)
		: mProgramID(0)
	{
		mProgramID = glCreateProgram();
		unsigned int vs = CompileShader(GL_VERTEX_SHADER, shaderFolder);
		unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, shaderFolder);

		glCall(glAttachShader(mProgramID, vs));
		glCall(glAttachShader(mProgramID, fs));
		glCall(glLinkProgram(mProgramID));

		int succes;
		glGetShaderiv(mProgramID, GL_LINK_STATUS, &succes);
		if (!succes)
		{
			int len;
			glGetShaderiv(mProgramID, GL_INFO_LOG_LENGTH, &len);
			char* message = (char*)malloc(len);

			glGetShaderInfoLog(mProgramID, len, &len, message);

			fprintf(stderr, "Failed to link program!!!\n%s\n", message);

			free(message);
		}

		glDeleteShaders({ vs, fs });
	}
	~Shader()
	{
		glCall(glDeleteProgram(mProgramID));
	}

	void Bind() const
	{
		glCall(glUseProgram(mProgramID));
	}
	void UnBind() const
	{
		glCall(glUseProgram(0));
	}

	template<typename T>
	void setUniform(const std::string& uniform, const T& value)
	{
		static_assert(false);
	}

	template<>
	void setUniform<float>(const std::string& uniform, const float& value)
	{
		glCall(glUniform1f(getUniformLocation(uniform), value));
	}

	template<>
	void setUniform<Vec3>(const std::string& uniform, const Vec3& value)
	{
		glCall(glUniform3f(getUniformLocation(uniform), value.x, value.y, value.z));
	}

private:
	unsigned int mProgramID;
	//Implement this again when you know what cause the error
	//std::unordered_map<std::string, unsigned int> m_UniformLocationCage;

	static std::string getShadersPath() { return "res/shaders/"; }

	/*thanks a lot to `HomelikeBrick42` from TheChernos Discord
	* for helping me with the error i was having with this function */
	unsigned int getUniformLocation(const std::string& uniform)
	{
		/*if (m_UniformLocationCage.find(uniform) != m_UniformLocationCage.end())
			return m_UniformLocationCage[uniform];*/

		int location = glGetUniformLocation(mProgramID, uniform.c_str());
		if (location == -1) {
			fprintf(stderr, "ERROR: %s does not exist\n", uniform.c_str());
			return NULL;
		}

		//m_UniformLocationCage[uniform] = location;
		return location;
	}

	static unsigned int CompileShader(unsigned int t, const std::string& folder)
	{
		unsigned int ID = glCreateShader(t);

		const char* t_str = (t == GL_VERTEX_SHADER ? "vertex" : "fragment");

		std::ifstream stream(getShadersPath() + folder + "/" + t_str + ".shader");
		std::stringstream buffer;

		if (!stream) {
			fprintf(stderr, "ERROR: No file in path: %s", getShadersPath() + folder + t_str + ".shader");
			return NULL;
		}

		buffer << stream.rdbuf();

		//Hardcode this shit cuz it hives errors B)
		std::string src = "#version 330 core\n";
		src.append(buffer.str());

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

	static void glDeleteShaders(std::vector<unsigned int> shaders)
	{
		for (int i = 0; i < shaders.size(); i++)
		{
			unsigned int shader = shaders[i];

			glCall(glDeleteShader(shader));
		}
	}
};