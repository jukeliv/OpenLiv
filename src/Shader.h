#pragma once

#include "Core.h"
#include "Renderer.h"

#include <fstream>
#include <string>
#include <sstream>

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

		glAttachShader(mProgramID, vs);
		glAttachShader(mProgramID, fs);
		glLinkProgram(mProgramID);

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

		glDeleteShader(vs);
		glDeleteShader(fs);
	}
	~Shader()
	{
		glDeleteProgram(mProgramID);
	}

	void Bind() const
	{
		glCall(glUseProgram(mProgramID));
	}
	void UnBind() const
	{
		glCall(glUseProgram(0));
	}

	inline void setFloat(const char* fUniform, float v) { glUniform1f(getUniformLocation(fUniform), v); }

	inline void setVec3(const char* fUniform, const Vec3& v) { glUniform3f(getUniformLocation(fUniform), v.x, v.y, v.z); }
private:
	unsigned int mProgramID;
	static std::string getShadersPath() { return "res/shaders/"; }

	unsigned int getUniformLocation(const char* uniform) const
	{
		int location = glGetUniformLocation(mProgramID, uniform);
		if (location != -1)
			return location;
		else {
			fprintf(stderr, "ERROR: invalid location");
			return NULL;
		}
	}

	static unsigned int CompileShader(unsigned int t, const std::string& folder)
	{
		unsigned int ID = glCreateShader(t);

		const char* t_str = (t == GL_VERTEX_SHADER ? "vertex" : "fragment");

		std::ifstream stream(getShadersPath() + folder + "/" + t_str + ".shader");
		std::stringstream buffer;
		if (stream)
			buffer << stream.rdbuf();
		else
			fprintf(stderr, "ERROR: No file in path: %s", getShadersPath() + folder + t_str + ".shader");

		//Hardcode this shit cuz it hives errors B)
		std::string src = "#version 330 core\n";
		src.append(buffer.str());

		const char* src_c = src.c_str();

		glShaderSource(ID, 1, &src_c, NULL);

		glCompileShader(ID);
			
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
};