#pragma once

#include "GLErrorManager.h"
#include <iostream>
#include <fstream>
#include <sstream>

class StringTools {
public:
	static std::string getFile(const std::string& folder, const std::string& file)
	{
		std::ifstream stream(folder + "/"  + file);
		std::stringstream buffer;

		if (!stream) {
			fprintf(stderr, "ERROR: No file in path: %s\n", folder + "/" + file);
			ASSERT(false);
		}

		buffer << stream.rdbuf();

		return buffer.str();
	}
};