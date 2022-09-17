#pragma once
#include "Core.h"

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

namespace OpenLiv {
	class ShadersUtil {
	public:
		static unsigned int CreateShader(const std::string& shadersFolder)
		{
			unsigned int program = glCreateProgram();
			unsigned int vs = CompileShader(GL_VERTEX_SHADER, shadersFolder);
			unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, shadersFolder);

			glAttachShader(program, vs);
			glAttachShader(program, fs);
			glLinkProgram(program);
			glValidateProgram(program);

			glDeleteShader(vs);
			glDeleteShader(fs);

			return program;
		}

		static int UniformLocation(unsigned int& program, std::string variableStr) {
			int location = glGetUniformLocation(program, variableStr.c_str());
			if (location != -1)
				return location;
			else {
				fprintf(stderr, "ERROR: invalid location");
				return 0;
			}
		}
	private:
		static std::string getShadersPath() { return "res/shaders/"; }

		static unsigned int CompileShader(unsigned int t, const std::string& folder) {

			unsigned int ID = glCreateShader(t);

			const char* t_str = (t == GL_VERTEX_SHADER ? "vertex" : "fragment");

			std::ifstream stream(getShadersPath() + folder + t_str + ".shader");
			std::stringstream buffer;
			if (stream)
				buffer << stream.rdbuf();
			else
				fprintf(stderr, "ERROR: No file in path: %s", getShadersPath() + folder + t_str + ".shader");

			std::string src = "#version 330 core\n";
			src.append(buffer.str());

			const char* src_c = src.c_str();

			glShaderSource(ID, 1, &src_c, NULL);

			glCompileShader(ID);
			
			int err;
			glGetShaderiv(ID, GL_COMPILE_STATUS, &err);

			if (err == GL_FALSE)
			{
				int len;
				glGetShaderiv(ID, GL_INFO_LOG_LENGTH, &len);

				char* message = (char*)_alloca(len);

				glGetShaderInfoLog(ID, len, &len, message);

				fprintf(stderr, "Failed to compile %s shader!!!\n%s\n", t_str, message);
			}

			return ID;
		}
	};
}