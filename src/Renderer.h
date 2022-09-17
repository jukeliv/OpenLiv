#pragma once

#include "Core.h"

#define ASSERT(x) if (!(x)) __debugbreak();
#define glCall(x) while (glGetError());\
    x;\
    ASSERT(glCheckError(#x, __FILE__, __LINE__))

bool glCheckError(const char* func, const char* file, int line);